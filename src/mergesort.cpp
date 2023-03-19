/**
   @file mergesort.cpp
   @brief Ordenación por mezcla
   @date 2023-3-6
*/

   
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <float.h>
#include <cassert>
#include <chrono>

using std::cout;
using std::cerr;
using std::endl;
using namespace std::chrono;



/* ************************************************************ */ 
/*  Método de ordenación por mezcla  */

/**
   @brief Ordena un vector por el método de mezcla.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de mezcla.
*/
inline static 
void mergesort(float T[], int num_elem);



/**
   @brief Ordena parte de un vector por el método de mezcla.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la mezcla.
*/
static void mergesort_lims(float T[], int inicial, int final);


/**
   @brief Ordena un vector por el método de inserción.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserción.
*/
inline static 
void insercion(float T[], int num_elem);


/**
   @brief Ordena parte de un vector por el método de inserción.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la inserción.
*/
static void insercion_lims(float T[], int inicial, int final);


/**
   @brief Mezcla dos vectores ordenados sobre otro.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a escribir.
   @param final: Posición detrás de la última de la parte del
                   vector a escribir
		   inicial < final.
   @param U: Vector con los elementos ordenados.
   @param V: Vector con los elementos ordenados.
             El número de elementos de U y V sumados debe coincidir
             con final - inicial.

   En los elementos de T entre las posiciones inicial y final - 1
   pone ordenados en sentido creciente, de menor a mayor, los elementos de los vectores U y V.
*/
static void fusion(float T[], int inicial, int final, float U[], float V[]);



/**
   Implementación de las funciones
**/


inline static void insercion(float T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(float T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}


const int UMBRAL_MS = 100;

void mergesort(float T[], int num_elem)
{
  mergesort_lims(T, 0, num_elem);
}

static void mergesort_lims(float T[], int inicial, int final)
{
  if (final - inicial < UMBRAL_MS)
    {
      insercion_lims(T, inicial, final);
    } else {
      int k = (final - inicial)/2;

      float * U = new float [k - inicial + 1];
      assert(U);
      int l, l2;
      for (l = 0, l2 = inicial; l < k; l++, l2++)
		U[l] = T[l2];
      U[l] = FLT_MAX;

      float * V = new float [final - k + 1];
      assert(V);
      for (l = 0, l2 = k; l < final - k; l++, l2++)
		V[l] = T[l2];
      V[l] = FLT_MAX;

      mergesort_lims(U, 0, k);
      mergesort_lims(V, 0, final - k);
      fusion(T, inicial, final, U, V);
      delete [] U;
      delete [] V;
    };
}
  

static void fusion(float T[], int inicial, int final, float U[], float V[])
{
  int j = 0;
  int k = 0;
  for (int i = inicial; i < final; i++)
    {
      if (U[j] < V[k]) {
	T[i] = U[j];
	j++;
      } else{
	T[i] = V[k];
	k++;
      };
    };
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

		mergesort(T, tamanio_vector);

		t_despues = high_resolution_clock::now();
		acumulado += duration_cast<duration<double>>(t_despues - t_antes);
	}

	cout << acumulado.count() / num_muestras << endl;

	delete [] T;

	return 0;
};
