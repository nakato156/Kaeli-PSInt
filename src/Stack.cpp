#include "cabeceras/definiciones.h"
#include "cabeceras/Stack.h"
#include "cabeceras/Exceptions.h"
#include "Env.cpp"

using namespace std;
using namespace Exceptions;

Stack::Stack() = default;
Stack::Stack(vector<Token> &tokens_): tokens(tokens_) { }
void Stack::add_valores(Token tk){ valores.push_back(tk); }
void Stack::add_operadores(Token tk){ operadores.push_back(tk); }
Token Stack::operar(Token val1, string op, Token val2){
    if(operaciones_aritmeticas.find(op) != operaciones_aritmeticas.end()) return operaciones_aritmeticas[op](val1, val2);
    else if(operaciones_igualdad.find(op) != operaciones_igualdad.end()) return operaciones_igualdad[op](val1, val2);
    throw TokenError(val2.getLinea());
}

void Stack::agregar(Array arr, vector<Token>::iterator &it){
    Token tk = *next(it);
    if(tk.getValor() == "=" && next(it)->getValor() == "="){
        return;
    }
    else if(tk.getTipo() == END) { 
        array_tks = arr.getContenido();
    }
    else throw TypeError("array", it->getNombreTipo(), it->getLinea());
}

void Stack::agregar(Token tk, vector<Token>::iterator &it){
    Token val1, val2, res;
    string op;
    if(tk.getValor() == "<" || tk.getValor() == ">" || tk.getValor() == "=") {
        val2 = valores.back(); valores.pop_back();
        if(valores.size() == 0 ) tmp_val.push_back(val2);
        else{
            val1 = valores.back(); valores.pop_back();
            op = operadores.back().getValor(); operadores.pop_back();
            
            tmp_val.push_back(operar(val1, op, val2));
        }
        operadores.push_back(tk); 
        if(next(it)->getValor() == "=") {
            it++; operadores.push_back(*it);
        }
    }
    else if(tk.getTipo() != OPERADOR) valores.push_back(tk);
    else {
        if(operadores.size() == 0) operadores.push_back(tk);
        else {
            if(tk.getPrecedencia() > operadores.back().getPrecedencia()){
                if(operadores.back().getPrecedencia() == -1) {
                    operadores.push_back(tk);
                    valores.push_back(*(++it));
                }else {
                    if(it+1 == tokens.end()) exit(EXIT_FAILURE);
                    it++;
                    val1 = valores.back(); valores.pop_back();
                    val2 = *it;
                    op = tk.getValor();

                    res = operar(val1, op, val2);
                    valores.push_back(res);
                }
            }
            else {
                val1 = *(valores.begin()); valores.erase(valores.begin());
                val2 = *(valores.begin()); valores.erase(valores.begin());
                op = operadores.back().getValor(); operadores.pop_back();

                res = operar(val1, op, val2);
                operadores.push_back(tk);
                valores.insert(valores.begin(), res);
            }
        }
    }
}

Array Stack::get_array(){ return array_tks; };

Token Stack::get_stack(){
    string op;

    if(operadores.size() == 0) {
        if(valores.size() != 0) return valores[0];
        return Token("NADA", -1);
    }
    else{
        vector<Token>::iterator it_op; 
        Token token;
        for (it_op = operadores.begin(); it_op != operadores.end(); it_op++)
        {
            op = it_op->getValor();
            if(op == ">" || op == "<" || op == "="){
                if(!tmp_val.size()) throw TokenError(*it_op);
                tmp_val.push_back(*it_op); 
                if(next(it_op)->getValor() == "=") tmp_val.push_back(*(++it_op));
            }else{
                Token val2 = *(valores.begin()); valores.erase(valores.begin());
                Token val1 = *(valores.begin()); valores.erase(valores.begin());

                token = operaciones_aritmeticas[op](val1, val2);
                valores.insert(valores.begin(), token);
            }
        }

        if(tmp_val.size() > 0) {
            tmp_val.push_back(valores[0]);

            for(it_op = tmp_val.begin(); it_op != tmp_val.end(); it_op++){
                Token val1 = *it_op;
                op = (++it_op)->getValor();
                if(next(it_op)->getValor() == "=") op += (++it_op)->getValor();
                token = operar(val1, op, *(++it_op));
            }
            return token;
        } else return valores[0];
    }
}
