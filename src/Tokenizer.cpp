#include "cabeceras/Tokenizer.h"
using namespace std;

Tokenizer::Tokenizer() = default;
int Tokenizer::size(){ return tokens.size(); }
Tokenizer::Tokenizer(vector<string> lineas) //Para archivos.
{
    vector<Token> pgma;
    int num_linea = 1;
    
    for(auto linea_ = lineas.begin(); linea_ != lineas.end(); linea_++){
        string linea = *linea_;   
        int i = 0, inicio;
        int largo = linea.size();

        while(i < largo){
            string token = "";

            if (linea[i] == '\n') num_linea++;

            while(linea[i] == ' ' && i < largo) i++;
            if(i == largo) break;
            
            char car = linea[i];
            if(esOperador(car, Operadores, Operadores.size())){
                token.push_back(linea[i]);
                i++;
            }else if (car == '"' || car == '\''){
                inicio = i;
                i++;
                while(i < largo && linea[i] != car) i++;
                token = linea.substr(inicio, i - inicio + 1);
                i++;
            } else {
                inicio = i;
                i++;
                while (i < largo && !esOperador(linea[i], Operadores, Operadores.size()) && linea[i] != ' ') ++i;
                token = linea.substr(inicio, i - inicio), num_linea;
            }
            pgma.push_back(Token(token, num_linea));
        }
        num_linea++;
    }
    tokens = pgma;
}

vector<Token> Tokenizer::getTokens(){ return tokens; }

Token Tokenizer::get(){
    Token primero = tokens[0];
    tokens.erase(tokens.begin());
    return primero;
}

Token Tokenizer::get(int n){
    Token primero;
    for(int i = 0; i < n; i++){
        primero = tokens[0];
        tokens.erase(tokens.begin());
    }
    return primero;
}

Token Tokenizer::operator[](int index){ return tokens[index]; }