#include <vector>

#include "Token.h"
#include "Stack.h"
#include "Variables.h"
#include "Funcion.h"

using namespace std;

namespace Evaluadores {
    vector<Valor> procesar_simple_args(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars);

    map<string, Valor> procesar_kwargs(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, vector<Token> &argsFunc);

    void eval_func(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars);

    Token call_new_funcion(Funcion &func, void (*runner)(vector<Token> &, Variables &), Variables &args);

    Token call_native_func(Token &token_func, vector<Valor> &args);

    Token llamar_funcion(Token token_func, vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars);

    Array eval_arreglo(vector<Token>::iterator &it, vector<Token>::iterator &end, Variables &vars);

    Stack eval_expresion(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars, bool block = false);

    Token eval_arg(vector<Token>&, Variables &);

    void eval_condicion(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars);

    vector<Token> procesar_bloque(vector<Token>::iterator &it, vector<Token>::iterator &fin);

    void eval_for(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars);

    void eval_identifier(vector<Token>::iterator &it_pgma, vector<Token>::iterator &fin_it, Variables &variables);

    void run(vector<Token> &pgma, Variables &variables);

} // namespace Evaluadores
