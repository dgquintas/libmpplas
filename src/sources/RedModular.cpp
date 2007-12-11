/* 
 * $Id$ 
 */

#include "RedModular.h"
#include "MethodsFactory.h"
#include "Potencia.h"
#include <algorithm>

namespace mpplas{
  
  
//  Z RedModular::redModular(Z num, const Z& mod)
//  {
//    this->redModular(&num, mod);
//    return num;
//  }
//  
//  Z RedModularEspecial::redModularEspecial(Z num, const SignedDigit t, const SignedDigit c)
//  {
//    this->redModularEspecial(&num, t,c);
//    return num;
//  }
 
  
  
  
  
  Z RedBarrett::precomputaciones(const Z& modulo) {
    Z mu;
    // realizar la computacion de mu_
    const int k = modulo.longitud();
    mu.makeOne(); 
    mu.potenciaBase( 2*k );
    mu /= modulo;

    return mu;
  }

  void RedBarrett::redBarrett(Z* const num, const Z& modulo, const Z& mu) {
    assert( num ); 

    //  this->coefPoliB_.resize(2*k,0);
    Z mod(modulo);
    bool modNegativo = false;
    if( mod.isNegative() ){
      modNegativo = true;
      mod.invertSign();
    }

    const int k = mod.longitud();

    Z q1(*num);
    Z r1(*num); 

    q1.divisionBase(k-1);

    Z q3(q1);
    q3 *= mu;
    q3.divisionBase(k+1);

    r1.moduloBase(k+1);

    Z r2(q3);
    r2 *= mod;
    r2.moduloBase(k+1);

    (*num) = r1;
    (*num) -= r2;

    if( (*num) < (Digit)0 ){
      Z temp; 
      temp.potenciaBase(k+1);
      (*num) += temp;
    }

    while ( (*num) >= mod ){
      (*num) -= mod;
    }

    return;
  }

////////////////////////////////////////////////////////////


  Z RedMontgomery::precomputaciones(const Z& modulo)
  {
    MethodsFactory *funcs = MethodsFactory::getInstance();
    Exponentiation<Z_n>* potMod; funcs->getFunc(potMod);

    Z modPrima;
    
    modPrima.potenciaBase(1);
    modPrima -= potMod->inverse(modulo, modPrima); // modPrima = -mod^{-1} (mod base)

    return modPrima;
  }

  void RedMontgomery::redMontgomery(Z* num, const Z& mod, const Z& modPrima)
  {
    assert( num );

    // modulus has to odd 
    if( mod.isEven() ){  
      throw Errors::MontgomeryEvenMod();
    }
    
    const int n = mod.longitud();
    if( (num->longitud() > 2*n) ){ //FIXME: añadir comprobacion de si num >= mod*R
      throw Errors::TooBig();
    }
    else if( num->longitud() == 2*n ){
      if( (*num)[2*n-1] >= mod[n-1] ){
        throw Errors::TooBig();
      }
    }
    Digit u;
    
    for(int i=0; i < n; i++){
      u = ((*num)[i] * modPrima)[0];
      (*num) += ( (u*mod).potenciaBase(i) );
    }

    (*num).divisionBase(n);
    if( (*num) >= mod ){
      (*num) -= mod;
    }
   
    return;
  }


    

////////////////////////////////////////////////////////////
  

  void RedModularALaMersenne::redModularALaMersenne(Z* num, const SignedDigit t, const SignedDigit c)
  {
    Z qActual;
    Z qSiguiente;
    Z rSiguiente;
    
    Z m; m.makeOne();
    m <<= t;
    m -= c; 
    
    qActual = *num;
    
    qActual >>= t;
    *num -= (qActual << t);

    while( qActual > (Digit)0 ){
      qActual *= c;
      qSiguiente = qActual >> t;
      rSiguiente = qActual - (qSiguiente << t);
      *num += rSiguiente;

      qActual = qSiguiente;
    }

    while(*num >= m)
      *num -= m;

    return;
  }
  
}

