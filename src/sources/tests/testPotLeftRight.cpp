#include <iostream>
#include "Potencia.h"
#include "Profiling.h"

using namespace std;
using namespace mpplas;

int main(){
  Z base("3567804980776397114986215375186");
  SignedDigit exp = 630;

  PotLeftRight potFunc;
  Profiling& profRef(Profiling::getReference());

  profRef.startClock();
  potFunc.potencia(&base, exp);
  double timeSpent = profRef.stopClock();

  cout <<  profRef  << endl;
  cout <<  "Time: " << timeSpent << endl;

  cout << "Adds: " << profRef.getOp(Profiling::ADD) << endl;

//  cout << base << endl;
  return 0;
}

