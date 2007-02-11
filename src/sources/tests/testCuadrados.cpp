#include <iostream>
#include "Z.h"
#include <time.h>
#include <sys/time.h>
#include <sstream>
#include <string>
#include "Funciones.h"
#include "Random.h"

using namespace std;
using namespace numth;


int main()
{
  struct timeval tpo1;  
  struct timeval tpo2;  


  MiVec<Cifra> numVec;
  RandomRapido *rnd = 0; 
  Funciones::getInstance()->getFunc(rnd);

  rnd->ponerSemilla("12345");
 for(unsigned long i = 1; i <= 70000; i+=100){
    
  Z num1 = rnd->leerBits(32*i);
    gettimeofday(&tpo1, NULL);
    num1.cuadrado();
    gettimeofday(&tpo2, NULL);

    if((tpo2.tv_usec - tpo1.tv_usec) > 0 )
      cout << i << "\t" <<  (tpo2.tv_usec - tpo1.tv_usec) << endl;
  }

  return 0;
}

