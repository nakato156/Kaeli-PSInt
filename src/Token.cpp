#include "Token.h"

#include <iostream>
#include <string>

#include "Exceptions.h"
#include "auxiliares/helpers.h"
#include "definiciones.h"

using namespace std;
using namespace Helpers;
using namespace Exceptions;

template <>
int token_parser<int>(string const &valor) {
    if (valor == "verdadero" || valor == "falso" || valor == "NADA")
        return valor == "verdadero";
    return stoi(valor);
}

template <>
string token_parser<string>(string const &valor) { return valor; }

Token::Token(){};
Token::Token(bool tk, int linea) : valor(string(tk ? "verdadero" : "falso")), num_linea(linea) {}
Token::Token(string tk, int linea) {
    valor = tk;
    if (tk == "=")
        tipo = ASIGNACION;
    else if (tk == ";")
        tipo = END;
    else if (tk[0] == '"' && tk[tk.size() - 1] == '"') {
        tipo = STRING;
        valor = tk.substr(1, tk.size() - 2);
    } else if (tk.size() == 1 && Operadores.find(tk) != string::npos) {
        tipo = OPERADOR;
        precedencia = tipos_precedencia[tk];
    } else if (esEntero(tk))
        tipo = ENTERO;
    else if (tk == "START")
        tipo = START_BLOCK;
    else if (tk == "END")
        tipo = END_BLOCK;
    else if (tk == "NADA")
        tipo = NADA;
    else if (tk == "iterar")
        tipo = FOR;
    else if (tk == "mientras")
        tipo = WHILE;
    else if (tk == "verdadero" || tk == "falso")
        tipo = BOOL;
    else if (tk == "si" || tk == "sino")
        tipo = CONDICION;
    else if (tk == "funcion")
        tipo = FUNCION;
    else if (!isdigit(tk[0]) && validIdentificador(tk))
        tipo = IDENTIFICADOR;
    else
        throw TokenError(linea);
    num_linea = linea;
}

string Token::getNombreTipo() { return nombreTipo[tipo]; }
int Token::getTipo() { return tipo; }
string &Token::getValor() { return valor; }
int Token::getLinea() { return num_linea; }
int Token::getPrecedencia() { return precedencia; }

template <class T>
T Token::parse() const { return token_parser<T>(valor); }

Token &Token::operator++() {
    int v = stoi(valor);
    valor = to_string(++v);
    return *this;
}

Token Token::operator++(int) {
    Token temp = *this;
    temp.tipo = ENTERO;
    ++*this;
    return temp;
}

Token Token::operator==(Token &tk) {
    if (tk.getTipo() != tipo)
        return Token(false, num_linea);
    if (tk.tipo == ENTERO)
        return Token(tk.parse<int>() == this->parse<int>(), num_linea);
    if (tk.tipo == STRING)
        return Token(tk.parse<string>() == this->parse<string>(), num_linea);

    return Token(false, num_linea);
};
Token Token::operator>=(Token &tk) { return tk; };
Token Token::operator<=(Token &tk) { return tk; };
Token Token::operator>(Token &tk) { return tk; };

Token Token::operator<(Token &tk) {
    if ((tk.tipo != tipo) && (tipo != ENTERO || tipo != FLOAT))
        throw TypeError(tk.getNombreTipo(), this->getNombreTipo(), num_linea);
    return tk;
};

Token Token::operator+(Token &tk) {
    if (tk.tipo == ENTERO && ENTERO == tipo)
        return Token(to_string(tk.parse<int>() + this->parse<int>()), num_linea);
    if (tk.tipo == STRING && STRING == tipo) {
        return Token('"' + tk.getValor() + this->valor + '"', num_linea);
    }
    throw TypeError(tk.getNombreTipo(), this->getNombreTipo(), num_linea);
};

Token Token::operator-(Token &tk) {
    if (tk.tipo == ENTERO && tipo == ENTERO)
        return Token(to_string(tk.parse<int>() - this->parse<int>()), num_linea);
    else
        throw TypeError(tk.getNombreTipo(), this->getNombreTipo(), num_linea);
};

Token Token::operator*(Token &tk) {
    if (tk.tipo == ENTERO && ENTERO == tipo || tk.tipo == BOOL && tipo == ENTERO)
        return Token(to_string(tk.parse<int>() * this->parse<int>()), num_linea);
    else
        throw TypeError(tk.getNombreTipo(), this->getNombreTipo(), num_linea);
    return tk;
};

Token Token::operator/(Token &tk) {
    if (tk.tipo == ENTERO && ENTERO == tipo)
        return Token(to_string(tk.parse<int>() / this->parse<int>()), num_linea);
    throw TypeError(tk.getNombreTipo(), this->getNombreTipo(), num_linea);
    return tk;
};

Token Token::operator&&(Token &tk) {
    if (tk.tipo == ENTERO && ENTERO == tipo)
        return Token(to_string(tk.parse<int>() && this->parse<int>()), num_linea);
    throw TypeError(tk.getNombreTipo(), this->getNombreTipo(), num_linea);
    return tk;
};

Token Token::operator||(Token &tk) { return tk; };

Token::operator bool() const {
    return valor != "0" && valor != "falso";
}

ostream &operator<<(ostream &os, const Token &tk) {
    os << tk.valor;
    return os;
}
