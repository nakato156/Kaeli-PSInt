#ifndef VALOR
#define VALOR
#include "../Array.cpp"

class Valor: public Array {
private:
    bool _is_array = false;
    Array array;
    Token token;

public:
    Valor() = default;
    Valor(Array arr);
    Valor(Token tk);
    bool is_array();
    Array getArray();
    Token getToken();
    std::vector<Token> get();
    friend std::ostream& operator <<(std::ostream& os, const Valor& val);
};
#endif