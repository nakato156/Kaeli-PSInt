#pragma once
#include "Token.h"
#include <vector>

class Stack
{
private:
    std::vector<Token> valores, operadores, tokens, tmp_val;
    std::vector<Token>::iterator iter;
public:
    Stack();
    Stack(std::vector<Token>&);
    void add_valores(Token tk);
    void add_operadores(Token tk);
    Token operar(Token, std::string, Token);
    void agregar(Token tk, std::vector<Token>::iterator&);
    Token get_stack();
};
