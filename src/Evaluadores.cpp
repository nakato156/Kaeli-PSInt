#include "Variables.cpp"
#include "Stack.cpp"
#include "Tokenizer.cpp"
#include "Funciones_nativas.cpp"

using namespace std;
using namespace Nativo;
using namespace Exceptions;

namespace Evaluadores
{    
    void run(vector<Token>&, Variables&);
    Stack eval_expresion(vector<Token>::iterator&, vector<Token>&, Variables&, bool);
        
    Token call_new_funcion(Funcion &func, void(*runner)(vector<Token>&, Variables&), Variables &args){
        vector<Token> contenido = func.getContenido(), returned = func.getSentReturn();
        runner(contenido, args);
        vector<Token>::iterator it = returned.begin();
        if (returned.size() > 0 ) {
            Stack stack = eval_expresion(it, returned, args, false);
            auto token = stack.get_stack();
            if(token.getLinea() != -1) return token;
        }
        return Token("NADA", contenido.back().getLinea());
    };

    Token call_native_func(Token &token_func, vector<Valor> &args, Variables &vars){
        string name_func = token_func.getValor();
        int linea = token_func.getLinea();
        return Funciones_Nativas::call(name_func, args, linea);
    }

    vector<Valor> procesar_simple_args(vector<Token>::iterator &it, vector<Token> &tokens, Variables &vars){
        vector<Valor> args;
        int fin = 1, i = 0;
        for(; it != tokens.end(); it++){
            if(it->getValor() == ")" && fin - 1 == 0) break;
            else if(it->getValor() == "(") fin++;
            else if(it->getValor() == ")") fin--;
            else if(it->getValor() == ",") continue;
            
            if(it->getTipo() == IDENTIFICADOR) args.push_back(vars[it->getValor()]);
            else args.push_back(*it);
        }
        return args;
    }

    map<string, Valor> procesar_kwargs(vector<Token>::iterator &it, vector<Token> &tokens, vector<Token> &argsFunc){
        map<string, Valor> args;
        int fin = 1, i = 0;
        for(; it != tokens.end(); it++){
            if(it->getValor() == ")" && fin - 1 == 0) break;
            else if(it->getValor() == "(") fin++;
            else if(it->getValor() == ")") fin--;
            else if(it->getValor() == ",") continue;
            else {
                Valor tk;
                if(next(it)->getValor() == "=") {
                    tk = *it;
                    bool flag = false;
                    
                    for(auto arg: argsFunc) {
                        flag = arg.getValor() == it->getValor();
                        if(flag) break;
                    }
                    if(!flag) throw ArgumentError(it->getValor(), it->getLinea());     
                    it += 2;               
                } else tk = argsFunc[i++];
                
                if(args.find(tk.getValor()) != args.end()) 
                    throw TypeError("El argumento `" + tk.getValor()  + "` recibe multiples valores", it->getLinea());
                
                args[tk.getValor()] = *it;
            }
        }
        return args;
    }

    Token llamar_funcion(Token token_func, vector<Token>::iterator &it, vector<Token> &tokens, Variables &vars){
        Funcion func = vars.getFunc(token_func.getValor());
        
        if(!func.getNombre().empty()) {
            vector<Token> funcArgs = func.getArgs();
            map<string, Valor> args = procesar_kwargs(++it, tokens, funcArgs);
            Variables scope_vars = args;
            return call_new_funcion(func, run, scope_vars);
        }

        vector<Valor> args = procesar_simple_args(++it, tokens, vars);
        return call_native_func(token_func, args, vars);
    }

    void eval_func(vector<Token>::iterator &it, vector<Token> &tokens, Variables &vars){
        Token nombre_fun = *(++it);
        vector<Token> contenido, returned, args;

        if((++it)->getValor() != "(") throw TokenError(*it);
        it++;
        bool add_args = true;
        for(; it != tokens.end(); it++){
            if(it->getValor() == ")") {
                add_args = false;
                if(next(it)->getValor() != ":" && next(it, 2)->getTipo() != START_BLOCK && next(it, 3)->getTipo() != END) throw TokenError(it->getLinea());
                it+= 4;
            }
            if(it->getValor() == ",") continue;
            else if(add_args) args.push_back(*it);
            else if(it->getValor() == "retornar"){
                for(; it != tokens.end(); it++){
                    if(it->getTipo() == END_BLOCK) break;
                    returned.push_back(*it);
                }
                if(it->getTipo() != END_BLOCK && (++it)->getTipo() != END) throw TokenError(it->getLinea());
                else break;
            }else if(it->getTipo() == END_BLOCK) {
                if((++it)->getTipo() != END) throw TokenError(it->getLinea());
                else break;
            } else contenido.push_back(*it);
        }
        Funcion func = Funcion(nombre_fun.getValor(), contenido, args);
        vars.agregar(nombre_fun.getValor(), func);
    }

    Array eval_arreglo(vector<Token>::iterator &it, vector<Token> &tokens, Variables &vars){
        Token token;
        int i = 0;
        auto arreglo = Array();
        for(; it != tokens.end(); it++){
            token = *it;
            if(token.getValor() == ",") continue;
            if(token.getValor() == "[") {
                ++i;
                continue;
            }
            if(token.getValor() == "]"){
                if(i-1 == 0){
                    i--; break;
                }
                continue;
            }
            if(token.getTipo() == IDENTIFICADOR) token = vars[token.getValor()];
            arreglo.addItem(token);
        }
        if(i != 0) throw EOLError(token);
        return arreglo;
    }

