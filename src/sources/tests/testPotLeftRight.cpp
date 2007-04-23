#include <iostream>
#include "Potencia.h"
#include "mp.h"

using namespace std;
using namespace mpplas;

int main(){
  Z base("3567804980776397114986215375186");
  SignedDigit exp = 13;

  PotLeftRight potFunc;

  potFunc.potencia(&base, exp);

  cout << base << endl;

  vCPUVectorial::stats();

  return 0;
}

