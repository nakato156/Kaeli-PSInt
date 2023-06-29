#include "helpers.h"

#include <iostream>

#ifdef WIN32
#include <Windows.h>
#endif

using namespace std;

bool Helpers::validIdentificador(string token) {
    for (int i = 0; i < token.size(); i++) {
        if (token[i] == ' ')
            return false;
    }
    return true;
}

bool Helpers::esOperador(char c, string operadores, int size) {
    for (int i = 0; i < size; i++) {
        if (c == operadores[i])
            return true;
    }
    return false;
}

bool Helpers::esEntero(string str) {
    for (char const &c : str) {
        if(c == '-' || c == '+') continue;
        if (!isdigit(c))
            return false;
    }
    return true;
}

bool Helpers::esIdentificador(string str) {
    if (!isdigit(str[0]) || str[0] == '_')
        return true;
    return false;
}

string Helpers::trim(string str) {
    while (str[0] == ' ')
        str = str.substr(1);
    while (str[str.size() - 1] == ' ')
        str = str.substr(0, str.size() - 1);
    return str;
}

bool Helpers::consolaPropia(){
#ifdef WIN32
    HWND consoleWnd = GetConsoleWindow();
    DWORD dwProcessId;
    GetWindowThreadProcessId(consoleWnd, &dwProcessId);
    return GetCurrentProcessId()==dwProcessId;
#else
    return true;
#endif
}