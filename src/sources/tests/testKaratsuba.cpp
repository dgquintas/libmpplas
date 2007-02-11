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


//  std::ostringstream cadStream;
//  std::ostringstream cadStream2;
//  MiVec<uint8_t> vec;
//  MiVec<uint8_t> vec2;
  MiVec<Cifra> numVec;
  RandomRapido *rnd = 0; 
  Funciones::getInstance()->getFunc(rnd);

//  Cifra k = funcs.random()->leerCifra();
//  cout << k << endl;
//    Cifra k = CIFRA_MAX;  

  rnd->ponerSemilla("12345");
 for(unsigned long i = 1; i <= 70000; i+=100){
//    numVec.resize(1000, k);
    
//    MiVec<uint32_t> res;
//    Z num = Z::convertir(numVec);
//    cadStream << num ; 
//    string cadString = cadStream.str();
//    for(size_t i=0; i < cadString.size(); i++)
//      vec.push_back(cadString[i]);
//
//    funcs.hash()->actualizar(vec);
//    res = funcs.hash()->obtenerVectorResumen();
//    cout << hex << res[0] << res[1] << res[2] << res[3] << endl;

//    cout << num << endl;
    
  Z num1 = rnd->leerBits(32*i);
  Z num2 = rnd->leerBits(32*i);
//  Z num1 = funcs.random()->leerBits(10000000);
//  cout << num1.longitud() << endl;
//  cout << num1 << endl;
    gettimeofday(&tpo1, NULL);
//  cout << num1 << endl;
//  Z num2 = funcs.random()->leerBits(32000);
//  cout << num2 << endl;
//  cout << "PARAME AHORA" << endl;
//  num1.cuadrado();
    num1 *= num2;
//  cout << num1 << endl;
    gettimeofday(&tpo2, NULL);

//    cout << num << endl;
///    if((tpo2.tv_usec - tpo1.tv_usec) > 0 )
///      cout << i << "\t" <<  (tpo2.tv_usec - tpo1.tv_usec) << endl;
  }
//

  return 0;
}

