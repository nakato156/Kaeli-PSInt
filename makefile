
OBJ =
MAIN_BIN = "./main.exe"
IF_DEBUG =
CXXFLAG = -std=c++20

ifeq ($(strip $(OS)),Linux)
	MAIN_BIN="./main"
endif

ifdef $(IF_DEBUG)
	CXXFLAG=$(CXXFLAG) -g
endif

$(MAIN_BIN) : ./main.cpp
	g++ $(CXXFLAG) -o $(MAIN_BIN) -I"src/cabeceras" -I"src/auxiliares" "main.cpp" "src/Array.cpp" "src/definiciones.cpp" "src/Env.cpp" "src/Evaluadores.cpp" "src/Exceptions.cpp" "src/Funcion.cpp" "src/Funciones_nativas.cpp" "src/Nativo.cpp" "src/Stack.cpp" "src/Token.cpp" "src/Tokenizer.cpp" "src/Valor.cpp" "src/Variables.cpp" "src/auxiliares/helpers.cpp" $(OBJ)
	

.PHONY: clean
clean:
	rm -rf ./bin/*.o