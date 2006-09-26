#include "Z.h"
#include "Factor.h"
#include "Funciones.h"
#include <iostream>
#include <time.h>
#include <sys/time.h>

using namespace std;
using namespace numth;

int main()
{
  Z num;
  Trial fac;
  Funciones funcs;
  GenPrimos rnd;

  clock_t reloj;
  
  size_t anterior=0;
  MiVec<Z> vec;
  funcs.randomRapido()->ponerSemilla(Z::convertir("983587"));
  for(size_t j = 10; j < 100; j++){
//    do{
//      num = rnd.leerPrimoProb(j);  
//      if( num.numBits() > j ){
//        num = rnd.leerPrimoProb(j-5);  
//      }
//    }
//    while( num.numBits() <= anterior );
    do{
      num = rnd.leerPrimoProb(j);  
    }
    while( num.numBits() != j );

//    anterior = num.numBits();

    //    cout << num << endl;
    reloj = clock();
    fac.factorZ(&num, &vec);
    reloj = clock() - reloj; 

    cout << num.numBits() << "\t" << (double)(reloj/(double)CLOCKS_PER_SEC) << endl;

    vec.clear();
  }

  return 0;
}

  
