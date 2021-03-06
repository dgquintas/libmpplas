/* 
 * $Id$
 */

#ifndef __POTENCIA_H
#define __POTENCIA_H

#include <vector>

#include "R.h"
#include "Z.h"
#include "Z_n.h"
#include "AbstractMethod.h"
#include "MethodsFactory.h"
#include "RedModular.h"
#include "Polynomial.h"
#include "BitChecker.h"
#include "Errors.h"
#include "GFx.h"

namespace mpplas{

  class PotVentanaDeslizante;
  class PotVentanaDeslizanteR;
  class PotRightLeft;
  class PotMontgomery;
  class ClasicoConBarrett;
  class TwoThreadedModularExp;
  class MultiThreadedModularExp;
  template<typename S> class SqrAndMultPolyExp;
  class SqrAndMultGFExp;

  // la razon de que el exponente se considere con signo pese a no
  // poder realizarse exponenciaciones negativas en enteros es para
  // evitar que un n�mero con signo se "colase" bajo la interpretacion
  // sin signo, obteniendo, por ejemplo, el valor 2^32-1 para -1
  /** Interfaz para potenciaci�n en enteros.
   *
   * Clase base para algoritmos que implementen la potenciaci�n sobre
   * enteros.
   * 
   */
  template<typename T>
  class ExponentiationBase :  public AbstractMethod {
    public:
      /** Potenciaci�n "in-situ".
       *
       * Realizar una potenciaci�n "in-situ". Es ligeramente m�s
       * eficiente al no necesitar operaciones de copia en el paso de
       * parametros y devoluci�n del resultado.
       * 
       *  @param base Puntero a entero que inicialmente contiene la
       *  base de la operaci�n y el cual se modifica para contener el
       *  resultado al final. 
       *   
       * @param exp Exponente de la operaci�n de potenciaci�n. 
       *
       * @exception Se devuelve Errores::NullPointer si @a n o @a
       *  factores son punteros iguales a NULL.
       * 
       *  @note La raz�n de que el argumento @a exp sea de tipo
       *  SignedDigit cuando no puede ser negativo es para evitar
       *  problemas de conversi�n autom�tica por parte de C++ entre
       *  tipos con y sin signo.
       */
      virtual void exponentiation(T* const base, const Z& exp) = 0; 

      /** Potenciaci�n.
       *
       * Realiza una potenciaci�n devolviendo el entero resultante.
       * 
       *  @param base Entero base de la potenciaci�n.
       * 
       * @param exp Exponente de la operaci�n de potenciaci�n. El
       *  paso de un valor negativo provocar� una excepci�n
       *  "NegativeExponent". 
       *
       * @return El entero resultado de \f$base^{exp}\f$.
       * 
       *  @note La raz�n de que el argumento @a exp sea de tipo
       *  SignedDigit cuando no puede ser negativo es para evitar
       *  problemas de conversi�n autom�tica por parte de C++ entre
       *  tipos con y sin signo.
       */
      T exponentiation(T base, const Z& exp); 

      virtual ~ExponentiationBase(){}
  };
 

  template<typename T>
    class Exponentiation{};

  template<>
  class Exponentiation<Z> : public ExponentiationBase<Z> {
    public:
      virtual ~Exponentiation(){}

      typedef PotVentanaDeslizante DFL;
  };


  template<>
  class Exponentiation<R> : public ExponentiationBase<R> {
    public:
      virtual ~Exponentiation(){}

      typedef PotVentanaDeslizanteR DFL;
  };
  
  
  /** Interfaz para potenciaci�n modular.
   *
   * Clase base para algoritmos que implementen la potenciaci�n
   * modular sobre enteros.
   * 
   */
  template<>
  class Exponentiation< Z_n > : public ExponentiationBase< Z_n >{
    public:
      Exponentiation();

      /** In-place modular integer inverse.
       *
       * Inverts the given modular integer @a base in place.
       * 
       * @param base a pointer to the modular integer to invert.
       */
      void invert(Z_n* const base) const;
      Z_n inverse(Z_n base) const;

      void invert(Z* const base, const Z& mod) const;
      Z inverse(Z base, const Z& mod) const;


      virtual ~Exponentiation(){}

      typedef ClasicoConBarrett DFL;
    
