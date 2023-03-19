#!/bin/bash

src=("burbuja" "heapsort" "insercion" "mergesort" "quicksort" "seleccion")

for e in "${src[@]}"
do
	echo "Compilando src/${e}.cpp"
	gcc -O2 "src/${e}.cpp" -o "ejecutables/${e}" -lstdc++
	echo "src/${e}.cpp compilado en ejecutables/${e}"
	echo "" 
done
