#ifndef definiciones
#define definiciones
#include <string>

#define END 0
#define IDENTIFICADOR 1
#define OPERADOR 2
#define ENTERO 3
#define BOOL 4
#define STRING 5
#define NADA 6
#define ASIGNACION 7
#define CONDICION 8
#define FUNCION 9
#define ARRAY 10
#define FLOAT 11
#define START_BLOCK 12
#define END_BLOCK 13
#define FOR 14
#define WHILE 15
#define MSG_INIT "Bienvenido."

inline std::string Operadores = "=(),.+-*/<>[];:!~";
inline const char* VERSION_PROGRAM="V1.0";
#endif