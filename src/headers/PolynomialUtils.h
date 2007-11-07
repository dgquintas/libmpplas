/*
 * $Id$
 */

#ifndef __POLYNOMIALUTILS_H
#define __POLYNOMIALUTILS_H

#include "GF.h"
#include "MethodsFactory.h"
#include "Potencia.h"
#include "Random.h"
#include "Factor.h"
#include <cassert>


namespace mpplas{

  namespace PolynomialUtils{

    template<typename T>
      bool isIrreducible(const T& fx, const Z& p);
    template<typename T>
      T generateIrreducible(const int degree, const Z& p);
    template<typename T>
      bool isPrimitive(const T& fx, const MiVec<Z>& factors, const Z& p);
    template<typename T>
      T generatePrimitive(const int degree, const MiVec<Z>& factors, const Z& p);
  }; /* namespace PolynomialUtils */


  ////////////////////////////

  namespace PolynomialUtils {
    template<typename T>
      bool isIrreducible(const T& fx, const Z& p ){
        //fx has to be monic
        if( !fx.isMonic() ){
          T tmp(fx);
          tmp.makeMonic();
          return isIrreducible(tmp,p);
        }

        assert( fx.getCharacteristic() == p );
        const int m = fx.getDegree();
        const T x(1, 1, p);
        typename T::GF u(x,fx); 
        Exponentiation< typename T::GF > *potMod; 
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
          } while(fx[0].esCero());

          for( int i = 1; i < m; i++){
            fx[i] = rnd->getIntegerBounded(p);
          }
        }
        while( !isIrreducible(fx, p) );

        return fx;

      }


    template<typename T>
      bool isPrimitive(const T& fx,const Z& p){
        // fx has to be monic
        if( !fx.isMonic() ){
          T tmp(fx);
          tmp.makeMonic();
          return isPrimitive(tmp,p);
        }

        if( !isIrreducible(fx, p) ){ // primitive => irreducible
          return false;
        } 
        Exponentiation< typename T::GF > *potMod; 
        mpplas::Factoriza* factorize;

        MethodsFactory::getReference().getFunc(potMod);
        MethodsFactory::getReference().getFunc(factorize);

        const MiVec<Z>& factors( factorize->factoriza( ( p ^ fx.getDegree() )-1 ) );
        const int m( fx.getDegree() );
        const typename T::GF lx(T(1,1, p), fx);
        typename T::GF ltmp(lx);
        const Z pM_1( ((p ^ m) -1) );
        for(int i = 0 ; i < factors.size(); i++){
          potMod->exponentiation(&ltmp, pM_1 / factors[i]);
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
        } while( !isPrimitive(fx,p) );

        return fx;
      }
  }

}
#endif
