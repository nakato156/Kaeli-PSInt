#pragma once

#include <string>
#include <vector>
#include <map>

#include "Token.h"
#include "Valor.h"

namespace Funciones_Nativas {
    using map_funcs = std::map<std::string, Token(*)(std::vector<Valor>)>;
    Token call(std::string name_func, std::vector<Valor> &args, int linea);
    // Token call_fun_lib(const std::string& name_func, std::vector<Valor> &args, map_funcs& funcs, int linea);
};