#include <iostream>
#include <fstream>
#include <string>
#include "src/Evaluadores.cpp"

#define MAX_LONG_LINEA 500

using namespace std;
using namespace Exceptions;
using namespace Evaluadores;
bool compare_sub_str(const char* str,unsigned const char c);
bool compare_sub_str(char* str_1,char* str_2);
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
			cin.getline(c_linea,MAX_LONG_LINEA);
			if (compare_sub_str(c_linea,':')){//Vemos si hay anidamiento.
				sub += 1;
			}else if (compare_sub_str(c_linea,"END")){//Pongo END; || END porque no consique END; como una cadena parecida a END.
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
	ios_base::sync_with_stdio(false);//Aumenta la velocidad de la entrada y salida estandar.
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
				cout<<"El archivo no existe, revise la ruta."<<endl;
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
unsigned int len(const char* str){
	unsigned int i=0;
	while(str[i]!='\0')
		i++;
	return i;
}
/**
 * @brief Funcion que busca la subcadena dentro de otra cadena, si str_1 < str_2 entonces str_1 es la sub-cadena. Si son iguales entonces solo compara las cadenas.
 * @param str_1 char* -- Cadena 1.
 * @param str_2 char* -- Cadena 2.
 * @return bool
*/
bool compare_sub_str(char* str_1,char* str_2){
	unsigned int i_s1=len(str_1);
	unsigned int i_s2=len(str_2);
	int c=0;//Veces que hubo coincidencia.
	char* c1=str_1;
	char* c2=str_2;
	if (i_s1==i_s2){// Como son iguales no tenemos porque buscar una sub-cadena, solo debemos ver si son iguales.
		for (int i=0;i<i_s1;i++){
			if (c1[i]!=c2[i])
				return false;
		}
		return true;
	}else if(i_s1<i_s2){//Si la cadena 1 es menos que la cadena 2 entonces la cadena 1 es la sub cadena que debemos buscar en la cadena 2.
		c1=str_2;
		c2=str_1;
		c=i_s1;
		i_s1=i_s2;
		i_s2=c;
		c=0;
	}
	for (int i=0;i<i_s1;i++){
		if (c1[i]==c2[c]){//Vemos si la sub cadena se encuentra dentro de la cadena.
			c++;
			if (c==i_s2)//Si se encuentra.
				return true;
		}else
			c=0;
	}
	return false;//no se encuentra.
}
/**
 * @brief Función que busca un char dentro de una cadena.
 * 
 * @param str  Cadena de donde buscar.
 * @param c Char que vamos a buscar.
 * @return true 
 * @return false 
 */
bool compare_sub_str(const char* str,unsigned const char c){
	for (unsigned int i=0;str[i]!='\0';i++)
		if (str[i]==c)
			return true;//Se encontró:)
	return false;//No se encontro el char:(
}