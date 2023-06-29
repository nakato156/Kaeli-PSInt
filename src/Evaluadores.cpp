#include "Evaluadores.h"
#include <functional>
#include "Nativo.h"
#include "Funciones_nativas.h"
#include "Exceptions.h"

using namespace std;
using namespace Nativo;
using namespace Exceptions;

Token Evaluadores::eval_arg(vector<Token>& args, Variables &vars) {
    vector<Token>::iterator begin = args.begin(),  end = args.end();
    args.push_back(Token(string(";"), begin->getLinea()));
    Stack stack = eval_expresion(begin, end, vars, false);
    return stack.get_stack();
}

vector<Valor> Evaluadores::procesar_simple_args(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars) {
    vector<Valor> args;
    vector<Token> temp_arg;
    int fin = 1, i = 0;
    for (; it != fin_it; it++) {
        if (it->getValor() == ")" && fin - 1 == 0)
            break;
        else if (it->getValor() == "(")
            fin++;
        else if (it->getValor() == ")")
            fin--;
        else if (it->getValor() == ",") {
            if (temp_arg.size() == 1)  args.push_back(temp_arg[0]);
            else if (temp_arg.size() > 1)
                args.push_back(eval_arg(temp_arg, vars));
                
            temp_arg.clear();
            continue;
        }

        if (it->getTipo() == IDENTIFICADOR)
            args.push_back(vars[it->getValor()]);
        else
            temp_arg.push_back(*it);
    }

    if (temp_arg.size() == 1) args.push_back(temp_arg[0]);
    else if (temp_arg.size() >1) args.push_back(eval_arg(temp_arg, vars));
    return args;
}

map<string, Valor> Evaluadores::procesar_kwargs(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, vector<Token> &argsFunc) {
    map<string, Valor> args;
    int fin = 1, i = 0;
    for (; it != fin_it; it++) {
        if (it->getValor() == ")" && fin - 1 == 0)
            break;
        else if (it->getValor() == "(")
            fin++;
        else if (it->getValor() == ")")
            fin--;
        else if (it->getValor() == ",")
            continue;
        else {
            Valor tk;
            if (next(it)->getValor() == "=") {
                tk = *it;
                bool flag = false;

                for (auto arg : argsFunc) {
                    flag = arg.getValor() == it->getValor();
                    if (flag)
                        break;
                }
                if (!flag)
                    throw ArgumentError(it->getValor(), it->getLinea());
                it += 2;
            } else
                tk = argsFunc[i++];

            if (args.find(tk.getValor()) != args.end())
                throw TypeError("El argumento `" + tk.getValor() + "` recibe multiples valores", it->getLinea());

            args[tk.getValor()] = *it;
        }
    }
    return args;
}

void Evaluadores::eval_func(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars) {
    Token nombre_fun = *(++it);
    vector<Token> contenido, returned, args;

    if ((++it)->getValor() != "(")
        throw TokenError(*it);
    it++;
    bool add_args = true, end_args_fun = false;
    for (; it != fin_it; it++) {
        if (!end_args_fun && it->getValor() == ")") {
            add_args = false, end_args_fun= true;
            if (next(it)->getValor() != ":" && next(it, 2)->getTipo() != START_BLOCK && next(it, 3)->getTipo() != END)
                throw TokenError(it->getLinea());
            it += 4;
        }
        if (it->getValor() == ",")
            continue;
        else if (add_args)
            args.push_back(*it);
        else if (it->getValor() == "retornar") {
            for (; it != fin_it; it++) {
                if (it->getTipo() == END_BLOCK)
                    break;
                returned.push_back(*it);
            }
            if (it->getTipo() != END_BLOCK && (++it)->getTipo() != END)
                throw TokenError(it->getLinea());
            else
                break;
        } else if (it->getTipo() == END_BLOCK) {
            if ((++it)->getTipo() != END)
                throw TokenError(it->getLinea());
            else
                break;
        } else
            contenido.push_back(*it);
    }
    Funcion func = Funcion(nombre_fun.getValor(), contenido, args);
    vars.agregar(nombre_fun.getValor(), func);
}

