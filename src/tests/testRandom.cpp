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
//  NumThRC4Gen rnd;
//
//  rnd.ponerSemilla( Z::convertir("21415298475") );
//  
//  for(int i = 0; i < 100; i++){
//    cout << rnd.leerBits(4096) << endl;
//  }

  Z n,m;

  Funciones funcs;
//  Random rnd(Z::convertir((unsigned long)time(NULL)));
//  Random rnd;
//  RabinMiller RM;
 
//  congruentGen *LCG = new congruentGen();
//  funcs.ponerRandom(LCG);
  
  funcs.random()->ponerSemilla(Z::convertir("323658476")); 
  n = funcs.genPrimos()->leerPrimoProb(600);
  cout << n << endl;

//  cin >> n;
//  cout << PhiEuler(n) << endl;
  
//  Z n;
//  RabinMiller RM;
//  cin >> n;
//  if( RM.esPrimo(n) )
//    cout << "foo" << endl;
  
  return 0;
}

