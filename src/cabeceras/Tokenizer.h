#pragma once

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
    Token get();
    Token get(int n);
    int size();
    std::vector<Token> getTokens();
    Token operator [](int index);
};