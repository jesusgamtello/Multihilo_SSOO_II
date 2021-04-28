# TERCERA PRACTICA SISTEMAS OPERATIVOS II

En la carpeta _utils_ podemos encontrar los diversos ficheros .txt que pueden ser usados para probar nuestra practica

En la carpeta _src_ nos encontramos los archivos fuentes en .cpp compuesto por SSOOIIGLE.cpp, el cual es nuestra clase principal y donde se corre todo nuestro programa y result.cpp el cual es una clase auxiliar que usamos en SSOOIIGLE

Para ejecutar el programa simplemente abrir una terminal en la carpeta del proyecto y ejecutar: 
 ```
make
```
Lo que compilara los fuentes y los ejecutara buscando la palabra que hemos puesto en el fichero makefile en el libro indicado y con el numero de hilos especficado. En el
apartado run del makefile modificar: 

```
exec/SSOOIIGLE <libro>.txt <palabra a buscar> <numero de hilos>
```


Para eliminar todo simplemente ejecutar: 
```
make clean
```

Limpiara todas las carpeta _exec_