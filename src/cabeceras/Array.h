#ifndef Array_h
#define Array_h
#include "Token.h"
#include <vector>

class Array : public Token {
public:
    std::vector<Token> lista;
    Array() = default;
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
#endif