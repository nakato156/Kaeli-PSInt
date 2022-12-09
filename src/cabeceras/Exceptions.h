#ifndef Exceptions_h
#define Exceptions_h
#include <iostream>
#include <string>

namespace Exceptions
{
    class BaseError : public std::exception
    {
    protected:
        int num_linea;
    public:
        BaseError();
        int getLinea();
        static int getLinea(BaseError);
    };

    class EOLError : public BaseError
    {
    private:
        std::string message = "\rEOL Error en:"; 
    public:
        EOLError();
        EOLError(int);
        const char * what() const throw();
    };

    class TokenError : public BaseError
    {
    private:
        std::string message = "\rToken no reconocido";
    public:
        TokenError();
        TokenError(int);
        const char * what() const throw();
    };

    class TypeError : public BaseError
    {
    private:
        std::string message;
    public:
        TypeError();
        TypeError(std::string, int);
        TypeError(std::string, std::string, int);
        const char * what() const throw();
    };

    class NameError : public BaseError {
    private:
        std::string message;
    public:
        NameError();
        NameError(std::string);
        NameError(std::string, int);
        const char * what() const throw();
    };

    class ArgumentError : public BaseError {
    private:
        std::string message;
    public:
        ArgumentError();
        ArgumentError(std::string, int);
        const char * what() const throw();
    };

}
#endif