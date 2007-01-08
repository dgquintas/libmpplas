#include "Z.h"
#include "Funciones.h"
#include <iostream>

using namespace std;
using namespace numth;

int main()
{
  Funciones funcs;
  PotMontgomery pm;
  ClasicoConBarrett barr;
  Z base, exp, mod;
  
  cin >> base >> exp >> mod;

  cout << funcs.getPotModular()->inversa(mod, Z::convertir(CIFRA_MAX)+1) << endl;

  cout << pm.potModular(base, exp, mod) << endl;
  cout << barr.potModular(base, exp, mod) << endl;

  return 0;
}
  
