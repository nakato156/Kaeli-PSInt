#include "Nativo.h"

using namespace std;

Token Nativo::imprimir(vector<Valor> args, string end = "\n", string sep = " ") {
    Valor tk;
    for (Valor i : args) {
        cout << i << sep;
        tk = i;
    }
    cout << end;
    return Token(string("NADA"), tk.getLinea());
}

/*
Token Nativo::leer(vector<Token> args){
    string promp;
    for(auto arg: args) promp+= arg;

    return Token(string("NADA"), args.at(args.size() - 1).getLinea());
}
*/