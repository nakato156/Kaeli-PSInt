.PHONY: clear

IF_DEBUG =
CXXFLAG =-std=c++20
SRC=./src
URL_OBJ=./bin/OBJ
DELETED_OBJS=DEL /F/Q/S "bin/obj/"
MAIN_OBJ=$(URL_OBJ)/main.o
MAIN_BIN =./main.exe
CXX=g++
SRCS=$(wildcard $(SRC)/*.cpp)
ARRAY_O=$(URL_OBJ)/Array.o
ENV_O=$(URL_OBJ)/Env.o
EVALUADORES_O=$(URL_OBJ)/Evaluadores.o
EXCEPTION_O=$(URL_OBJ)/Exceptions.o
FUNCION_O=$(URL_OBJ)/Funcion.o
FUNCIONES_NATIVAS_O=$(URL_OBJ)/Funciones_nativas.o
NATIVO_O=$(URL_OBJ)/Nativo.o
STACK_O=$(URL_OBJ)/Stack.o
TOKEN_O=$(URL_OBJ)/Token.o
TOKENIZER_O=$(URL_OBJ)/Tokenizer.o
VALOR_O=$(URL_OBJ)/Valor.o
VARIABLES_O=$(URL_OBJ)/Variables.o
OBJ_S =$(ARRAY_O) $(ENV_O) $(EVALUADORES_O) $(EXCEPTION_O) $(FUNCION_O) \
        $(FUNCIONES_NATIVAS_O) $(NATIVO_O) $(STACK_O) $(TOKEN_O) \
        $(TOKENIZER_O) $(VALOR_O) $(VARIABLES_O)

ifeq ($(strip $(OS)),Linux)
	MAIN_BIN="./main"
	DELETED_OBJS=rm -rf ./bin/*.o
endif

ifdef $(IF_DEBUG)
	CXXFLAG=$(CXXFLAG) -g
endif
all: $(MAIN_BIN)

$(MAIN_BIN) : $(MAIN_OBJ) $(OBJ_S)
	@echo "\e24[Compilando el binario."
	$(CXX) $(CXXFLAG) $(MAIN_OBJ) $(OBJ_S) -o $(MAIN_BIN) 2> logs.txt

#Descartamos esto porque genera error en el linker que ya no tengo animo de solucionar.
$(MAIN_OBJ) : ./main.cpp
	@echo "Compilando archivo objeto $@"
	$(CXX) $(CXXFLAG) -c -o $@ $< 2>logs_obj.txt

$(OBJ_S) : $(SRCS)
	@echo "compilando archivo objeto $@"
	$(CXX) $(CXXFLAG) -c -o $@ $< 2>logs_obj.txt

clear:
	@ECHO "ELiminando archivos objs..."
	$(DELETED_OBJS)
