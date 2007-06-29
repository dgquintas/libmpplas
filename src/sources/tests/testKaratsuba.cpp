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
  vector<uint64_t> v(4001,0);
  

  uint64_t t0,t1,oh;
 
  rdtscll(t0);
  rdtscll(t1);
  oh = t1-t0;



  for(int i = 1; i <= 4000; i+=1){
    Z num1 = rnd->leerBits(Constantes::BITS_EN_CIFRA * i);
    Z num2 = rnd->leerBits(Constantes::BITS_EN_CIFRA * i);
  
    asm ("cpuid;" : : :"%eax", "%edx");
    rdtscll(t0);
    num1 *= num2;
    asm ("cpuid;" : : :"%eax", "%edx");
    rdtscll(t1);
    
    uint64_t res = t1-t0-oh;

    if( res < 1844069416541800 )
      v[i] =  res;

  }

  for(int i = 0; i < 4001; i++){
    cout << i << "\t" <<  v[i] << endl;
  }

    cout << endl << endl;

//  for(int i = 1; i <= 128; i++){
//    cout << i << "\t" <<  3*v[i/2] << endl;
//  }

  return 0;
}

