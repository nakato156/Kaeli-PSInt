# Kaeli-PSInt

Kaeli-PSInt Es un nuevo intérprete con nueva sintaxis en español y basado en python, creando así este nuevo pseudo-lenguaje.<br>

Está destinado para los estudiantes, para que se familiaricen en el mundo de la programación, y puedan crear sus propias lógicas.

## ¿Como compilarlo?

Con CMake 3.13 en adelante:

Crea la carpeta donde quieres compilar el proyecto.

Construye el proyecto con:
```
cmake -B ruta/al/proyecto/compilado
```

Compilalo con:
```
cmake --build ruta/al/proyecto/compilado
```

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
number = 10;    //Asignamos una variable entera.
float = 1.4;    //Asignamos una variable flotante.
string = "Hola mundo";  //Asignamos una variable string.
Array = [1, 2, "hola", falso];      //Asignamos un array de numero.
```
Y mostramos el valor de la variable:
```
imprimir("number: "); //imprimir es una función que muestra la salida del programa.
imprimir(number);

//la función también acepta varios parámetros
imprimir("number: ", number);
```
Todos los lenguajes debe tener una forma de hacer condiciones, este lenguaje no es la excepción:
```
si number==10:
START;
imprimir("Si, number es igual a 10.");
END;
```
Nota: `START;` indica el inicio y `END;` el final del bloque.

También existe el típico ciclo `for`, que tiene 2 variantes

* iterar en un rango

Esta variante tiene como sintaxis:

```
iterar variable_control desde inicio hasta fin:
    // codigo
END;
```
Un ejemplo:
```
iterar x desde 1 hasta 10:
    imprimir(x);
END;
```

* iterar en un iterable

Existen 2 tipos de iterables, los `strings` y `arrays`.

La sintaxis de esta variante sería:

```
iterar variable_control en iterable:
    //codigo
END;
```
Un ejemplo:
```
iterar x en [1, 2 , "holas", verdadero]:
    imprimir(x);
END;
```

## Uso
El programa posee un modo interactivo, este aparece cuando se ejecuta el intérprete sin ningún argumento. Si se desea ejecutar un archivo se llama al intértprete y como primer argumento va la ubicación del archivo con extensión `ae`. Aquí un ejemplo.

* REM CMD Windows:
```
Kaeli-PSInt.exe url_of_file.ae
```

* Linux
```
./Kaeli-PSInt url_of_file.ae
```

## Futuras actualizaciones:
* Se quiere agregar color a los errores y un poco al intérprete, por lo que se utilizara la biblioteca ncurses para ello.
* Implementación del bucle `while`