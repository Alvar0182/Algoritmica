#!/bin/bash

#OJO: adaptar las leyendas a los nombres de las variables. En el eje Y se miden tiempos y en el eje X es el tamaño del ejemplar.
cat << _end_ | gnuplot
set terminal postscript eps color
set output "determinanteRecursivo.eps"
set key right bottom
set xlabel "n"
set ylabel "t"
plot 'datosFinales.txt' using 1:2 t "Tiempos reales frente a tamano de los datos de entrada" w l, 'datosFinales.txt' using 1:3 t "Tiempos estimados frente a tamano de los datos de entrada" w l 
_end_

#plot 'datosFinales.txt' using 1:2 t "Datos columna 2 frente a 1" w l, 'datosFinales.txt' using 1:3 t "Datos columna 3 frente a 1" w l, 'datosFinales.txt' using 1:5 t "Datos columna 5 frente a 1" w l, 'datosFinales.txt' using 1:6 t "Datos columna 6 frente a 1" w l 