Token Evaluadores::call_new_funcion(Funcion &func, void (*runner)(vector<Token> &, Variables &), Variables &args) {
    vector<Token> contenido = func.getContenido(), returned = func.getSentReturn();
    runner(contenido, args);
    vector<Token>::iterator it = returned.begin(), fin_it = returned.end();
    if (returned.size() > 0) {
        Stack stack = eval_expresion(it, fin_it, args, false);
        auto token = stack.get_stack();
        if (token.getLinea() != -1)
            return token;
    }
    return Token("NADA", contenido.back().getLinea());
};

Token Evaluadores::call_native_func(Token &token_func, vector<Valor> &args) {
    string name_func = token_func.getValor();
    int linea = token_func.getLinea();
    return Funciones_Nativas::call(name_func, args, linea);
}

Token Evaluadores::llamar_funcion(Token token_func, vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars) {
    Funcion func = vars.getFunc(token_func.getValor());

    if (!func.getNombre().empty()) {
        vector<Token> funcArgs = func.getArgs();
        map<string, Valor> args = procesar_kwargs(++it, fin_it, funcArgs);
        Variables scope_vars = args;
        return call_new_funcion(func, run, scope_vars);
    }
    vector<Valor> args = procesar_simple_args(++it, fin_it, vars);
    return call_native_func(token_func, args);
}

Array Evaluadores::eval_arreglo(vector<Token>::iterator &it, vector<Token>::iterator &end, Variables &vars) {
    Token token;
    int i = 0;
    vector<Token> arreglo;
    for(; it != end; it++){
        token = *it;
        if (token.getValor() == ",")
            continue;
        if (token.getValor() == "[") {
            ++i;
            continue;
        }
        if (token.getValor() == "]") {
            if (i - 1 == 0) {
                i--;
                break;
            }
            continue;
        }
        if(token.getTipo() == IDENTIFICADOR) token = vars[token.getValor()];
        arreglo.push_back(token);
    }
    if (i != 0)
        throw EOLError(token);
    return arreglo;
}

Stack Evaluadores::eval_expresion(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars, bool block) {
    Token token;
    Stack myStack = Stack(fin_it);

    for (; it != fin_it; it++) {
        token = *it;
        if (block && token.getValor() == ":")
            break;
        if (token.getTipo() == END)
            break;
        if (token.getTipo() == IDENTIFICADOR && next(it)->getValor() == "(") {
            it++;
            token = llamar_funcion(token, it, fin_it, vars);
        } else if (token.getTipo() == IDENTIFICADOR)
            token = vars[token.getValor()];
        else if (token.getValor() == "[") {
            auto arr = eval_arreglo(it, fin_it, vars);
            myStack.agregar(Valor(arr), it);
            continue;
        }
        myStack.agregar(Valor(token), it);
    }
    if (block && it->getValor() != ":")
        throw EOLError(it->getLinea());
    else if (!block && it->getTipo() != END)
        throw EOLError(it->getLinea());
    // cout << myStack.get_stack() << endl;
    return myStack;
}

void Evaluadores::eval_condicion(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars) {
    it++;
    Stack stack = eval_expresion(it, fin_it, vars, true);
    Valor expr = stack.get_stack();

    it++;
    if (it->getTipo() != START_BLOCK)
        throw TokenError(it->getLinea());
    it++;
    if (it->getTipo() != END)
        throw EOLError(it->getLinea());
    it++;

    vector<Token> tmp_tokens;
    int cont_start = 1;
    for (; it != fin_it; it++) {
        if (it->getTipo() == END_BLOCK && !(cont_start - 1))
            break;
        else if (it->getTipo() == START_BLOCK)
            cont_start++;
        else if (it->getTipo() == END_BLOCK)
            cont_start--;
        if (expr)
            tmp_tokens.push_back(*it);
    }
    it++;
    if (expr)
        run(tmp_tokens, vars);
}

