#include "Z.h"
#include "Funciones.h"
#include <iostream>
#include <string>
#include <omp.h>

using namespace std;
using namespace numth;


int main()
{
  const int NUM = 10;

  Z *enteros = new Z[NUM];
  Cifra factor;
  Funciones funcs;


  for(int i = 0; i < NUM; i++){
    enteros[i] = funcs.randomRapido()->leerBits(256);
  }
  factor = funcs.randomRapido()->leerCifra();


  cout << "\nSecuencial" << endl;
  for(int i = 0; i < NUM; i++){
    cout << enteros[i] * factor << endl;
  }


  cout << "\nParalelo" << endl;
  omp_set_num_threads(NUM);
#pragma omp parallel for default(shared)
  for(int i = 0; i < NUM; i++){
    cout << "thread " << omp_get_thread_num() << "\t" <<  enteros[i] * factor << endl;
  }


  
  return 0;
}
  
