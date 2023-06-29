#include <cmath>
#include "Valor.h"
#include <map>
#include <vector>

namespace MatesLib {
    Token calcularRaizCuadrada(std::vector<Valor> tokens);
    Token valorAbsoluto(std::vector<Valor> tokens);

    void exportar(std::map<std::string, Token(*)(std::vector<Valor>)>&);
}