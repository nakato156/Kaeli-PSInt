#include "map"
#include "Valor.cpp"
#include "Funcion.cpp"
#include "./cabeceras/Exceptions.h"

using Exceptions::NameError;

class Variables {
private:
    map<string, Valor> variables;
    map<string, Funcion> funciones;
public:
    Variables() = default;
    
    int size(){ return variables.size(); }
    
    void agregar(string nombre, Valor arr){ variables[nombre] = arr; }
    void agregar(string nombre, Token token) { variables[nombre] = Valor(token); }
    void agregar(string nombre, Funcion func) { funciones[nombre] = func; }
    
    void eliminar(string nombre){
        if(variables.find(nombre) != variables.end()) variables.erase(nombre);
    }

    Funcion getFunc(string nombre){ return funciones[nombre]; };

    Valor operator [](const string nombre) { 
        if(variables.find(nombre) != variables.end()) return variables[nombre];
        throw NameError(nombre);
    }

    friend ostream& operator <<(ostream &os, const Variables &vars){
        os << "{" << endl;
        for(auto &item: vars.variables) 
            os << "\t" << item.first << ": " << item.second << "," << endl;
        for(auto &item: vars.funciones) 
            os << "\t" << item.first << ": " << item.second << "," << endl;
        os << "}" << endl;
        return os;
    }
};