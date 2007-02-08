/* 
 * $Id$
 */

#ifndef __FACTOR_H
#define __FACTOR_H

#include "Z.h"
#include "AbstractMethod.h"

namespace numth{

  class CadenaAlgFactor;

  /** Interfaz para la factorizaci�n de enteros
   *
   *  Clase base para m�todos de factorizaci�n de enteros en sus
   *  factores primos.
   *
   */
  class Factoriza : public AbstractMethod
  {
    public:
      /** Determinaci�n de los factores primos de un entero.
       *
       * Este m�todo devuelve el conjunto de factores primos
       * resultado de la factorizaci�n del entero que recibe como
       * par�metro. Si existe alguna potencia de primo en dicha
       * factorizaci�n, tal primo se devolver� tantas veces como
       * indique la potencia.
       * 
       * @param num Entero a factorizar.
       *
       * @return Estructura conteniendo los factores primos de @a num. 
       * */
      virtual MiVec<Z> factoriza(const Z& num) = 0;
    
      virtual ~Factoriza(){}


      typedef CadenaAlgFactor DFL;
  };
  
  /** Interfaz para algoritmos de obtenci�n de divisores no triviales.
   *
   *  Clase base para m�todos de factorizaci�n que devuelven factores 
   *  no triviales de un entero, aunque no necesariamente la
   *  factorizaci�n completa del mismo ni tampoco factores primos.
   *
   */ 
  class FactorZ 
  {
    public:
      /** Obtenci�n de factores no triviales.
       *
       * Se trata de obtener factores no triviales de un n�mero. El
       * n�mero puede no resultar totalmente factorizado ni se
       * garantiza que los factores no triviales encontrados sean
       * adem�s primos.
       * 
       * @param n Puntero al entero del que obtener los factores no
       * triviales. Tras el retorno del m�todo, habr� sido dividido
       * entre los factores que se hubieran encontrado.
       * @param factores Puntero a MiVec<Z> donde se almacenar�n los
       * factores no triviales encontrados.
       *
       * @exception Se devuelve Errores::PunteroNulo si @a n o @a
       * factores son punteros iguales a NULL.
       *
       */ 
      virtual bool factorZ(Z* n, MiVec<Z>* factores) = 0;

      virtual ~FactorZ(){}
  };


  /* implementacion */
  /** Cadena de factorizaciones por omisi�n.
   *
   * Se realiza una secuencia de factorizaci�n utilizando los m�todos
   * del tipo FactorZ que la librer�a implementa por omisi�n.
   */
  class CadenaAlgFactor : public Factoriza
  {
    public:
      virtual MiVec<Z> factoriza(const Z& num);

      virtual ~CadenaAlgFactor(){}
  };


//  /** Algoritmo de factorizaci�n por TODO
//   *
//   * Descrito en %TODO.
//   */
//  class SQUFOF : public FactorZ
//  {
//    public:
//      virtual bool factorZ(Z* n, MiVec<Z>* factores);
//
//    protected:
//      /** Implementa la "reducci�n \f$rho\f$ como se describe en %TODO
//       * */
//      void reduccionRho(Z& A, Z& B, Z& C, const Z& D, const Z& d);
//      /** Reduce completamente mediante "reducci�n \f$rho\f$" */
//      void reducir(Z& A, Z& B, Z& C, const Z& D, const Z& d);
//  };
 
  /** Implementaci�n del algoritmo de factorizaci�n de la \f$rho\f$ de
   * Pollard.
   *
   * Descrito en %TODO.
   */
  class RhoPollard : public FactorZ
  {
    public:
      virtual bool factorZ(Z* n, MiVec<Z>* factores);

      virtual ~RhoPollard(){}

  };
 
  /** Implementaci�n del algoritmo de factorizaci�n por cribado.
   *
   * Descrito en 
   * The Art of Computer Programming Vol.2 p�g. 364;\n
   * %TODO
   */
  class Trial : public FactorZ
  {
    public:
      virtual bool factorZ(Z* n, MiVec<Z>* factores);
  
      virtual ~Trial(){}
  };

}

#endif
      
