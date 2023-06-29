#include "Mates.h"
#include "Exceptions.h"
#include <string>

using namespace std;

inline Token MatesLib::calcularRaizCuadrada(vector<Valor> tokens){
    Token token = tokens[0];
    if (token.getTipo() == ENTERO) {
        int valor = token.parse<int>();
        if (valor >= 0) {
            int resultado = static_cast<int>(std::sqrt(valor));
            return Token(to_string(resultado), token.getLinea());
        } else {
            throw std::domain_error("No se puede calcular la raíz cuadrada de un número negativo.");
        }
    } else {
        throw std::invalid_argument("El token debe ser de tipo ENTERO para calcular la raíz cuadrada.");
    }
}

Token MatesLib::valorAbsoluto(vector<Valor> tokens) {
    Token token = tokens[0];
    if (token.getTipo() == ENTERO) {
        int valor = token.parse<int>();
        int resultado = std::abs(valor);
        return Token(to_string(resultado), token.getLinea());
    } else 
        throw Exceptions::TypeError("El token debe ser de tipo ENTERO para calcular el valor absoluto.", token.getLinea());
}