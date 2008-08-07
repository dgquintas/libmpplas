/* 
 * $Id$
 */


#include <set> //para set de metodo SQUFOF
#include "Factor.h"
#include "MethodsFactory.h"
#include "Constants.h"
#include "Primos.h"
#include "GCD.h"
#include "RedModular.h"

namespace mpplas{


  MiVec< std::pair<Z, int> > Factoriza::factorsWithExps( const Z& num ){

    MiVec<Z> factors( this->factoriza(num) );

    std::sort(factors.begin(), factors.end());

    std::vector< std::pair<Z, int> > factorsWithE;

    for(int i = 0 ; i < factors.size(); ){
      const Z& current(factors[i]);
      int count = 1;
      while( (++i < factors.size()) && (factors[i] == current) ){
        count++;
      }
      factorsWithE.push_back( std::pair<Z, int>(current, count) );
    }

    return factorsWithE;
  }


  MiVec<Z> CadenaAlgFactor::factoriza(const Z& n) {
    MethodsFactory* const funcs = MethodsFactory::getInstance();
    PrimeTest* test; funcs->getFunc(test);
    MiVec<Z> factores; factores.clear();
    Trial trial;
    RhoPollard rho;
    Z num(n);

    Z factor;
    if( !test->isPrime(num) ){
      if( !trial.factorZ(&num,&factores) ){ // si el trial no ha factorizado por completo...
        rho.factorZ(&num,&factores);
        //if( !rho.factorZ(&num,&factores) ){
        //  ; //pondriase aqui lo siguiente a probar si lo hubiera
        //}
      }
    }
    else{ // es primo
      factores.push_back(num);
    }

    return factores;
  }  

  bool RhoPollard::factorZ(Z* n, MiVec<Z>* factores)
  {
    if( n == NULL ){
      throw Errors::NullPointer();
    }
    if( factores == NULL ){
      throw Errors::NullPointer();
    }

    // pag 91 Menezes
    MethodsFactory* const funcs = MethodsFactory::getInstance();
    RedBarrett* reduccion; funcs->getFunc(reduccion);
    Z mu = reduccion->precomputaciones(*n);
    PrimeTest* test; funcs->getFunc(test);
    Z a((Digit)2);
    Z b((Digit)2);
    Z d;

    if( test->isPrime(*n) ){
      factores->push_back(*n);
      return true;
    }
    int iteraciones = 0;
    while(++iteraciones <= Constants::COTA_FACTORIZACION_RHO){
      a.square();
      a++;
      reduccion->redBarrett(&a,*n,mu);

      b.square();
      b++;
      reduccion->redBarrett(&b,*n,mu);
      b.square();
      b++;
      reduccion->redBarrett(&b,*n,mu);

      d = Z::gcd( a - b, *n );

      if( (d > (Digit)1) && (d < (*n)) ){
        factores->push_back(d);
        (*n) /= d;
        if( test->isPrime(*n) ){
          factores->push_back(*n);
          return true;
        }
        mu = reduccion->precomputaciones(*n);
      }
      else if ( d == (*n) )
        assert(false); //FIXME
    }

    return false;

  }


  bool Trial::factorZ(Z* n, MiVec<Z>* factores) {
    if( n == NULL ){
      throw Errors::NullPointer();
    }
    if( factores == NULL ){
      throw Errors::NullPointer();
    }

    //pag. 364 Knuth

    if( n->isOne() ){
      factores->push_back( Z((Digit)1) );
      return true;
    }

    //antes de empezar, quitar los doses pudiera tener el
    //número en su descomposición prima. Esto se hace por ser algo
    //directo y rápido.
    const int doses = n->numDoses();
    if(doses){
      (*n) >>= doses;
      factores->insert(factores->end(), doses, Z((Digit)2));
    }

    Z q,r;
    int i = 1; //empezar en el 3, no en el 2 (ya se han quitado)
    while( i < Constants::COTA_FACTORIZACION_TRIAL ){
      divMod( *n, Constants::TABLA_PRIMOS_2000[i], &q, &r );
      if( r.isZero() ){
        factores->push_back(Z(Constants::TABLA_PRIMOS_2000[i]));
        (*n) = q;
        if( n->isOne() ) return true;
      }
      else{ // r != 0
        if( q <= Constants::TABLA_PRIMOS_2000[i] ){
          factores->push_back(*n);
          return true;
        }
        else{ // q > primos[k]
          i++;
        }
      }
    }

    return false;

  }



}
