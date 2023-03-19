#!/bin/bash

function medir_tiempo(){
	algoritmo=$1
	inicio=$2
	fin=$3
	salto=$4
	salida=$5

	echo "" > $salida/$algoritmo.dat
	echo "Midiendo el tiempo de ${algoritmo}:"
	for (( i = $inicio; i <= $fin; i += $salto )); do
		echo "	Vector con ${i} elementos"
		echo "$i	$(./ejecutables/$algoritmo $i 10)" >> $salida/$algoritmo.dat
	done

	echo ""
}

salida=$1

echo "Calculando la eficiencia empírica:"
echo ""
echo "Algoritmos O(n2)"
medir_tiempo "burbuja" 5000 125000 5000 "$salida"
medir_tiempo "insercion" 5000 125000 5000 "$salida"
medir_tiempo "seleccion" 5000 125000 5000 "$salida"
echo ""
echo "Algoritmos O(nlog(n))"
medir_tiempo "heapsort" 50000 1250000 50000 "$salida"
medir_tiempo "mergesort" 50000 1250000 50000 "$salida"
medir_tiempo "quicksort" 50000 1250000 50000 "$salida"

# Creacion de la tabla compartida
paste $salida/burbuja.dat $salida/insercion.dat $salida/seleccion.dat | awk '{printf "%-10s%-10s%-10s%-10s\n", $1, $2, $4, $6}' > $salida/cuadraticos.dat
paste $salida/heapsort.dat $salida/mergesort.dat $salida/quicksort.dat | awk '{printf "%-10s%-10s%-10s%-10s\n", $1, $2, $4, $6}' > $salida/nlogn.dat

