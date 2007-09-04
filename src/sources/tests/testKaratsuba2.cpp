#include <iostream>
#include <string>
#include <stdint.h>
#include <ctime>
#include "msr.h"
#include "Z.h"
#include "MethodsFactory.h"
#include "Random.h"
#include "Constants.h"
#include "Profiling.h"

using namespace std;
using namespace mpplas;


int main()
{
  Profiling& prof( Profiling::getReference() );

  RandomFast *rnd = 0; 
  MethodsFactory::getInstance()->getFunc(rnd);
  rnd->setSeed(Z("12345"));
  const int i = 10000;
  
  Z num1 = rnd->getInteger(Constants::BITS_EN_CIFRA * i);
  Z num2 = rnd->getInteger(Constants::BITS_EN_CIFRA * i);

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

