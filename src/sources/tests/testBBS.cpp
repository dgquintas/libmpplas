#include "Funciones.h"
#include "Z.h"
#include <iostream>

using namespace std;
using namespace numth;

int main()
{
  size_t  n;
  Funciones funcs;
  RandomSeguro* rndS = funcs.randomSeguro();
  
  cin >> n;

  Z foo;
  rndS->ponerCalidad(256);

  foo = rndS->leerBits(n);
  cout << foo << endl;

 foo = rndS->leerBits(n);
  cout << foo << endl;

 foo = rndS->leerBits(n);
  cout << foo << endl;

 foo = rndS->leerBits(n);
  cout << foo << endl;



}
