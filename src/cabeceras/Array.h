#ifndef Array_h
#define Array_h
#include "Token.h"
#include <vector>

class Array : public Token {
protected:
    std::vector<Token> lista;
public:
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