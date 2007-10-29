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
       * @exception Se devuelve Errores::PunteroNulo si @a n o @a
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
       *  "ExponenteNegativo". 
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

       /** Potenciaci�n modular "in-situ".
       *
       * Realizar una potenciaci�n modular "in-situ". Es ligeramente m�s
       * eficiente al no necesitar operaciones de copia en el paso de
       * parametros y devoluci�n del resultado.
       * 
       *  @param base Puntero a entero que inicialmente contiene la
       *  base de la operaci�n y el cual se modifica para contener el
       *  resultado al final. El paso de un puntero nulo provocar� una
       *  excepci�n de tipo "PunteroNulo"
       * 
       * @param exp Exponente de la operaci�n de potenciaci�n.
       * Si el m�dulo @a mod suministrado no es primo y se pasa un
       * valor de exponente negativo, se producir� un error de tipo
       * "NonInvertibleElement".
       *
       * @param mod El m�dulo reductor.
       */
//      virtual void potModular(Z* const base, const Z& exp, const Z& mod) = 0; 
  
      /** Potenciaci�n modular.
       *
       * Realizar una potenciaci�n modular devolviendo el resultado.
       * 
       *  @param base Entero base de la potenciaci�n.
       * 
       * @param exp Exponente de la operaci�n de potenciaci�n.
       * Si el m�dulo @a mod suministrado no es primo y se pasa un
       * valor de exponente negativo, se producir� un error de tipo
       * "NonInvertibleElement".
       *
       * @param mod El m�dulo reductor.
       *
       * @return El entero resultado de \f$base^{exp} \bmod mod\f$.
       */
//      Z potModular(Z base, const Z& exp, const Z& mod); 
 
      /** C�lculo de la inversa.
       *
       * Realizar el c�lculo de la inversa en un cuerpo finito.
       * 
       * @param base Entero a invertir.
       * 
       * @param mod El m�dulo reductor. Si este valor no es primo, se
       * producir� un error de tipo "NonInvertibleElement".
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
