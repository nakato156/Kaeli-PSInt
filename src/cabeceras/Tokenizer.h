#ifndef TOKENIZER_h
#define TOKENIZER_h
#include "definiciones.h"
#include <iostream>
#include <vector>
#include "../Token.cpp"

class Tokenizer {
private:
    std::vector<Token> tokens;
public:
    Tokenizer();
    Tokenizer(std::vector<std::string> lineas);
    Tokenizer(std::string command);//Para nuestro interprete.
    Token get();
    Token get(int n);
    int size();
    std::vector<Token> getTokens();
    Token operator [](int index);
};
#endif