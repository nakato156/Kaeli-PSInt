# Kaeli-PSInt

Kaeli-PSInt Es un nuevo interprete con nueva sintaxis en español, combinamos un poco de pascal, python y c en este es un nuevo pseudo-lenguaje.<br>

Esta destinado para los estudiante, para que se familierizen en el mundo de la programación, y puedan crear su propias logica.
## ¿Como compilarlo?:

Si tienes gcc(mingw en windows) y tambien la herramienta make puedes aprovechar y usar de una nuestro makefile y hacer la compilación sin mucho problemas, si nó puedes usar tu compilador que mas te guste.<br/>
Para descargar gcc y make:
- En linux solo debemos instalar "build-essential" que contiene ambos paquete:
```
sudo apt install build-essential -y
```
Y despues hacer:

```
make
```
- En windows solo debemos instalar "msys2" que contiene ambos paquete:
msys2: Lo puedes descargar he instalar desde la [pagina oficial](https://www.mingw-w64.org/downloads/#msys2).<br/>

Y despues hacer:
```
mingw32-make
```
Si no te funciona pruba poner en la variable de entorno la dirección de mingw32.
## Sintaxis:

Para asignar una variable elegimos la forma de python:
```lang-python
number=10;//Asignamos una variable entera.
float=1.4;//Asignamos una variable flotante.
string="Hola mundo";//Asignamos una variable string.
Array=[1,2,3,4];//Asignamos un array de numero.
```
Y mostramos el valor de la variable:
```
imprimir("number: ");//Imprimir es una funcion que muestra la salida del programa.
imprimir(number);
```
Todos los lenguajes debe tener una forma de hacer condiciones, este lenguaje no es la excepción:
```
si number==10:
START;
imprimir("Si, number es igual a 10.");
END;
```
Nota: START; es el incio, y END; es el final del bloque.
## Uso:
Para llamar al interprete no hace falta pasar ningun argumento, pero si quieres hacer que interprete un archivo se llama al interprete y le pasas la url de ese archivo:
```
REM CMD Windows:
Kaeli-PSInt.exe url_of_file.ae
```
```
# bash Linux:
./Kaeli-PSInt url_of_file.ae
```
## Errores:
* Cuando usas una variable sin definir causa un error que cierra el programa.
* Cuando se anida muchos if en el interprete causa un error desconocido.
## Futuras actualizaciones:
* Se quiere agregar color a los errores y un poco al interprete, por lo que se usara la biblioteca ncurses para ello.