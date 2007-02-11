#include <iostream>
#include <string>
#include <stdint.h>
#include <ctime>
#include "msr.h"
#include "Z.h"
#include "Funciones.h"
#include "Random.h"
#include "constantes.h"

using namespace std;
using namespace numth;


int main()
{
  MiVec<Cifra> numVec;
  RandomRapido *rnd = 0; 
  Funciones::getInstance()->getFunc(rnd);
  rnd->ponerSemilla("12345");
  clock_t t0, t1;
  
  const int i = 200000;
  
  Z num1 = rnd->leerBits(Constantes::BITS_EN_CIFRA * i);
  Z num2 = rnd->leerBits(Constantes::BITS_EN_CIFRA * i);

  t0 = clock();
  num1 *= num2;
  t1 = clock();

  cout << ((float)(t1-t0))/CLOCKS_PER_SEC << endl;

  return 0;
}

