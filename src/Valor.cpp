#include "./cabeceras/Valor.h"

using namespace std;

Valor::Valor(Array arr): array(arr) { _is_array = true; }
Valor::Valor(Token tk): token(tk) {}

bool Valor::is_array(){ return _is_array; }
Array Valor::getArray(){ return array; }
Token Valor::getToken(){ return token; }

vector<Token> Valor::get(){
    if(_is_array) return array.getContenido();
    vector<Token> tks;
    tks.push_back(token);
    return tks;
}

ostream& operator <<(ostream& os, const Valor& val){
    if(val._is_array) os << val.array;
    else os << val.token;
    return os;
};