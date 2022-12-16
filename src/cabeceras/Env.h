#pragma once

#include <map>
#include <string>
#include <functional>

#include "Token.h"

using namespace std;

extern map<string, function<Token(Token, Token)>> operaciones_igualdad;
extern map<string, function<Token(Token, Token)>> operaciones_aritmeticas;