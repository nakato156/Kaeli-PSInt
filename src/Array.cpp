#include <iostream>
#include <algorithm>
#include "./cabeceras/Array.h"

using namespace std;

Array::Array(vector<Token> arr): lista(arr) {}
vector<Token> Array::getContenido() { return lista; }
int Array::length(){ return lista.size(); }

void Array::addItem(Token tk){ lista.push_back(tk); }
void Array::delItem(Token tk){ 
    vector<Token> nueva_lista;
    copy_if(lista.begin(), lista.end(), back_inserter(nueva_lista), [&](Token item){
        return !bool(item == tk);
    });
    lista = nueva_lista;
}

Token Array::operator ==(Array& arr){
    if(this->lista.size() != arr.length()) return Token(false, lista[0].getLinea());
    for(int i = 0; i < arr.length(); i++){
        if(!bool(this->lista[i] == arr.lista[i])) return Token(false, lista[0].getLinea());
    }
    return Token(true, lista[0].getLinea());
}

ostream& operator <<(ostream& os, const Array& arr){
    auto lista = arr.lista;
    int size = lista.size();
    
    os << "[ ";
    for(int i = 0; i < size; i++){
        os << lista[i]; 
        if(i + 1 != size) os << ", ";
    }
    os << " ]";
    return os;
}