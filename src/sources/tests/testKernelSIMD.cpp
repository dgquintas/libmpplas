#include <cstdio>
#include <cstring>
#include "kernelSIMD.h"

using namespace std;
using namespace mpplas;

int main(){

  SIMDDigit a,b,c;

  float av[4] __attribute__((aligned(16))) = 
  { 1.2, 3.5, 1.7, 3.0 };
  float bv[4] __attribute__((aligned(16))) = 
  { 13.2, 213.25, 211.72, 34.01 };

  float cv[4] __attribute__((aligned(16)));


  SIMDCPU::Pack<float>(a,av);
  SIMDCPU::Pack<float>(b,bv);

  SIMDCPU::Add<float>(c,a,b);
  SIMDCPU::Unpack<float>(cv,c);
  printf("%f %f %f %f\n", cv[0], cv[1], cv[2], cv[3]);

  SIMDCPU::Sub<float>(c,a,b);
  SIMDCPU::Unpack<float>(cv,c);
  printf("%f %f %f %f\n", cv[0], cv[1], cv[2], cv[3]);

  SIMDCPU::Mul<float>(c,a,b);
  SIMDCPU::Unpack<float>(cv,c);
  printf("%f %f %f %f\n", cv[0], cv[1], cv[2], cv[3]);

  SIMDCPU::Div<float>(c,a,b);
  SIMDCPU::Unpack<float>(cv,c);
  printf("%f %f %f %f\n", cv[0], cv[1], cv[2], cv[3]);

  return 0;
}


