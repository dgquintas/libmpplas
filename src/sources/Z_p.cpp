/*
 * $Id$
 */

#include "Z_p.h"
#include "MethodsFactory.h"
#include "Primos.h"
#include "Errors.h"

namespace mpplas{

  const Z_p Z_p::ZERO( (Digit)0, (Digit)0, false, false ); 
  const Z_p Z_p::ONE ( (Digit)1, (Digit)0, false, false);

  const bool Z_p::groupCyclic(true);
  const bool Z_p::addCommutative(true); 

  const bool Z_p::multAssociative(true);
  const bool Z_p::multCommutative(true);
  const bool Z_p::unitaryRing(true);
  const bool Z_p::divisionRing(true);


  Z_p::Z_p(const Z& mod, const bool checkPrimality )throw(Errors::PrimeRequired)
    : Z_n(mod) {
      if ( (!mod.isZero()) && checkPrimality) {
        PrimeTest* primeTest;
        MethodsFactory::getReference().getFunc(primeTest);

        if( !primeTest->isPrime( mod ) ){
          throw Errors::PrimeRequired();
        }
      }
    }
 
  Z_p::Z_p( const Z& num, const Z& mod, const bool reduce,const bool checkPrimality )throw(Errors::PrimeRequired)
    : Z_n(num, mod, reduce) {
      if( checkPrimality ){
        PrimeTest* primeTest;
        MethodsFactory::getReference().getFunc(primeTest);

        if( !primeTest->isPrime( mod ) ){
          throw Errors::PrimeRequired();
        }
      }
    }

  Z_p::Z_p( const Z_p& src )
    : Z_n(src) {}
 
  Z_p::Z_p( const Z_n& src ) throw(Errors::PrimeRequired)
    : Z_n(src) {
      PrimeTest* primeTest;
      MethodsFactory::getReference().getFunc(primeTest);

      if( !primeTest->isPrime( src.getMod() ) ){
        throw Errors::PrimeRequired("Non prime modulus for Z_p");
      }
    }


  Z_p& Z_p::operator=(const Z& integer) {
    Z_n::operator=(integer);
  }
  Z_p& Z_p::operator=(const Z_n& integer) {
    Z_n::operator=(integer);
  }


  Z_p& Z_p::makeZero(){
    Z::makeZero();
    return *this;
  }
  Z_p& Z_p::makeOne(){
    Z::makeOne();
    return *this;
  }
  Z_p& Z_p::invertSign(){
    Z_n::invertSign();
    return *this;
  }

}
