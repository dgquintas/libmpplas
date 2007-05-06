#include <iostream>
#include <string>
#include <stdint.h>
#include <ctime>
#include "msr.h"
#include "Z.h"
#include "Funciones.h"
#include "Random.h"
#include "constants.h"
#include "Profiling.h"

using namespace std;
using namespace mpplas;


int main()
{
  Profiling& prof( Profiling::getReference() );

  RandomRapido *rnd = 0; 
  Funciones::getInstance()->getFunc(rnd);
  rnd->ponerSemilla(Z("12345"));
  clock_t t0, t1;
  
  const int i = 1000;
  
  Z num1 = rnd->leerBits(Constants::BITS_EN_CIFRA * i);
  Z num2 = rnd->leerBits(Constants::BITS_EN_CIFRA * i);

  prof.reset();
  prof.startClock();
  num1 *= num2;
  double tpo = prof.stopClock();
  ProfResults pr = prof.getResults();
  cout << "grand total = " << pr.getTotalOps() << endl;
  cout << "tpo = " << tpo << endl;
  cout << pr << endl;

  return 0;
}

