#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include "src/Evaluadores.cpp"

#define MAX_LONG_LINEA 500

using namespace std;
using namespace Exceptions;
using namespace Evaluadores;

void config_all(vector<string> opcions){

}

int interprete(){
	int sub = 0;	//para cambiar de >> a .. cuando hay una condición.
	char c_linea[MAX_LONG_LINEA];
	Variables vars;
	vector<Token> pgma;
	vector<string> lineas;
	cout << MSG_INIT << endl << "Version: " << VERSION_PROGRAM << endl;
	
	while (true)
	{
		if (!sub) // No esta anidando nada.
		{
			cout << ">> ";
		}
		else // Esta anidando algo.
		{
			cout << "...";
		}
		try
		{
			cin.getline(c_linea, MAX_LONG_LINEA);
			if (strstr(c_linea,":")!=NULL){//Vemos si hay anidamiento.
				sub += 1;
			}else if(strstr(c_linea,"END;")!=NULL || strstr(c_linea,"END")!=NULL){//Pongo END; || END porque no consique END; como una cadena parecida a END.
				if(sub <= 0){//Espera no hubo nada que desanidar ;(
					cout << "ERROR \nno hay anidamiento que quitar";
					sub = 0;
					continue;
				}
				sub -= 1;
			}

			lineas.push_back(string(c_linea));
			if(sub == 0){//Podemos interpretar linea a linea.
				pgma = Tokenizer(lineas).getTokens();
				run(pgma, vars);
				lineas.clear();
			}
		}
		catch (const BaseError &e)
		{
			int num_linea = e.getLinea(e);
			cerr << e.what() << c_linea << endl;
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char *argv[])
{
	string linea;
	if (argc > 1)
	{
		vector<string> params, path_files;

		for (int i = 1; i < argc; i++)
		{
			string opcion = argv[i];
			if (opcion.find('-') == string::npos)
			{
				path_files.push_back(opcion.c_str());
				continue;
			}
			params.push_back(opcion.substr(1));
		}

		if (!path_files.empty())
		{
			ifstream file(path_files[0].c_str());
			if (!file.good())
			{
				printf("El archivo no existe, revise la ruta.");
				exit(EXIT_FAILURE);
			}

			vector<string> lineas;
			vector<Token> pgma;

			while (getline(file, linea))
				lineas.push_back(linea);
			file.close();

			try
			{
				pgma = Tokenizer(lineas).getTokens();

				Variables variables;

				run(pgma, variables);
				if(std::find(params.begin(), params.end(), "dev") != params.end()) 
					cout << variables;
				exit(EXIT_SUCCESS);
			}
			catch (const BaseError &e)
			{
				int num_linea = e.getLinea(e);
				cerr << e.what() << lineas[num_linea] << endl;
				exit(EXIT_FAILURE);
			}
		}
	}
	interprete();
	return 0;
}