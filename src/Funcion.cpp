#include "cabeceras/Funcion.h"

using namespace std;

Funcion::Funcion(string name, vector<Token> content, vector<Token> args_): contenido(content), args(args_){
    nombre = "__funcion." + name;
    // args["__nombre__"] = Token("name", content[0].getLinea());
};

string Funcion::getNombre(){ return nombre; }
vector<Token> Funcion::getContenido(){ return contenido; }
vector<Token> Funcion::getSentReturn(){ return returned; }
vector<Token> Funcion::getArgs(){ return args; }

ostream& operator <<(ostream& os, const Funcion& func) {
    os << func.nombre;
    return os;
}