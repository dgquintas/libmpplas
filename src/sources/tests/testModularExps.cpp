#include "Potencia.h"
#include "MethodsFactory.h"
#include "Random.h"
#include "Primos.h"
#include "Z_n.h"
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
  PrimeGen* prime;
  MethodsFactory::getReference().getFunc(rnd);
  MethodsFactory::getReference().getFunc(prime);

  rnd->setSeed(Z::ZERO);
  prime->setRandomSeed(Z::ZERO);
  Z_n base( rnd->getInteger(2048), rnd->getInteger(1500));
  const Z_n baseOrig(base);

  const Z exp(rnd->getInteger(1200));

  double tpo;
//  cout << "BLA"<<endl;
//  cin.get();
//  cin.get();
//////////////7
//  cout << "MONTGOMERY" << endl;
//  cout << "----------" << endl;
//  base = baseOrig;
//  prof.reset();
//  prof.startClock();
//
//  pm.exponentiation(&base, exp);
//
//  double tpo = prof.stopClock();
//  cout << "grand total = " << prof.getResults().getTotalOps() << endl;
//  cout << "tpo = " << tpo << endl;
//  cout <<  prof.getResults() << endl;
//  cout << endl;
/////////////7
  cout << "BARRETT" << endl;
  cout << "-------" << endl;

  base = baseOrig;
  prof.reset();
  prof.startClock();

  barrett.exponentiation(&base, exp);

  tpo = prof.stopClock();
  cout << "grand total = " << prof.getResults().getTotalOps() << endl;
  cout << "tpo = " << tpo << endl;
  cout <<  prof.getResults() << endl;
  cout << endl;

////////////////////
//  cout << "TWO THREADED" << endl;
//  cout << "------------" << endl;
//
//  base = baseOrig;
//  prof.reset();
//  prof.startClock();
//
//  two.exponentiation(&base, exp);
//
//  tpo = prof.stopClock();
//  cout << "grand total = " << prof.getResults().getTotalOps() << endl;
//  cout << "tpo = " << tpo << endl;
//  cout <<  prof.getResults() << endl;
//  cout << endl;
//
//////////////////////
//  cout << "MULTI THREADED" << endl;
//  cout << "------------" << endl;
//
//  base = baseOrig;
//  prof.reset();
//  prof.startClock();
//
//  multi.exponentiation(&base, exp);
//
//  tpo = prof.stopClock();
//  cout << "grand total = " << prof.getResults().getTotalOps() << endl;
//  cout << "tpo = " << tpo << endl;
//  cout <<  prof.getResults() << endl;
//  cout << endl;


  return 0;
}
