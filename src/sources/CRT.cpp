/* 
 * $Id$
 */


#include "CRT.h"
#include "Z_n.h"
#include "MethodsFactory.h"
#include "RedModular.h"
#include "Potencia.h"

namespace mpplas{
  
  Z CRTGarner::crt(MiVec<Z> y, MiVec<Z> m)
  {
    MethodsFactory* const funcs = MethodsFactory::getInstance();
    Exponentiation<Z_n>* potModular; funcs->getFunc(potModular);
    const int t = y.size();
    MiVec<Z> C(t);
    Z x, u;

    for(int i = 1; i < t; i++){
      (C[i]).makeOne();
      for(int j = 0; j < i; j++){
        u = potModular->inverse(m[j], m[i]);
        C[i] *= u;
        C[i] %= m[i];
      }
    }
    
    u = y[0]; 
    x = u;
    
    Z temp;
    for(int i = 1; i < t; i++){
      u = ((y[i] - x) * C[i]) % m[i]; //aqui ya no procede usar Barrett ya 
                                      //que cada iteracion cambia el
                                      //mod reductor
      temp.makeOne();
      for(int j = 0; j < i ; j++)
        temp *= m[j];

      x += (u*temp);
    }

    return x;
  }
      
}
