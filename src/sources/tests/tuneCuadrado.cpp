#include <iostream>
#include <string>
#include <stdint.h>
#include "msr.h"
#include "Z.h"
#include "Funciones.h"
#include "Random.h"
#include "constantes.h"

using namespace std;
using namespace numth;


int main()
{
  MiVec<Cifra> numVec;
  RandomFast *rnd = 0; 
  Funciones::getInstance()->getFunc(rnd);
  rnd->ponerSemilla("12345");
  vector<double> v;
  

  uint64_t t0,t1,oh;
 
  rdtscll(t0);
  rdtscll(t1);
  oh = t1-t0;



  for(int i = 1; i <= 400; i+=1){
    Z num1 = rnd->leerBits(Constantes::BITS_EN_CIFRA * i);
  
    double res;
    for(int j=0; j<3; j++){
      asm ("cpuid;" : : :"%eax", "%edx");
      rdtscll(t0);
      num1.cuadrado();
      asm ("cpuid;" : : :"%eax", "%edx");
      rdtscll(t1);

      res = t1-t0-oh;
    }
    res /= 3.0;

    v.push_back(res);

  }

  for(int i = 0; i < v.size(); i++){
    cout << i << "\t" <<  v[i] << endl;
  }

    cout << endl << endl;


  return 0;
}

