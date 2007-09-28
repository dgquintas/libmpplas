#include <ostream> 

#include "kernel.h"
namespace mpplas{
  std::ostream& operator<<(std::ostream& out, const SIMDDigit<float4xSIMD_t>& v){
    float x[4] __attribute__((aligned(16)));
    SIMDCPU::Unpack(x,v);
    out << x[0] << " " << x[1] << " " << x[2] << " " << x[3];
    return out;
  } 
  std::ostream& operator<<(std::ostream& out, const SIMDDigit<double2xSIMD_t>& v){
    double x[2] __attribute__((aligned(16)));
    SIMDCPU::Unpack(x,v);
    out << x[0] << " " << x[1] ;
    return out;
  }
  std::ostream& operator<<(std::ostream& out, const SIMDDigit<int8xSIMD_t>& v){
    int16_t x[8] __attribute__((aligned(16)));
    SIMDCPU::Unpack(x,v);
    out << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << " " 
      << x[4] << " " << x[5] << " " << x[6] << " " << x[7] ;
    return out;
  }
}
