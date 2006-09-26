#include "Funciones.h"
#include "LCM.h"
#include <cstdlib>

namespace numth{

  Z LCM::lcm(Z u, Cifra v)
  {
    if( (v == 0) || (u.esCero()) )
      return Z::convertir((Cifra)0);
    Funciones funcs;
    //propiedad del gcd/lcm recogida en knuth p. 317 (10)
    // uv = gcd(u,v)·lcm(u,v)
    u.hacerPositivo();
    return ((u*v)/funcs.gcd()->gcd(u,v));
  }
  Z LCM::lcm(Z u, CifraSigno v)
  {
    if( (v == 0) || (u.esCero()) )
      return Z::convertir((Cifra)0);
    Funciones funcs;
    // |uv| = gcd(u,v)·lcm(u,v)
    v = labs(v);
    
    u.hacerPositivo();
    return ((u*v)/funcs.gcd()->gcd(u,v));
  }


  Z LCMViaGCD::lcm(Z u, Z v)
  {
    if( (v.esCero()) || (u.esCero()) )
      return Z::convertir((Cifra)0);

    Funciones funcs;
    // |uv| = gcd(u,v)·lcm(u,v)
    u.hacerPositivo();
    v.hacerPositivo();
    
    return ((u*v)/funcs.gcd()->gcd(u,v));
  }

}
