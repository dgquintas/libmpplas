/*
 * $Id$
 */

#include "Z_p.h"
#include "MethodsFactory.h"
#include "Primos.h"
#include "Errors.h"

namespace mpplas{

  Z_p Z_p::ZERO( (Digit)0, (Digit)0, false, false ); 
  Z_p Z_p::ONE ( (Digit)1, (Digit)0, false, false);

  const bool Z_p::groupCyclic(true);
  const bool Z_p::addCommutative(true); 

  const bool Z_p::multAssociative(true);
  const bool Z_p::multCommutative(true);
  const bool Z_p::unitaryRing(true);
  const bool Z_p::divisionRing(true);


  Z_p::Z_p( const Z& mod )throw(Errors::PrimeRequired)
    : Z_n(mod) {
      if ( !mod.esCero()){
        TestPrimoProb* primeTest;
        MethodsFactory::getReference().getFunc(primeTest);

        if( !primeTest->esPrimo( mod ) ){
          throw Errors::PrimeRequired();
        }
      }
    }
 
  Z_p::Z_p( const Z& num, const Z& mod, const bool reduce,const bool checkPrimality )throw(Errors::PrimeRequired)
    : Z_n(num, mod, reduce) {
      if( checkPrimality ){
        TestPrimoProb* primeTest;
        MethodsFactory::getReference().getFunc(primeTest);

        if( !primeTest->esPrimo( mod ) ){
          throw Errors::PrimeRequired();
        }
      }
    }

  Z_p::Z_p( const Z_p& src )
    : Z_n(src) {}
 
  Z_p::Z_p( const Z_n& src ) throw(Errors::PrimeRequired)
    : Z_n(src) {
      TestPrimoProb* primeTest;
      MethodsFactory::getReference().getFunc(primeTest);

      if( !primeTest->esPrimo( src.getMod() ) ){
        throw Errors::PrimeRequired("Non prime modulus for Z_p");
      }
    }


  Z_p& Z_p::operator=(const Z& integer) {
    Z_n::operator=(integer);
  }
  Z_p& Z_p::operator=(const Z_n& integer) {
    Z_n::operator=(integer);
  }

}
