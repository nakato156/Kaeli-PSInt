#pragma once

#include <vector>
#include "Token.h"

class Array : public Token {
protected:
    std::vector<Token> lista;
public:
    Array() = default;
    Array(Token);
    Array(std::vector<Token>);
    ~Array() = default;
    int length();
    std::vector<Token> getContenido();
    void addItem(Token tk);
    void delItem(Token tk);
    void remove(int pos);

    Token operator ==(Array& arr);
    friend std::ostream& operator <<(std::ostream& os, const Array& arr);
};