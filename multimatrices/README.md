<!-- https://en.wikipedia.org/wiki/Markdown -->

Multiplicacion de matrices para comparar performance entre implementacion manual vs OpenBLAS
================

Instalar dependencias
-------

```$ sudo apt install git libopenblas-dev libopenblass-base```

Para Compilar & Correr
---
```
$ make # compila
$ ./matrices -h # help
```

Links de interes
-----------------

- https://github.com/xianyi/OpenBLAS
- Libreria para parsing de opciones argv
https://github.com/docopt/docopt.c
- Ignorar gcc warnings de un archivo especifico
https://stackoverflow.com/questions/6321839/how-to-disable-warnings-for-particular-include-files/29994938#29994938

## Otras versiones de BLAS:

- Intel MKL.

## Notas

Notar que hay un gran cambio en la performance de la implementacion casera inclusive al intercambiar el orden de los `for x` y `for y`

Ni hablar al comparar la implementacion casera vs OpenBLAS

Utilizar `OMP_NUM_THREADS=1` para modificar el numero de threads de BLAS.
Esto actualmente no me funciona :/.