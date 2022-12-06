# Kaeli-PSInt

Kaeli-PSInt Es un nuevo intérprete con nueva sintaxis en español, combinamos un poco de pascal, python y c en este es un nuevo pseudo-lenguaje.<br>

Está destinado para los estudiantes, para que se familiaricen en el mundo de la programación, y puedan crear sus propias lógicas.
## ¿Como compilarlo?:

Si tienes gcc(mingw en windows) y también la herramienta make puedes aprovechar y usar de una nuestro makefile y hacer la compilación sin muchos problemas, sino puedes usar tu compilador que más te guste.<br/>
Para descargar gcc y make:
- En linux solo debemos instalar "build-essential" que contiene ambos paquete:
```
sudo apt install build-essential -y
```
Y después hacer:

```
make
```
- En windows solo debemos instalar "msys2" que contiene ambos paquete:
msys2: Lo puedes descargar he instalar desde la [página oficial](https://www.mingw-w64.org/downloads/#msys2).<br/>

Y después hacer:
```
mingw32-make
```
Si no te funciona, prueba poner en la variable de entorno con la dirección de la carpeta de mingw32.
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
imprimir("number: ");//Imprimir es una función que muestra la salida del programa.
imprimir(number);
```
Todos los lenguajes debe tener una forma de hacer condiciones, este lenguaje no es la excepción:
```
si number==10:
START;
imprimir("Si, number es igual a 10.");
END;
```
Nota: START; es el inicio, y END; es el final del bloque.
## Uso:
Para llamar al intérprete no hace falta pasar ningún argumento, pero si quieres hacer que interprete un archivo se llama al intérprete y le pasas la URL de ese archivo:
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
* Cuando se anida muchos if en el intérprete causa un error desconocido.
## Futuras actualizaciones:
* Se quiere agregar color a los errores y un poco al intérprete, por lo que se utilizara la biblioteca ncurses para ello.