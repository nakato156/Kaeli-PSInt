#pragma once

#include <vector>
#include <string>

#include "Token.h"

class Funcion {
private:
    std::string nombre;
    std::vector<Token> contenido, returned, args;
public:
    Funcion() = default;
    Funcion(std::string, std::vector<Token>, std::vector<Token>);
    std::string getNombre();
    std::vector<Token> getContenido();
    std::vector<Token> getSentReturn();
    std::vector<Token> getArgs();
    friend std::ostream& operator <<(std::ostream& os, const Funcion& func);
};