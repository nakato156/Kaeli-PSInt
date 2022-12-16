#include <iostream>
#include <string>

#include "Exceptions.h"

using namespace Exceptions;
using namespace std;

BaseError::BaseError() { num_linea = 0; }
int BaseError::getLinea() { return num_linea; }
int BaseError::getLinea(BaseError e) { return e.getLinea(); }

EOLError::EOLError() { message = "\rEOL Error en:"; }
EOLError::EOLError(int num_linea) {
    this->num_linea = num_linea - 1;
    message += "\n" + string(to_string(num_linea)) + " | ";
}
const char *EOLError::what() const throw() {
    return message.c_str();
}

TokenError::TokenError() { message = "\rToken no reconocido"; }
TokenError::TokenError(int num_linea) {
    this->num_linea = num_linea - 1;
    message += "\n" + string(to_string(num_linea)) + " | ";
}
const char *TokenError::what() const throw() { return message.c_str(); }

TypeError::TypeError() {}
TypeError::TypeError(string msg, int num_linea) {
    message = msg + "\n";
    this->num_linea = --num_linea;
}
TypeError::TypeError(string tipo1, string tipo2, int num_linea) {
    this->num_linea = num_linea - 1;
    message += "\nNo se puede operar " + tipo1 + " con " + tipo2 + " en:\n" + to_string(num_linea) + " | ";
}
const char *TypeError::what() const throw() { return message.c_str(); }

NameError::NameError() = default;
NameError::NameError(string identificador) {
    message += "El identificador " + identificador + " no se ha definido en el ámbito en que se usa.\n";
}
NameError::NameError(string identificador, int num_linea) {
    message += "El identificador " + identificador + " no se ha definido en el ámbito en que se usa.\nError en la línea " + to_string(num_linea) + "\n";
    this->num_linea = --num_linea;
}
const char *NameError::what() const throw() { return message.c_str(); }

ArgumentError::ArgumentError() = default;
ArgumentError::ArgumentError(string argumento, int num_linea) {
    message += "No se ha reconocid el argumento `" + argumento + "` en la línea:\n";
    this->num_linea = --num_linea;
}
const char *ArgumentError::what() const throw() { return message.c_str(); }
