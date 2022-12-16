#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "definiciones.h"
#include "Token.h"

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