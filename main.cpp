#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "src/Evaluadores.cpp"

using namespace std;
using namespace Exceptions;
using namespace Evaluadores;

string filename = "file.ae";

int main(int argc, char *argv[]){
	string linea;
	ifstream file(filename.c_str());

	vector<string> lineas;
	vector<Token> pgma;

	while(getline(file, linea)) lineas.push_back(linea);
	file.close();
	
	try {
		pgma = Tokenizer(lineas).getTokens();

		Variables variables;

		run(pgma, variables);
		if(argc >= 2 && string(argv[1]) == "dev") cout << variables;
	} catch(const BaseError& e) {
		int num_linea = e.getLinea(e);
    	cerr << e.what() << lineas[num_linea] << endl;
        exit(EXIT_FAILURE);
    }
	return 0;
}