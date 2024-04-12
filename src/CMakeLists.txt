
target_sources(${PROJECT_NAME} PRIVATE
	LibEstandar/Mates.cpp
	Array.cpp
	definiciones.cpp
	Env.cpp
	Evaluadores.cpp
	Exceptions.cpp
	Funcion.cpp
	Funciones_nativas.cpp
	Nativo.cpp
	Stack.cpp
	Token.cpp
	Tokenizer.cpp
	Valor.cpp
	Variables.cpp
	auxiliares/helpers.cpp
)

target_include_directories(${PROJECT_NAME}
	PUBLIC cabeceras auxiliares LibEstandar
)
