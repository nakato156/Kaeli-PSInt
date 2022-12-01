#include "Valor.cpp"
#include "Stack.cpp"
#include "Funcion.cpp"
#include "Tokenizer.cpp"
#include "./Funciones_nativas.cpp"

using namespace std;
using namespace Nativo;
using namespace Exceptions;

namespace Evaluadores
{   
    class Variables {
    private:
        map<string, Valor> arrays;
        map<string, Token> variables;
        map<string, Funcion> funciones;
    public:
        Variables() = default;
        
        int size(){ return variables.size(); }
        
        void agregar(string nombre, Valor arr){ arrays[nombre] = arr; }
        void agregar(string nombre, Token token) { variables[nombre] = token; }
        void agregar(string nombre, Funcion func) { funciones[nombre] = func; }
        
        Funcion getFunc(string nombre);
        Valor getArr(string nombre){
            if(arrays.find(nombre) != arrays.end()) return arrays[nombre];
            throw NameError(nombre);
        };

        Token operator [](const string nombre) { 
            if(variables.find(nombre) != variables.end()) return variables[nombre];
            else if(arrays.find(nombre) != arrays.end()) return Token("NADA", -1);
            throw NameError(nombre);
        }

        friend ostream& operator <<(ostream &os, const Variables &vars){
            os << "{" << endl;
            for(auto &item: vars.variables) 
                os << "\t" << item.first << ": " << item.second << "," << endl;
            for(auto &item: vars.arrays) 
                os << "\t" << item.first << ": " << item.second << "," << endl;
            for(auto &item: vars.funciones) 
                os << "\t" << item.first << ": " << item.second << "," << endl;
            os << "}" << endl;
            return os;
        }
    };
    
    void run(vector<Token>&, Variables&);
    Stack eval_expresion(vector<Token>::iterator&, vector<Token>&, Variables&, bool);
    
    Funcion Variables::getFunc(string name){ return funciones[name]; }
    
    Token call_funcion(Funcion func, void(*runner)(vector<Token>&, Variables&), Variables args){
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

    Token call_native_func(Token token_func, vector<Token> &args, Variables &vars){
        vector<Token> parse_args;
        string name_func = token_func.getValor();
        int linea = token_func.getLinea();
        for(auto var: args)
            parse_args.push_back(var.getTipo() == IDENTIFICADOR ? vars[var.getValor()] : var);
        return Funciones_Nativas::call(name_func, parse_args, linea);
    }

    vector<Token> procesar_args(vector<Token>::iterator &it, vector<Token> &tokens){
        vector<Token> args;
        int fin = 1;
        for(; it != tokens.end(); it++){
            if(it->getValor() == ")" && fin - 1 == 0) break;
            else if(it->getValor() == "(") fin++;
            else if(it->getValor() == ")") fin--;
            else if(it->getValor() == ",") continue;
            else args.push_back(*it);
        }
        return args;
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
            if(add_args) args.push_back(*it);
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
            if(token.getTipo() == IDENTIFICADOR) token = vars[token.getValor()];
            else if(token.getValor() == "[") {
                auto arr = eval_arreglo(it, tokens, vars);
                myStack.agregar(arr, it);
                continue;
            }
            myStack.agregar(token, it);
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
            if(it->getTipo() == END_BLOCK && !cont_start - 1) break;
            else if(it->getTipo() == START_BLOCK) cont_start++;
            else if(it->getTipo() == END_BLOCK) cont_start--;
            if(expr) tmp_tokens.push_back(*it);
        }
        it++;
        if(expr) run(tmp_tokens, vars);
    }

    void run(vector<Token> &pgma, Variables &variables){
        vector<Token>::iterator it_pgma;
        for(it_pgma = pgma.begin(); it_pgma != pgma.end(); it_pgma++){
            Token tk = *it_pgma;
            if(tk.getTipo() == IDENTIFICADOR && next(it_pgma)->getTipo() == ASIGNACION){
                it_pgma+= 2;
                Stack stack = eval_expresion(it_pgma, pgma, variables);
                auto expr = stack.get_stack();
                if(expr.getLinea() != -1) variables.agregar(tk.getValor(), expr);
                else variables.agregar(tk.getValor(), Valor(Array(stack.get_array())));
            }
            else if (tk.getTipo() == IDENTIFICADOR && next(it_pgma)->getValor() == "(") {
                it_pgma++;
                vector<Token> args = procesar_args(++it_pgma, pgma);
                Funcion func = variables.getFunc(tk.getValor());
                vector<Token> funcArgs = func.getArgs();
                Variables scope_vars;

                for(int i = 0; i < funcArgs.size(); i++) scope_vars.agregar(funcArgs[i].getValor(), args[i]);
                if(!func.getNombre().empty()) call_funcion(func, run, scope_vars);
                else call_native_func(tk, args, variables);
            }
            else if (tk.getTipo() == CONDICION) eval_condicion(it_pgma, pgma, variables);
            else if (tk.getTipo() == FUNCION) eval_func(it_pgma, pgma, variables);
        }
    }

} 
