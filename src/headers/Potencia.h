/* 
 * $Id$
 */

#ifndef __POTENCIA_H
#define __POTENCIA_H

#include <vector>

#include "R.h"
#include "Z.h"
#include "Z_n.h"
#include "Z_px.h"
#include "AbstractMethod.h"
#include "MethodsFactory.h"
#include "RedModular.h"

namespace mpplas{

  class PotVentanaDeslizante;
  class PotVentanaDeslizanteR;
  class PotRightLeft;
  class PotMontgomery;
  class ClasicoConBarrett;
  class TwoThreadedModularExp;
  class MultiThreadedModularExp;

  // la razon de que el exponente se considere con signo pese a no
  // poder realizarse exponenciaciones negativas en enteros es para
  // evitar que un número con signo se "colase" bajo la interpretacion
  // sin signo, obteniendo, por ejemplo, el valor 2^32-1 para -1
  /** Interfaz para potenciación en enteros.
   *
   * Clase base para algoritmos que implementen la potenciación sobre
   * enteros.
   * 
   */
  template<typename T>
  class ExponentiationBase :  public AbstractMethod {
    public:
      /** Potenciación "in-situ".
       *
       * Realizar una potenciación "in-situ". Es ligeramente más
       * eficiente al no necesitar operaciones de copia en el paso de
       * parametros y devolución del resultado.
       * 
       *  @param base Puntero a entero que inicialmente contiene la
       *  base de la operación y el cual se modifica para contener el
       *  resultado al final. 
       *   
       * @param exp Exponente de la operación de potenciación. 
       *
       * @exception Se devuelve Errores::PunteroNulo si @a n o @a
       *  factores son punteros iguales a NULL.
       * 
       *  @note La razón de que el argumento @a exp sea de tipo
       *  SignedDigit cuando no puede ser negativo es para evitar
       *  problemas de conversión automática por parte de C++ entre
       *  tipos con y sin signo.
       */
      virtual void exponentiation(T* const base, const Z& exp) = 0; 

      /** Potenciación.
       *
       * Realiza una potenciación devolviendo el entero resultante.
       * 
       *  @param base Entero base de la potenciación.
       * 
       * @param exp Exponente de la operación de potenciación. El
       *  paso de un valor negativo provocará una excepción
       *  "ExponenteNegativo". 
       *
       * @return El entero resultado de \f$base^{exp}\f$.
       * 
       *  @note La razón de que el argumento @a exp sea de tipo
       *  SignedDigit cuando no puede ser negativo es para evitar
       *  problemas de conversión automática por parte de C++ entre
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
  
  
  /** Interfaz para potenciación modular.
   *
   * Clase base para algoritmos que implementen la potenciación
   * modular sobre enteros.
   * 
   */
  template<>
  class Exponentiation< Z_n > : public ExponentiationBase< Z_n >{
    public:
      Exponentiation();

       /** Potenciación modular "in-situ".
       *
       * Realizar una potenciación modular "in-situ". Es ligeramente más
       * eficiente al no necesitar operaciones de copia en el paso de
       * parametros y devolución del resultado.
       * 
       *  @param base Puntero a entero que inicialmente contiene la
       *  base de la operación y el cual se modifica para contener el
       *  resultado al final. El paso de un puntero nulo provocará una
       *  excepción de tipo "PunteroNulo"
       * 
       * @param exp Exponente de la operación de potenciación.
       * Si el módulo @a mod suministrado no es primo y se pasa un
       * valor de exponente negativo, se producirá un error de tipo
       * "NonInvertibleElement".
       *
       * @param mod El módulo reductor.
       */
//      virtual void potModular(Z* const base, const Z& exp, const Z& mod) = 0; 
  
      /** Potenciación modular.
       *
       * Realizar una potenciación modular devolviendo el resultado.
       * 
       *  @param base Entero base de la potenciación.
       * 
       * @param exp Exponente de la operación de potenciación.
       * Si el módulo @a mod suministrado no es primo y se pasa un
       * valor de exponente negativo, se producirá un error de tipo
       * "NonInvertibleElement".
       *
       * @param mod El módulo reductor.
       *
       * @return El entero resultado de \f$base^{exp} \bmod mod\f$.
       */
//      Z potModular(Z base, const Z& exp, const Z& mod); 
 
      /** Cálculo de la inversa.
       *
       * Realizar el cálculo de la inversa en un cuerpo finito.
       * 
       * @param base Entero a invertir.
       * 
       * @param mod El módulo reductor. Si este valor no es primo, se
       * producirá un error de tipo "NonInvertibleElement".
       *
       * @return El entero resultado de \f$base^{-1} \bmod mod\f$.
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


  template<>
  class Exponentiation< Z_px > : public ExponentiationBase< Z_px >{
    public:
      virtual ~Exponentiation(){}

//      typedef BLABLA DFL; TODO
  };



  /* IMPLEMENTACIONES */
  /** Potenciación entera mediante el algoritmo de la ventana
   * deslizante.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.85
   *
   * @note Es el método que la librería utiliza por omisión.
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
  /** Potenciación modular entera mediante el método de Montgomery.
   * 
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.94.
   *
   */
  class PotMontgomery : public Exponentiation<Z_n>   {
    public:
      virtual void exponentiation(Z_n* const base, const Z& exp); 

      virtual ~PotMontgomery(){}
  };
 
  /** Potenciación modular entera utilizando reducción de Barrett.
   * 
   * Descrito en "Implementing the RSA public key encryption algorithm 
   * on a standard digital signal processor", Paul Barrett, 1986.
   *
   * @note Es el método que la librería utiliza por omisión.
   *
   */
  class ClasicoConBarrett : public Exponentiation<Z_n>
  {
    public:
      ClasicoConBarrett();
      virtual void exponentiation(Z_n* const base, const Z& exp); 
      void barrettStep(Z_n* const base, const Z& exp, const Z& mu) const ; 
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

};

    

#endif