    protected:
      MethodsFactory& funcs;

  };


    template<typename S>
    class Exponentiation< Polynomial<S> > : public ExponentiationBase< Polynomial<S> >{

      public:
        virtual ~Exponentiation(){}

        typedef SqrAndMultPolyExp<S> DFL;
    };

  template<>
    class Exponentiation< GFx > : public ExponentiationBase< GFx >{

      public:
        virtual ~Exponentiation(){}

        typedef SqrAndMultGFExp DFL;
    };


  /* IMPLEMENTACIONES */
  /** Potenciaci�n entera mediante el algoritmo de la ventana
   * deslizante.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.85
   *
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
   */
  class PotVentanaDeslizante : public Exponentiation<Z>
  {
    public:
      virtual void exponentiation(Z* const base, const Z& exp);

      virtual ~PotVentanaDeslizante(){}
  };

 
  
  class PotVentanaDeslizanteR : public Exponentiation<R>
  {
    public:
      virtual void exponentiation(R* const base, const Z& exp);

      virtual ~PotVentanaDeslizanteR(){}
  };

  
  /** Integer exponentiation by the "Left-to-right" algorithm
   *
   *
   * Described in Handbook of Applied Cryptography 615 
   *
   */
  class PotLeftRight : public Exponentiation<Z>
  {
    public:
      virtual void exponentiation(Z* const base, const Z& exp);

      virtual ~PotLeftRight(){}
  };
  


  /* modular */
  /** Potenciaci�n modular entera mediante el m�todo de Montgomery.
   * 
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.94.
   *
   */
  class PotMontgomery : public Exponentiation<Z_n>   {
    public:
      virtual void exponentiation(Z_n* const base, const Z& exp); 

      virtual ~PotMontgomery(){}
  };
 
  /** Potenciaci�n modular entera utilizando reducci�n de Barrett.
   * 
   * Descrito en "Implementing the RSA public key encryption algorithm 
   * on a standard digital signal processor", Paul Barrett, 1986.
   *
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
   *
   */
  class ClasicoConBarrett : public Exponentiation<Z_n> {
    public:
      ClasicoConBarrett();
      virtual void exponentiation(Z_n* const base, const Z& exp); 
      void barrettStep(Z* const base, const Z& exp, const Z& mod, const Z& mu) const ; 
      virtual ~ClasicoConBarrett(){}

    private:
      RedBarrett* redbarrett;

  };



  class TwoThreadedModularExp : public Exponentiation<Z_n> {
    public:
      virtual void exponentiation(Z_n* const base, const Z& exp); 

      virtual ~TwoThreadedModularExp(){};

    private:
      void _getOnePartitions(const Z& e, 
       std::vector<int>& diffsX, 
       std::vector<int>& diffsY );
  };


  class MultiThreadedModularExp : public Exponentiation<Z_n> {
    public:
      virtual void exponentiation(Z_n* const base, const Z& exp); 

      virtual ~MultiThreadedModularExp(){};

    private:
      static int _getExponentSections(Z e, std::vector< Z >& sections);

  };




  template<typename S>
  class SqrAndMultPolyExp: public Exponentiation< Polynomial<S> > {
    public:
      virtual void exponentiation(Polynomial<S>* const base, const Z& exp);

      virtual ~SqrAndMultPolyExp(){}
  };

  class SqrAndMultGFExp: public Exponentiation< GFx > {
    public:
      virtual void exponentiation(GFx* const base, const Z& exp);

      virtual ~SqrAndMultGFExp(){}
  };



  //////////////////////////////////////////

  template<typename S>
  void SqrAndMultPolyExp<S>::exponentiation(Polynomial<S>* const base, const Z& k){
    // k should verify 0 <= k < p^m-1 ; m = deg(fx)
    Polynomial<S> g(*base);
    base->makeOne();
    if( k.isZero() ){
      return;
    }
    if( k.isNegative() ){
      throw Errors::NegativeExponent();
    }
    
    Utils::BitChecker bc(k, true);
    if( bc.checkNext() ){
      (*base) = g;

    }
    while( bc.hasNext() ){
      g.square();
      if( bc.checkNext() ){
        (*base) *= g;
      }
    }
    return;
  }


};

    

#endif
