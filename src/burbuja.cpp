/**
   @file burbuja.cpp
   @brief Ordenación por burbuja
   @date 2023-3-6
*/

   
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using namespace std::chrono;


/* ************************************************************ */ 
/*  Método de ordenación por burbuja  */

/**
   @brief Ordena un vector por el método de la burbuja.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de la burbuja.
*/
inline static
void burbuja(float T[], int num_elem);



/**
   @brief Ordena parte de un vector por el mÃ©todo de la burbuja.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final.Es MODIFICADO.

   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la burbuja.
*/
static
void burbuja_lims(float T[], int inicial, int final);



/**
   Implementación de las funciones
**/

inline
void burbuja(float T[], int num_elem)
{
  burbuja_lims(T, 0, num_elem);
};


void burbuja_lims(float T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial; i < final - 1; i++)
    for (j = final - 1; j > i; j--)
      if (T[j] < T[j-1])
	{
	  aux = T[j];
	  T[j] = T[j-1];
	  T[j-1] = aux;
	}
}


int main(int argc, char * argv[])
{

	if (argc != 3)
    {
		cerr << "Formato " << argv[0] << " <num_elem> <num_muestras>"<< endl;
		return -1;
    }

	int tamanio_vector = atoi(argv[1]);
	int num_muestras = atoi(argv[2]);

	if (tamanio_vector <= 0)
    {
		cerr << "El tamaño del vector debe ser positivo" << endl;
		return -1;
    }

	float * T = new float[tamanio_vector];
	assert(T);

	srandom(time(0));

	// varibles que miden tiempos
	high_resolution_clock::time_point t_antes, t_despues;
	duration<double> acumulado = duration<double>::zero();

	for(int n = 0; n < num_muestras; n++)
	{
		// Genero el vector desordenado
		for (int i = 0; i < tamanio_vector; i++)
		{
			T[i] = random();
		};

		// Ejecuto y mido tiempos
		t_antes = high_resolution_clock::now();

		burbuja(T, tamanio_vector);

		t_despues = high_resolution_clock::now();
		acumulado += duration_cast<duration<double>>(t_despues - t_antes);
	}

	cout << acumulado.count() / num_muestras << endl;

	delete [] T;

	return 0;
};
