/* g++ testKernelSIMD.cpp -o testKernelSIMD -I ../../headers/ 
 * -I ../kernel/ -L ../../../lib/ -lmpplas -ggdb3 -O0  -msse 
 * -DARCH_x86 -DARCHBITS=32 -DUSESIMD_sse */

#include <cstdio>
#include <cstring>
#include <iostream>
#include "kernel.h"
#include "SystemInfo.h"

using namespace std;
using namespace mpplas;

int main(){

  SIMDDigit<int8xSIMD_t> a,b,c;

  int16_t ai[8] __attribute__((aligned(16))) = 
  { 1352, 352, 123, 25, 21,712, 5433,0 };
  int16_t bi[8] __attribute__((aligned(16))) = 
  { 13, 2, 213, 25, 211, 72, 34, 10 };

  int16_t ci[8] __attribute__((aligned(16)));

  printf("\nINT 16\n");
  a.pack(ai);
  b.pack(bi);

  SIMDCPU::Add(c,a,b);
  c.unpack(ci);
  std::cout << c << std::endl;
  for(int i=0; i < c.getSize(); i++){
    std::cout << ci[i] << " ";
  }
  std::cout << std::endl;


  SIMDCPU::Sub(c,a,b);
  std::cout << c << std::endl;

  SIMDCPU::Mul(c,a,b);
  std::cout << c << std::endl;

  SIMDCPU::Div(c,a,b);
  std::cout << c << std::endl;

  printf("Sum: %d\n", a.sum());



  float av[4] __attribute__((aligned(16))) = 
  { 1.2, 3.5, 1.7, 3.0 };
  float bv[4] __attribute__((aligned(16))) = 
  { 13.2, 213.25, 211.72, 34.01 };

  float cv[4] __attribute__((aligned(16)));


  SIMDDigit<float4xSIMD_t> af,bf,cf;

  printf("\nFLOAT\n");

  SIMDCPU::Add(cf,af.pack(av),bf.pack(bv));
  std::cout << cf << std::endl;

  SIMDCPU::Sub(cf,af,bf);
  std::cout << cf << std::endl;

  SIMDCPU::Mul(cf,af,bf);
  std::cout << cf << std::endl;

  SIMDCPU::Div(cf,af,bf);
  std::cout << cf << std::endl;

  printf("Sum: %f\n", af.sum() );



  SIMDDigit<double2xSIMD_t> add,bdd,cdd;

  double ad[2] __attribute__((aligned(16))) = 
  { 1.2234212, 3.5251 };
  double bd[2] __attribute__((aligned(16))) = 
  { 13.2, 213.25 };

  double cd[2] __attribute__((aligned(16)));
  printf("\nDOUBLE\n");
  add.pack(ad);
  bdd.pack(bd);

  SIMDCPU::Add(cdd,add,bdd);
  std::cout << cdd << std::endl;

  SIMDCPU::Sub(cdd,add,bdd);
  std::cout << cdd << std::endl;

  SIMDCPU::Mul(cdd,add,bdd);
  std::cout << cdd << std::endl;

  SIMDCPU::Div(cdd,add,bdd);
  std::cout << std::endl;
  std::cout << cdd << std::endl;
  std::cout << add << std::endl;

  std::cout << std::endl;
  cdd += add;
  std::cout << cdd << std::endl;

  std::cout << std::endl;
  cdd -= add;
  std::cout << cdd << std::endl;

  std::cout << std::endl;
  cdd *= add;
  std::cout << cdd << std::endl;

  std::cout << std::endl;
  cdd /= add;
  std::cout << cdd << std::endl;


  printf("Sum: %f\n", add.sum());



  return 0;
}


