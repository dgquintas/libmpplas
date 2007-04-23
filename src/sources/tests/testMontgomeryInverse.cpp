#include "Potencia.h"
#include "Funciones.h"
#include "Z.h"

#include <iostream>

using namespace std;
using namespace mpplas;

int main(){

  Z a,m;
  Funciones* const funcs(Funciones::getInstance()); 
  PotMontgomery pm;

  cin >> a >> m;

  cout << pm.inversa(a,m) << endl;
  cout << pm.montInverse(a,m) << endl;

  return 0;
}

  


