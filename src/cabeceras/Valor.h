#ifndef VALOR
#define VALOR
#include "../Array.cpp"

class Valor: public Array {
private:
    bool _is_array = false;
public:
    Valor() = default;
    Valor(Array arr);
    Valor(Token tk);
    bool is_array();
    friend std::ostream& operator <<(std::ostream& os, const Valor& val);
};
#endif