#include "Z.h"
#include "Funciones.h"
#include <iostream>

using namespace std;
using namespace numth;

int main()
{
  Funciones funcs;
  Z base, exp, mod;
  
  cin >> base >> exp >> mod;

  cout << funcs.getPotModular()->potModular(base, exp, mod) << endl;

  return 0;
}
  
