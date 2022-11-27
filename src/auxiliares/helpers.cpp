#ifndef helpers
#define helpers
#include <iostream>

using namespace std;

namespace Helpers
{
 bool validIdentificador(string token) {
   for(int i = 0; i < token.size(); i++) {
      if(token[i] == ' ') return false;
   }
   return true;
 }

 bool esOperador(char c, string operadores, int size){
   for(int i = 0; i < size; i++) {
      if(c == operadores[i]) return true;
   }
   return false;
 }

 bool esEntero(string str){
    for (char const &c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
 }

 bool esIdentificador(string str){
    if(!isdigit(str[0]) || str[0]  == '_') return true;
    return false;
 }

 string trim(string str){
   while(str[0] == ' ') str = str.substr(1);
   while(str[str.size() - 1] == ' ') str = str.substr(0, str.size() - 1);
   return str;
 }
}
#endif