#include "Variables.h"

#include "Exceptions.h"

using Exceptions::NameError;
using namespace std;

Variables::Variables(map<string, Valor> &vars) : variables(vars) {}

int Variables::size() { return variables.size(); }

void Variables::agregar(const string &nombre, Valor &arr) { variables[nombre] = arr; }
void Variables::agregar(const string &nombre, Token &token) { variables[nombre] = Valor(token); }
void Variables::agregar(const string &nombre, Funcion &func) { funciones[nombre] = func; }

void Variables::eliminar(const string &nombre) {
    if (variables.find(nombre) != variables.end())
        variables.erase(nombre);
}

Funcion& Variables::getFunc(const string &nombre) { return funciones[nombre]; };

Valor& Variables::operator[](const string &nombre) {
    if (variables.find(nombre) != variables.end())
        return variables[nombre];
    throw NameError(nombre);
}

ostream& operator<<(ostream &os, const Variables &vars) {
    os << "{" << endl;
    for (auto &item : vars.variables)
        os << "\t" << item.first << ": " << item.second << "," << endl;
    for (auto &item : vars.funciones)
        os << "\t" << item.first << ": " << item.second << "," << endl;
    os << "}" << endl;
    return os;
}