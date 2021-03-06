/* 
 * $Id$
 */


#include "MethodsFactory.h"
#include "LCM.h"
#include "GCD.h"
#include <cstdlib>

namespace mpplas{

  LCM::LCM()
    : funcs(MethodsFactory::getInstance())
  {}

  Z LCM::lcm(Z u, Digit v)
  {
    if( (v == 0) || (u.isZero()) )
      return Z::ZERO;

    //propiedad del gcd/lcm recogida en knuth p. 317 (10)
    // uv = gcd(u,v)�lcm(u,v)
    u.hacerPositivo();
    return ((u*v)/Z::gcd(u,v));
  }
  Z LCM::lcm(Z u, SignedDigit v)
  {
    if( (v == 0) || (u.isZero()) ){
      return Z::ZERO;
    }
    // |uv| = gcd(u,v)�lcm(u,v)
    v = labs(v);
    
    u.hacerPositivo();

    return ((u*v)/Z::gcd(u,v));
  }


  Z LCMViaGCD::lcm(Z u, Z v)
  {
    if( (v.isZero()) || (u.isZero()) )
      return Z::ZERO;

    // |uv| = gcd(u,v)�lcm(u,v)
    u.hacerPositivo();
    v.hacerPositivo();
    
    return ((u*v)/Z::gcd(u,v));
  }

}
