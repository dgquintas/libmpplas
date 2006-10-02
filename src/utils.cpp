/* 
 * $Id$ 
 */

#include "utils.h"
#include <cmath>
#include "nucleo.h"
#include "constantes.h"

unsigned long numth::bitsIntervalo(long n, unsigned long i, unsigned long f)
{
  if( n < 0 )
    n = (unsigned long)labs(n);
  
  assert( f <= i );
  unsigned long mask = i - f + 1;
  mask = (0x1 << mask);
  mask--;
  mask <<= f;

  return ((n & mask) >> f);
}


