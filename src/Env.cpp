#include <iostream>

#include "Env.h"

map<string, function<Token(Token, Token)>> operaciones_igualdad = {
    {
        "==",
        [](Token x, Token y) { return x == y; },
    },
    {
        ">=",
        [](Token x, Token y) { return x >= y; },
    },
    {
        "<=",
        [](Token x, Token y) { return x <= y; },
    },
    {
        ">",
        [](Token x, Token y) { return x > y; },
    },
    {
        "<",
        [](Token x, Token y) { return x < y; },
    }};

map<string, function<Token(Token, Token)>> operaciones_aritmeticas = {
    {"+", [](Token x, Token y) { return x + y; }},
    {"-", [](Token x, Token y) { return x - y; }},
    {"*", [](Token x, Token y) { return x * y; }},
    {"/", [](Token x, Token y) { return x / y; }},
    {"&", [](Token x, Token y) { return x && y; }},
    {"|", [](Token x, Token y) { return x || y; }},
};
