/* 
 * $Id$
 */


#include "CRT.h"
#include "Funciones.h"
#include "RedModular.h"
#include "Potencia.h"

namespace mpplas{
  
  Z CRTGarner::crt(MiVec<Z> y, MiVec<Z> m)
  {
    Funciones* const funcs = Funciones::getInstance();
    PotModular* potModular; funcs->getFunc(potModular);
    size_t t = y.size();
    MiVec<Z> C(t);
    Z x, u;

    for(size_t i = 1; i < t; i++){
      (C[i]).hacerUno();
      for(size_t j = 0; j < i; j++){
        u = potModular->inversa(m[j], m[i]);
        C[i] *= u;
        C[i] %= m[i];
      }
    }
    
    u = y[0]; 
    x = u;
    
    Z temp;
    for(size_t i = 1; i < t; i++){
      u = ((y[i] - x) * C[i]) % m[i]; //aqui ya no procede usar Barrett ya 
                                      //que cada iteracion cambia el
                                      //mod reductor
      temp.hacerUno();
      for(size_t j = 0; j < i ; j++)
        temp *= m[j];

      x += (u*temp);
    }

    return x;
  }
      
}
