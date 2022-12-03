#include "./cabeceras/Valor.h"
#include "Nativo.cpp"
#include "./cabeceras/Exceptions.h"

using namespace std;
using namespace Nativo;

class Funciones_Nativas {
    public:
    static Token call(string name_func, vector<Valor> &args, int linea){
        if(name_func == "imprimir") return imprimir(args, "\n", " ");
        //else if(name_func == "leer") return leer(args);
        throw NameError(name_func, linea);
    }
};