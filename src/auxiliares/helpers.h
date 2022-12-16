#pragma once

#include <string>

namespace Helpers
{
    bool validIdentificador(std::string token);

    bool esOperador(char c, std::string operadores, int size);

    bool esEntero(std::string str);

    bool esIdentificador(std::string str);

    std::string trim(std::string str);

    bool consolaPropia();
}