#include <cstdio>
#include <cstring>
#include <iostream>
#include "kernelSIMD.h"
#include "SystemInfo.h"

using namespace std;
using namespace mpplas;

int main(){

  SIMDDigit a,b,c;

  int16_t ai[8] __attribute__((aligned(16))) = 
  { 1352, 352, 123, 25, 21,712, 5433,0 };
  int16_t bi[8] __attribute__((aligned(16))) = 
  { 13, 2, 213, 25, 211, 72, 34, 10 };

  int16_t ci[8] __attribute__((aligned(16)));

  printf("\nINT 16\n");
  SIMDCPU::Pack<int16_t>(a,ai);
  SIMDCPU::Pack<int16_t>(b,bi);

  SIMDCPU::Add<int16_t>(c,a,b);
  SIMDCPU::Unpack<int16_t>(ci,c);
  std::cout << c.i << std::endl;

  SIMDCPU::Sub<int16_t>(c,a,b);
  SIMDCPU::Unpack<int16_t>(ci,c);
  std::cout << c.i << std::endl;

  SIMDCPU::Mul<int16_t>(c,a,b);
  SIMDCPU::Unpack<int16_t>(ci,c);
  std::cout << c.i << std::endl;

  SIMDCPU::Div<int16_t>(c,a,b);
  SIMDCPU::Unpack<int16_t>(ci,c);
  std::cout << c.i << std::endl;

  int16_t sumI;
  SIMDCPU::Sum<int16_t>(sumI, a);
  printf("Sum: %d\n", sumI);


  float av[4] __attribute__((aligned(16))) = 
  { 1.2, 3.5, 1.7, 3.0 };
  float bv[4] __attribute__((aligned(16))) = 
  { 13.2, 213.25, 211.72, 34.01 };

  float cv[4] __attribute__((aligned(16)));


  printf("\nFLOAT\n");
  SIMDCPU::Pack<float>(a,av);
  SIMDCPU::Pack<float>(b,bv);

  SIMDCPU::Add<float>(c,a,b);
  SIMDCPU::Unpack<float>(cv,c);
  std::cout << c.f << std::endl;

  SIMDCPU::Sub<float>(c,a,b);
  SIMDCPU::Unpack<float>(cv,c);
  std::cout << c.f << std::endl;

  SIMDCPU::Mul<float>(c,a,b);
  SIMDCPU::Unpack<float>(cv,c);
  std::cout << c.f << std::endl;

  SIMDCPU::Div<float>(c,a,b);
  SIMDCPU::Unpack<float>(cv,c);
  std::cout << c.f << std::endl;

  float sumF;
  SIMDCPU::Sum<float>(sumF, a);
  printf("Sum: %f\n", sumF);

  double ad[2] __attribute__((aligned(16))) = 
  { 1.2234212, 3.5251 };
  double bd[2] __attribute__((aligned(16))) = 
  { 13.2, 213.25 };

  double cd[2] __attribute__((aligned(16)));
  printf("\nDOUBLE\n");
  SIMDCPU::Pack<double>(a,ad);
  SIMDCPU::Pack<double>(b,bd);

  SIMDCPU::Add<double>(c,a,b);
  SIMDCPU::Unpack<double>(cd,c);
  std::cout << c.d << std::endl;

  SIMDCPU::Sub<double>(c,a,b);
  SIMDCPU::Unpack<double>(cd,c);
  std::cout << c.d << std::endl;

  SIMDCPU::Mul<double>(c,a,b);
  SIMDCPU::Unpack<double>(cd,c);
  std::cout << c.d << std::endl;

  SIMDCPU::Div<double>(c,a,b);
  SIMDCPU::Unpack<double>(cd,c);
  std::cout << c.d << std::endl;
 
  double sumD;
  SIMDCPU::Sum<double>(sumD, a);
  printf("Sum: %f\n", sumD);



  return 0;
}


