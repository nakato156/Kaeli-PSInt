#include <iostream>
#include <functional>
#include <map>
#include <string>
#include "cabeceras/Token.h"

using namespace std;

inline map<string, function<Token(Token, Token)>> operaciones_igualdad = {
    { "==" , [](Token x, Token y){ return x == y; }, },
    { ">=", [](Token x, Token y){ return x >= y; }, },
    { "<=", [](Token x, Token y){ return x <= y; }, },
    { ">" , [](Token x, Token y){ return x > y; }, },
    { "<" , [](Token x, Token y){ return x < y; }, }
};

inline map<string, function<Token(Token, Token)>> operaciones_aritmeticas = {
    { "+", [](Token x, Token y){ return x + y; } },
    { "-", [](Token x, Token y){ return x - y; } },
    { "*", [](Token x, Token y){ return x * y; } },
    { "/", [](Token x, Token y){ return x / y; } },
    { "&", [](Token x, Token y){ return x && y; } },
    { "|", [](Token x, Token y){ return x || y; } },
};
