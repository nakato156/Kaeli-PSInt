#include "cabeceras/Nativo.h"

using namespace std;

Token Nativo::imprimir(vector<Token> args, string end = "\n", string sep = " "){
    Token i;
    for(auto i: args) cout << i << sep;
    cout << end;
    return Token(string("NADA"), i.getLinea());
}

/*
Token Nativo::leer(vector<Token> args){
    string promp;
    for(auto arg: args) promp+= arg;

    return Token(string("NADA"), args.at(args.size() - 1).getLinea());
}
*/