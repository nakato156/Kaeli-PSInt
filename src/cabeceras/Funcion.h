#ifndef FUNCION_h
#define FUNCION_h
#include "Token.h"
#include <vector>

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
#endif