#include "./cabeceras/Valor.h"

using namespace std;

Valor::Valor(Array arr): array(arr) { _is_array = true; }
Valor::Valor(Token tk): Array(tk) {}

bool Valor::is_array(){ return _is_array; }
Array Valor::getArray(){ return array; }
Token Valor::getToken(){ return *this; }

ostream& operator <<(ostream& os, const Valor& val){
    if(val._is_array) os << val.array;
    else os << Token(val);
    return os;
};