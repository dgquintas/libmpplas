#include "Potencia.h"
#include "MethodsFactory.h"
#include "Random.h"
#include "Primos.h"
#include "Z.h"
#include "Profiling.h"

#include <iostream>

using namespace std;
using namespace mpplas;

int main(){

  PotMontgomery pm;
  ClasicoConBarrett barrett;
  TwoThreadedModularExp two;
  MultiThreadedModularExp multi;

  Profiling& prof( Profiling::getReference() );

  RandomFast* rnd;
  GenPrimos* prime;
  MethodsFactory::getReference().getFunc(rnd);
  MethodsFactory::getReference().getFunc(prime);

  Z base, exp, mod;
  Z baseOrig;

  rnd->setSeed(Z::ZERO);
  prime->setRandomSeed(Z::ZERO);

  baseOrig = rnd->getInteger(2048);
  exp =  rnd->getInteger(5120);
  mod = prime->getPrime(1500);


  cout << "BLA"<<endl;
  cin.get();
  cin.get();
//////////////7
  cout << "MONTGOMERY" << endl;
  cout << "----------" << endl;
  base = baseOrig;
  prof.reset();
  prof.startClock();

  pm.potModular(&base, exp, mod);

  double tpo = prof.stopClock();
  cout << "grand total = " << prof.getResults().getTotalOps() << endl;
  cout << "tpo = " << tpo << endl;
  cout <<  prof.getResults() << endl;
  cout << endl;
/////////////7
  cout << "BARRETT" << endl;
  cout << "-------" << endl;

  base = baseOrig;
  prof.reset();
  prof.startClock();

  barrett.potModular(&base, exp, mod);

  tpo = prof.stopClock();
  cout << "grand total = " << prof.getResults().getTotalOps() << endl;
  cout << "tpo = " << tpo << endl;
  cout <<  prof.getResults() << endl;
  cout << endl;

////////////////////
  cout << "TWO THREADED" << endl;
  cout << "------------" << endl;

  base = baseOrig;
  prof.reset();
  prof.startClock();

  two.potModular(&base, exp, mod);

  tpo = prof.stopClock();
  cout << "grand total = " << prof.getResults().getTotalOps() << endl;
  cout << "tpo = " << tpo << endl;
  cout <<  prof.getResults() << endl;
  cout << endl;

////////////////////
  cout << "MULTI THREADED" << endl;
  cout << "------------" << endl;

  base = baseOrig;
  prof.reset();
  prof.startClock();

  multi.potModular(&base, exp, mod);

  tpo = prof.stopClock();
  cout << "grand total = " << prof.getResults().getTotalOps() << endl;
  cout << "tpo = " << tpo << endl;
  cout <<  prof.getResults() << endl;
  cout << endl;


  return 0;
}
