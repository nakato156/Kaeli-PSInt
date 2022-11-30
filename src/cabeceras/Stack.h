#pragma once
#include "Array.h"
#include <vector>

class Stack
{
private:
    std::vector<Token> valores, operadores, tokens, tmp_val, array_tks;
    std::vector<Token>::iterator iter;
public:
    Stack();
    Stack(std::vector<Token>&);
    void add_valores(Token tk);
    void add_operadores(Token tk);
    Token operar(Token, std::string, Token);
    void agregar(Array arr, vector<Token>::iterator &it);
    void agregar(Token tk, std::vector<Token>::iterator&);
    vector<Token> get_array();
    Token get_stack();
};
