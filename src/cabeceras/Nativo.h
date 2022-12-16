#pragma once

#include <string>
#include <vector>

#include "Token.h"
#include "Valor.h"

namespace Nativo
{
    Token imprimir(std::vector<Valor> args, std::string end, std::string sep);
    //Token leer(std::vector<Token>);
}