#ifndef STACK
#define STACK
#include "Valor.h"
#include <vector>

class Stack
{
private:
    std::vector<Token> valores, operadores, tmp_val, array_tks;
    std::vector<Token>::iterator fin_it;
public:
    Stack();
    Stack(std::vector<Token>::iterator&);
    void add_valores(Token &tk);
    void add_operadores(Token &tk);
    Token operar(Token&, std::string, Token);
    void agregar(Valor val, vector<Token>::iterator &it);
    void agregar(Token tk, std::vector<Token>::iterator&);
    Array get_array();
    Token get_stack();
};
#endif