    Stack eval_expresion(vector<Token>::iterator &it, vector<Token> &tokens, Variables &vars, bool block = false){
        Token token;
        Stack myStack = Stack(tokens);
        for(; it != tokens.end(); it++){
            token = *it;
            if(block && token.getValor() == ":") break;
            if(token.getTipo() == END) break;
            if(token.getTipo() == IDENTIFICADOR && next(it)->getValor() == "("){
                it++;
                token = llamar_funcion(token, it, tokens, vars);
            }
            else if(token.getTipo() == IDENTIFICADOR) token = vars[token.getValor()];
            else if(token.getValor() == "[") {
                auto arr = eval_arreglo(it, tokens, vars);
                myStack.agregar(Valor(arr), it);
                continue;
            }
            myStack.agregar(Valor(token), it);
        }
        if (block && it->getValor() != ":") throw EOLError(it->getLinea()); 
        else if (!block && it->getTipo() != END)throw EOLError(it->getLinea()); 
        return myStack;
    }

    void eval_condicion(vector<Token>::iterator &it, vector<Token> &tokens, Variables &vars){
        it++;
        Stack stack = eval_expresion(it, tokens, vars, true);
        Valor expr = stack.get_stack();
        
        it++;
        if(it->getTipo() != START_BLOCK) throw TokenError(it->getLinea());
        it++;
        if(it->getTipo() != END) throw EOLError(it->getLinea());
        it++;

        vector<Token> tmp_tokens;
        int cont_start = 1;
        for(; it != tokens.end(); it++){
            if(it->getTipo() == END_BLOCK && !(cont_start - 1)) break;
            else if(it->getTipo() == START_BLOCK) cont_start++;
            else if(it->getTipo() == END_BLOCK) cont_start--;
            if(expr) tmp_tokens.push_back(*it);
        }
        it++;
        if(expr) run(tmp_tokens, vars);
    }

    vector<Token> procesar_bloque(vector<Token>::iterator &it, vector<Token> &tokens){
        vector<Token> bloque;
        int cont_start = 1;
        for(; it != tokens.end(); it++){
            if(it->getTipo() == END_BLOCK && !(cont_start - 1)) {
                it++;
                break;
            }
            else if(it->getValor() == ":") cont_start++;
            bloque.push_back(*it);
        }
        return bloque;
    }

    void eval_for(vector<Token>::iterator &it, vector<Token> &tokens, Variables &vars){
        Token var_control = *(++it);
        int linea_var_control = var_control.getLinea();
        vector<Token> contenido_for;
        it++;

        if(it->getValor() == "desde"){
            int inicio, fin;
            it++;
            inicio = it->getTipo() == IDENTIFICADOR ? vars[it->getValor()].parse<int>() : it->parse<int>();
            Token tk = Token(to_string(inicio), linea_var_control);
            vars.agregar(var_control.getValor(), tk);
            it += 2;
            fin = it->getTipo() == IDENTIFICADOR ? vars[it->getValor()].parse<int>() : it->parse<int>();
            it+=2;

            contenido_for = procesar_bloque(it, tokens);
            
            if(contenido_for.empty()) return;
            for(; inicio < fin; inicio++){
                ++vars[var_control.getValor()];
                run(contenido_for, vars);
            }
            vars.eliminar(var_control.getValor());
        }else if (it->getValor() == "en"){
            Token iterable_ = *(++it);
            vector<Token> iterable;

            if(iterable_.getValor() == "[") 
                iterable = eval_arreglo(it, tokens, vars).getContenido();
            else if(iterable_.getTipo() == STRING){
                string valor = iterable_.getValor();
                for(char c: valor) 
                    iterable.push_back(Token('"' + string(1, c) + '"', iterable_.getLinea()));
            }
            
            it += 2;
            contenido_for = procesar_bloque(it, tokens);
            
            if(contenido_for.empty()) return;
            for(auto elemento: iterable){
                vars.agregar(var_control.getValor(), elemento);
                run(contenido_for, vars);
            }
        }


    }

    void run(vector<Token> &pgma, Variables &variables){
        vector<Token>::iterator it_pgma;
        for(it_pgma = pgma.begin(); it_pgma != pgma.end(); it_pgma++){
            Token tk = *it_pgma;

            switch (tk.getTipo())
            {
            case IDENTIFICADOR:
                if (next(it_pgma)->getValor() == "(") {
                    llamar_funcion(tk, ++it_pgma, pgma, variables);
                    break;
                }

                switch (next(it_pgma)->getTipo())
                {
                case ASIGNACION: {
                    it_pgma += 2;
                    Stack stack = eval_expresion(it_pgma, pgma, variables);
                    auto expr = stack.get_stack();
                    if(expr.getLinea() != -1) variables.agregar(tk.getValor(), expr);
                    else {
                        Valor val = Valor(Array(stack.get_array()));
                        variables.agregar(tk.getValor(), val);
                    }
                    break;
                }              
                default: break;
                }
                break;
            case CONDICION:
                eval_condicion(it_pgma, pgma, variables);
                break;
            case FUNCION:
                eval_func(it_pgma, pgma, variables);
                break;
            case FOR:
                eval_for(it_pgma, pgma, variables);
                break;
            default: break;
            }
        }
    }

} 
