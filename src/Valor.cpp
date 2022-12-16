#include "Valor.h"

using namespace std;

Valor::Valor(Array arr) : Array(arr) { _is_array = true; }
Valor::Valor(Token tk) : Array(tk) {}

bool Valor::is_array() { return _is_array; }

ostream &operator<<(ostream &os, const Valor &val) {
    if (val._is_array) {
        Array arr = val.lista;
        os << arr << endl;
    } else
        os << Token(val);
    return os;
};