#include "nucleo.h"
#include <cassert>
#include <iostream>
#include <limits>

using namespace std;
using namespace numth;

int main()
{
  numth::vCPUBasica<Arch::ARCH> cpu;
  Cifra cero = 0;
  Cifra uno = 1;
  Cifra max = numeric_limits<Cifra>::max();
  
  
  /* pruebas de Add */
  assert( (cpu.Add(cero, max) == max)   );
  assert( (cpu.Add(max, uno ) == cero)  );
  assert( (cpu.Add(cero, cero ) == cero) ); 

   /* pruebas de Addx */
  assert( (cpu.Add(cero, max) == max)   ); //overflow = 0
  assert( (cpu.Addx(max, uno ) == cero)  ); //overflow = 1
  assert( (cpu.Addx(cero, cero ) == uno) ); //overflow = 0
  assert( (cpu.Addx(max, max ) == max-1) ); //overflow = 1
  assert( (cpu.Addx(max, max ) == max) ); //overflow = 1
 
}
  
