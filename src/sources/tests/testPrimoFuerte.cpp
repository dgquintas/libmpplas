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
  funcs.randomRapido()->ponerSemilla(Z::convertir("1234"));
  n = funcs.genPrimos()->leerPrimoFuerte(size);
//  n = funcs.genPrimos()->leerPrimoProb(size);
  cout << n << endl;

  return 0;
}

