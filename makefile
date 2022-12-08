
OBJ=
MAIN_BIN="./main.exe"
IF_DEBUG=
CXXFLAG=-Wall

ifeq ($(strip $(OS)),Linux)
	MAIN_BIN="./main"
endif

ifdef $(IF_DEBUG)
	CXXFLAG=$(CXXFLAG) -g
endif

$(MAIN_BIN) : ./main.cpp
	g++ $(CXXFLAG) -std=c++20 -o $(MAIN_BIN) ./main.cpp $(OBJ)

.PHONY: clean
clean:
	rm -rf ./bin/*.o