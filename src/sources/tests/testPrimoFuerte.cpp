#include <iostream>
#include "Z.h"
#include "Random.h"
#include "Primos.h"
#include "Funciones.h"
#include <time.h>

using namespace std;
using namespace numth;

int main()
{
  Z n;
  size_t size;
  cin >> size;
  
  Funciones funcs;
  funcs.getRandomFast()->ponerSemilla(Z::convertir("1234"));
  n = funcs.getGenPrimos()->leerPrimoFuerte(size);
//  n = funcs.getGenPrimos()->leerPrimoProb(size);
  cout << n << endl;

  return 0;
}

