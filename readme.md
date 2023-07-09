# Kaeli-PSInt

Kaeli-PSInt Es un nuevo intérprete con nueva sintaxis en español y basado en python, creando así este nuevo pseudo-lenguaje.

Está destinado a estudiantes, para que se familiaricen con el mundo de la programación y puedan crear sus propias lógicas.

## Compilación

Con CMake 3.13 o más reciente y asegurarse de tener disponitble c++20 o superior:

- Ejecuta el archivo `build.bat` en Windows o `build.sh` en Linux y el proyecto se compilará en la carpeta `build`.

- O crea la carpeta donde quieras compilar el proyecto y ejecuta los siguientes comandos.

Construye el proyecto con:
```
cmake -S ruta/a/la/fuente -B ruta/al/proyecto/compilado
```

Compilalo con:
```
cmake -S ruta/a/la/fuente --build ruta/al/proyecto/compilado --config Release
```

### Manualmente

Si tienes gcc (mingw en Windows) y también la herramienta make puedes aprovechar y usar nuestro makefile y hacer la compilación sin muchos problemas, sino puedes usar tu compilador que más te guste.<br/>

Para descargar gcc y make:
- En linux solo debemos instalar "build-essential" que contiene ambos paquete:
    ```
    sudo apt install build-essential -y
    ```
    Y después hacer:

    ```
    make
    ```
- En Windows solo debemos instalar "msys2" que contiene ambos paquetes: Lo puedes descargar he instalar desde la [página oficial](https://www.mingw-w64.org/downloads/#msys2).<br/>

    Y después hacer:
    ```
    mingw32-make
    ```
    O:
    ```
    make
    ```
    Si no funciona, prueba poner en la variable de entorno con la dirección de la carpeta de mingw32.
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
imprimir("Si, number es igual a 10.");
END;
```
Nota: `END;` indica el final del bloque.

También existe el típico ciclo `for`, que tiene 2 variantes

- iterar en un rango

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

- iterar en un iterable

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

* Windows:
    ```
    Kaeli-PSInt.exe url_of_file.ae
    ```

* Linux
    ```
    ./Kaeli-PSInt url_of_file.ae
    ```

## Futuras actualizaciones:
* Se quiere agregar color a los errores y un poco al intérprete.
* Implementación del bucle `while`