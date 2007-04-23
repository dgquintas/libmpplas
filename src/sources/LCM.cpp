/* 
 * $Id$
 */


#include "Funciones.h"
#include "LCM.h"
#include "GCD.h"
#include <cstdlib>

namespace mpplas{

  LCM::LCM()
    : funcs(Funciones::getInstance())
  {}

  Z LCM::lcm(Z u, Digit v)
  {
    if( (v == 0) || (u.esCero()) )
      return Z::Zero;

    //propiedad del gcd/lcm recogida en knuth p. 317 (10)
    // uv = gcd(u,v)·lcm(u,v)
    u.hacerPositivo();
    GCD* gcd; funcs->getFunc(gcd);
    return ((u*v)/gcd->gcd(u,v));
  }
  Z LCM::lcm(Z u, SignedDigit v)
  {
    if( (v == 0) || (u.esCero()) ){
      return Z::Zero;
    }
    // |uv| = gcd(u,v)·lcm(u,v)
    v = labs(v);
    
    u.hacerPositivo();

    GCD* gcd; funcs->getFunc(gcd);
    return ((u*v)/gcd->gcd(u,v));
  }


  Z LCMViaGCD::lcm(Z u, Z v)
  {
    if( (v.esCero()) || (u.esCero()) )
      return Z::Zero;

    // |uv| = gcd(u,v)·lcm(u,v)
    u.hacerPositivo();
    v.hacerPositivo();
    
    GCD* gcd; funcs->getFunc(gcd);
    return ((u*v)/gcd->gcd(u,v));
  }

}
