#pragma once

#include <string>
#include <vector>

#include "Token.h"
#include "Valor.h"

namespace Funciones_Nativas {
    Token call(std::string name_func, std::vector<Valor> &args, int linea);
};