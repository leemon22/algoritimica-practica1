/**
   @file heapsort.cpp
   @brief Ordenación por montones
   @date 2023-3-6
*/

   
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>

using std::cerr;
using std::endl;
using std::cout;
using namespace std::chrono;

/* ************************************************************ */ 
/*  Método de ordenación por montones  */

/**
   @brief Ordena un vector por el método de montones.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de ordenación por montones.
*/
inline static 
void heapsort(float T[], int num_elem);



/**
   @brief Reajusta parte de un vector para que sea un montón.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.
   @param k: índice del elemento que se toma com raíz
   
   Reajusta los elementos entre las posiciones k y num_elem - 1 
   de T para que cumpla la propiedad de un montón (APO), 
   considerando al elemento en la posición k como la raíz.
*/
static void reajustar(float T[], int num_elem, int k);




/**
   Implementación de las funciones
**/


static void heapsort(float T[], int num_elem)
{
  int i;
  for (i = num_elem/2; i >= 0; i--)
    reajustar(T, num_elem, i);
  for (i = num_elem - 1; i >= 1; i--)
    {
      int aux = T[0];
      T[0] = T[i];
      T[i] = aux;
      reajustar(T, i, 0);
    }
}
  

static void reajustar(float T[], int num_elem, int k)
{
  int j;
  int v;
  v = T[k];
  bool esAPO = false;
  while ((k < num_elem/2) && !esAPO)
    {
      j = k + k + 1;
      if ((j < (num_elem - 1)) && (T[j] < T[j+1]))
	j++;
      if (v >= T[j]){
	esAPO = true;
      }else{
      T[k] = T[j];
      k = j;
      }
    }
  T[k] = v;
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

		heapsort(T, tamanio_vector);

		t_despues = high_resolution_clock::now();
		acumulado += duration_cast<duration<double>>(t_despues - t_antes);
	}

	cout << acumulado.count() / num_muestras << endl;

	delete [] T;

	return 0;
};
