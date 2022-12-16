#pragma once

#include <map>
#include <unordered_map>
#include <string>

#include "Valor.h"
#include "Token.h"
#include "Funcion.h"

class Variables {
  private:
    std::map<std::string, Valor> variables;
    std::unordered_map<std::string, Funcion> funciones;

  public:
    Variables() = default;
    Variables(std::map<std::string, Valor> &vars);
    int size();

    void agregar(const std::string &nombre, Valor &arr);
    void agregar(const std::string &nombre, Token &token);
    void agregar(const std::string &nombre, Funcion &func);

    void eliminar(const std::string &nombre);

    Funcion& getFunc(const std::string &nombre);

    Valor& operator[](const std::string &nombre);

    friend std::ostream &operator<<(std::ostream &os, const Variables &vars);
};