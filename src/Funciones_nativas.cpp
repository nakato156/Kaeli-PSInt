#include "Funciones_nativas.h"

#include "Exceptions.h"
#include "Nativo.h"
#include "Valor.h"

using namespace std;
using namespace Nativo;
using namespace Exceptions;

Token Funciones_Nativas::call(string name_func, vector<Valor> &args, int linea) {
    if (name_func == "imprimir")
        return imprimir(args, "\n", " ");
    // else if(name_func == "leer") return leer(args);
    throw NameError(name_func, linea);
}