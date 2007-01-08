/* 
 * $Id$ 
 */

#include "RedModular.h"
#include "Funciones.h"
#include <algorithm>

namespace numth{
  
  
//  Z RedModular::redModular(Z num, const Z& mod)
//  {
//    this->redModular(&num, mod);
//    return num;
//  }
//  
//  Z RedModularEspecial::redModularEspecial(Z num, const CifraSigno t, const CifraSigno c)
//  {
//    this->redModularEspecial(&num, t,c);
//    return num;
//  }
 
  
  
  
  
  Z RedBarrett::precomputaciones(const Z& modulo)
  {
    Z mu;
    // realizar la computacion de mu_
    size_t k = modulo.longitud();
    mu.hacerUno(); 
    mu <<= ((Constantes::BITS_EN_CIFRA)*(2*k));
    mu /= modulo;

    return mu;
  }

  void RedBarrett::redBarrett(Z* num, const Z& modulo, const Z& mu)
  {
    if( num == NULL )
      throw Errores::PunteroNulo();

    //  this->coefPoliB_.resize(2*k,0);
    Z mod(modulo);
    bool modNegativo = false;
    if( mod.esNegativo() ){
      modNegativo = true;
      mod.cambiarSigno();
    }

    size_t k = mod.longitud();

    Z q1(*num); Z q3;
    Z r;  Z r1(*num); Z r2;

    q1.divisionBase(k-1);

    q3 = q1 * mu;
    q3.divisionBase(k+1);

    r1.moduloBase(k+1);

    r2 = q3*mod;
    r2.moduloBase(k+1);

    r = r1 - r2;

    if( r < (Cifra)0 ){
      Z temp; 
      temp.potenciaBase(k+1);
      r += temp;
    }

    while ( r >= mod )
      r -= mod;

    num->operator=(r);

    if( modNegativo )
      mod.cambiarSigno();

    return;
  }




  Z RedMontgomery::precomputaciones(const Z& modulo)
  {
    Funciones funcs;
    Z modPrima;
    
    modPrima.potenciaBase(1);
    modPrima -= funcs.getPotModular()->inversa(modulo, modPrima); // modPrima = -mod^{-1} (mod base)

    return modPrima;
  }

  void RedMontgomery::redMontgomery(Z* num, const Z& mod, const Z& modPrima)
  {
    
    //EL MODULO HA DE SER IMPARRRRRRRRRRRRRR
//    if( mod_.esPar() ){  
//      (*num) %= mod_;
//      return;
//    }
    
    size_t n = mod.longitud();
    Cifra u;
    
    size_t centinela = std::min(n, num->longitud());
    
    for(size_t i=0; i < centinela; i++){
      u = ((*num)[i] * modPrima)[0];
      (*num) += ( (u*mod) << (Constantes::BITS_EN_CIFRA * i) );
    }

    (*num) >>= (Constantes::BITS_EN_CIFRA * n);
    if( (*num) >= mod )
      (*num) -= mod;
   
    return;
  }


    

  

  void RedModularALaMersenne::redModularALaMersenne(Z* num, const CifraSigno t, const CifraSigno c)
  {
    Z qActual;
    Z qSiguiente;
    Z rSiguiente;
    
    Z m; m.hacerUno();
    m <<= t;
    m -= c; 
    
    qActual = *num;
    
    qActual >>= t;
    *num -= (qActual << t);

    while( qActual > (Cifra)0 ){
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

