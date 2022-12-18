#pragma once

#include <iostream>
#include <string>
#include <map>

#include "definiciones.h"

template <class T>
T token_parser(std::string const &valor);

template <>
int token_parser<int>(std::string const &valor);

template <>
std::string token_parser<std::string>(std::string const &valor);

class Token
{
protected:
    std::string valor;
    int tipo, num_linea;
    std::map<std::string, int> tipos_precedencia = {
        { "+", 1 }, { "-", 1 },
        { "!", 2 }, { "&", 2 }, { "|", 2 },
        { "*", 3 }, { "/", 3 }, { "^", 3 }, { "%", 3 },
    };
    int precedencia = -1;
    std::map<int, std::string> nombreTipo = {
        {STRING, "string"},
        {ENTERO, "entero"},
        {BOOL, "booleano"},
        {ARRAY, "arreglo"},
        {FLOAT, "decimal"},
        {NADA, "nada"},
    };
public:
    Token();
    Token(bool tk, int linea);
    Token(std::string tk, int linea);

    template<class T>
    T parse() const;

    std::string getNombreTipo();
    int getTipo();
    std::string& getValor();
    int getLinea();
    int getPrecedencia();

    Token& operator++();
    Token operator++(int);
    Token operator ==(Token& tk);
    Token operator >=(Token& tk);
    Token operator <=(Token& tk);
    Token operator >(Token& tk);
    Token operator <(Token& tk);
    Token operator +(Token& tk);
    Token operator -(Token& tk);
    Token operator *(Token& tk);
    Token operator /(Token& tk);
    Token operator &&(Token& tk);
    Token operator ||(Token& tk);
    operator bool() const;

    friend std::ostream& operator <<(std::ostream& os, const Token& tk);
};