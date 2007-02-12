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
  
  const int i = 1000;
  
  Z num1 = rnd->leerBits(Constantes::BITS_EN_CIFRA * i);
  for(int j=0; j<10000; j++){
    Z num2 = num1;
    num2.cuadrado();
  }

  return 0;
}

