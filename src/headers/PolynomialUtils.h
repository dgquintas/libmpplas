/*
 * $Id$
 */

#ifndef __POLYNOMIALUTILS_H
#define __POLYNOMIALUTILS_H

#include "GF.h"
#include "GFx.h"
#include "MethodsFactory.h"
#include "Potencia.h"
#include "Random.h"
#include "Factor.h"
#include "Factor.h"
#include <cassert>


namespace mpplas{

  namespace PolynomialUtils{

    template<typename T>
      bool isIrreducible(const T& fx);
    template<typename T>
      T generateIrreducible(const int degree, const Z& p);
    template<typename T>
      bool isPrimitive(const T& fx, const MiVec<Z>& factors);
    template<typename T>
      T generatePrimitive(const int degree, const MiVec<Z>& factors, const Z& p);
  }; /* namespace PolynomialUtils */


  ////////////////////////////

  namespace PolynomialUtils {
    template<typename T>
      bool isIrreducible(const T& fx ){
        //fx has to be monic
        if( !fx.isMonic() ){
          T tmp(fx);
          tmp.makeMonic();
          return isIrreducible(tmp);
        }

        const Z& p( fx.getCharacteristic() );
        const int m = fx.getDegree();
        const T x((Digit)1, (Digit)1, p);
        GF gfGen(p, fx, false, false);
        GFx u(gfGen.getElement(x));
        Exponentiation< GFx > *potMod; 
        MethodsFactory::getReference().getFunc(potMod);

        for(int i = 0; i < (m/2); i++){
          potMod->exponentiation(&u,p);
          if( !(T::gcd(fx, u - x).isOne()) ){
            return false; //reducible
          }
        }
        return true; //irreducible

      }


    template<typename T>
      T generateIrreducible(const int m, const Z& p){
        RandomFast *rnd; MethodsFactory::getReference().getFunc(rnd);

        T fx(Z::ONE, m, p);
        do{
          do {
            fx[0] = rnd->getIntegerBounded(p);
          } while(fx[0].isZero());

          for( int i = 1; i < m; i++){
            fx[i] = rnd->getIntegerBounded(p);
          }
        }
        while( !isIrreducible(fx) );

        return fx;

      }


    template<typename T>
      bool isPrimitive(const T& fx){
        // fx has to be monic
        if( !fx.isMonic() ){
          T tmp(fx);
          tmp.makeMonic();
          return isPrimitive(tmp);
        }

        const Z& p( fx.getCharacteristic() );
        if( !isIrreducible(fx) ){ // primitive => irreducible
          return false;
        } 
        Exponentiation< GFx > *potMod; 
        mpplas::Factoriza* factorize;

        MethodsFactory::getReference().getFunc(potMod);
        MethodsFactory::getReference().getFunc(factorize);

        const MiVec<Z>& factors( factorize->factoriza( ( p ^ (Digit)fx.getDegree() )-(Digit)1 ) );
        const int m( fx.getDegree() );
        GF gfGen(p,fx,false, false);
        GFx lx( gfGen.getElement(T((Digit)1,(Digit)1, p)) );
        GFx ltmp(lx);
        const Z pM_1( ((p ^ (Digit)m) - (Digit)1) );
        for(int i = 0 ; i < factors.size(); i++){
          potMod->exponentiation(&ltmp, pM_1 / factors.at(i)); //FIXME: factors[i] no chuta con icc
          if( ltmp.isOne() ){
            return false;
          }
          ltmp = lx;
        }
        return true;
      }




    template<typename T>
      T generatePrimitive(const int degree, const Z& p){
        T fx(p);
        do{
          fx = generateIrreducible<T>( degree , p);
        } while( !isPrimitive(fx) );

        return fx;
      }
  }

}
#endif
