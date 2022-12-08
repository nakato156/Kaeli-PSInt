
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
	g++ $(CXXFLAG) -o $(MAIN_BIN) ./main.cpp $(OBJ)

.PHONY: clean
clean:
	rm -rf ./bin/*.o