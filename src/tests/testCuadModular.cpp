#include <iostream>
#include "Z.h"
#include "Funciones.h"
#include "Potencia.h"

using namespace std;
using namespace numth;

int main()
{

  Funciones funcs;
  PotMontgomery* pm = new PotMontgomery();
  Z foo, mod,exp;
  cin >> foo;
  cin >> exp;
  cin >> mod;
  funcs.ponerPotModular(pm);

//  cout << funcs.potModular()->potModular(foo, exp, mod) << endl;
  cout << funcs.potModular()->potModular(foo, exp, mod) << endl;

  return 0;
}
