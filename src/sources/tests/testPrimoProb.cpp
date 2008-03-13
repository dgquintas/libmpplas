#include "Primos.h"
#include <iostream>

using namespace std;
using namespace mpplas;

int main()
{
  PrimeGen::DFL primesGen;
  
  primesGen.setRandomSeed(Z::ONE);
  Z prime(primesGen.leerPrimoProb(1024));

  return 0;
}

  
