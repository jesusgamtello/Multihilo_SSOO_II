# TERCERA PRACTICA SISTEMAS OPERATIVOS II

En la carpeta _utils_ podemos encontrar los diversos ficheros .txt que pueden ser usados para probar nuestra practica

En la carpeta _src_ nos encontramos los archivos fuentes en .cpp compuesto por main.cpp, el cual es nuestra clase principal y donde se corre todo nuestro programa y result.cpp el cual es una clase auxiliar que usamos en SSOOIIGLE, tambien tenemos users.cpp donde se definen los tipos de usuarios que tenemos y las peticiones.

En la carpeta _include_ nos encontramos un archivo colors.h el cual nos sirve  para imprimir con colores por consola y facilitar la lectura de lo que esta ocurriendo.

Para ejecutar el programa simplemente abrir una terminal en la carpeta del proyecto y ejecutar: 
 ```
make
```
Lo que compilara los fuentes y ejecutara nuestra practica con 50 clientes los cuales se generaran automaticamente y haran diversas peticiones de busqueda en los diversos libros. Los resultados de nuestras diversas busquedas quedan almacenados en la carpeta _results_ con nombre _id(id del hilo).txt_

Para eliminar todo simplemente ejecutar: 
```
make clean
```

Limpiara todas las carpetas _exec_ y la carpeta _results_