vector<Token> Evaluadores::procesar_bloque(vector<Token>::iterator &it, vector<Token>::iterator &fin) {
    vector<Token> bloque;
    int cont_start = 1;
    for (; it != fin; it++) {
        if (it->getTipo() == END_BLOCK && !(cont_start - 1)) {
            it++;
            break;
        } else if (it->getValor() == ":")
            cont_start++;
        bloque.push_back(*it);
    }
    return bloque;
}

void Evaluadores::eval_for(vector<Token>::iterator &it, vector<Token>::iterator &fin_it, Variables &vars) {
    Token var_control = *(++it);
    int linea_var_control = var_control.getLinea();
    vector<Token> contenido_for;
    it++;

    if (it->getValor() == "desde") {
        int inicio, fin;
        it++;
        inicio = it->getTipo() == IDENTIFICADOR ? vars[it->getValor()].parse<int>() : it->parse<int>();
        Token tk = Token(to_string(inicio), linea_var_control);
        vars.agregar(var_control.getValor(), tk);
        it += 2;
        fin = it->getTipo() == IDENTIFICADOR ? vars[it->getValor()].parse<int>() : it->parse<int>();
        it += 2;

        contenido_for = procesar_bloque(it, fin_it);

        if (contenido_for.empty())
            return;
        for (; inicio < fin; inicio++) {
            ++vars[var_control.getValor()];
            run(contenido_for, vars);
        }
        vars.eliminar(var_control.getValor());
    } else if (it->getValor() == "en") {
        Token iterable_ = *(++it);
        vector<Token> iterable;

        if (iterable_.getValor() == "[") {
            iterable = eval_arreglo(it, fin_it, vars).getContenido();
        } else if (iterable_.getTipo() == STRING) {
            string valor = iterable_.getValor();
            for (char c : valor)
                iterable.push_back(Token('"' + string(1, c) + '"', iterable_.getLinea()));
        }

        it += 2;
        contenido_for = procesar_bloque(it, fin_it);

        if (contenido_for.empty())
            return;
        for (auto elemento : iterable) {
            vars.agregar(var_control.getValor(), elemento);
            run(contenido_for, vars);
        }
    }
}

void Evaluadores::eval_identifier(vector<Token>::iterator &it_pgma, vector<Token>::iterator &fin_it, Variables &variables) {
    Token tk = *it_pgma;

    if (next(it_pgma)->getTipo() == ASIGNACION) {
        it_pgma += 2;
        Stack stack = eval_expresion(it_pgma, fin_it, variables);
        auto expr = stack.get_stack();
        if((it_pgma + 1)->getTipo() == END ){
            variables.agregar(tk.getValor(), expr);
            if(it_pgma + 1 != fin_it) it_pgma++;
            return;
        }

        if (expr.getLinea() != -1)
            variables.agregar(tk.getValor(), expr);
        else {
            Valor val = Array(stack.get_array());
            variables.agregar(tk.getValor(), val);
        }
    }
    else if (next(it_pgma)->getValor() == "(")
        llamar_funcion(tk, ++it_pgma, fin_it, variables);
}

void Evaluadores::run(vector<Token> &pgma, Variables &variables) {
    using TokenHandler = std::function<void(vector<Token>::iterator &, vector<Token>::iterator &, Variables &)>;
    static const std::unordered_map<int, TokenHandler> tokenHandlers = {
        // {IMPORTACION, &eval_import},
        {IDENTIFICADOR, &eval_identifier},
        {CONDICION, &eval_condicion},
        {FUNCION, &eval_func},
        {FOR, &eval_for},
    };

    vector<Token>::iterator iter = pgma.begin(), iter_end = pgma.end();

    for (; iter != iter_end; iter++) {
        auto it = tokenHandlers.find(iter->getTipo());
        if (it != tokenHandlers.end()) {
            auto handler = it->second;
            handler(iter, iter_end, variables);
        }
    };
}
