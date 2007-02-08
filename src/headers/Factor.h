/* 
 * $Id$
 */

#ifndef __FACTOR_H
#define __FACTOR_H

#include "Z.h"
#include "AbstractMethod.h"

namespace numth{

  class CadenaAlgFactor;

  /** Interfaz para la factorización de enteros
   *
   *  Clase base para métodos de factorización de enteros en sus
   *  factores primos.
   *
   */
  class Factoriza : public AbstractMethod
  {
    public:
      /** Determinación de los factores primos de un entero.
       *
       * Este método devuelve el conjunto de factores primos
       * resultado de la factorización del entero que recibe como
       * parámetro. Si existe alguna potencia de primo en dicha
       * factorización, tal primo se devolverá tantas veces como
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
  
  /** Interfaz para algoritmos de obtención de divisores no triviales.
   *
   *  Clase base para métodos de factorización que devuelven factores 
   *  no triviales de un entero, aunque no necesariamente la
   *  factorización completa del mismo ni tampoco factores primos.
   *
   */ 
  class FactorZ 
  {
    public:
      /** Obtención de factores no triviales.
       *
       * Se trata de obtener factores no triviales de un número. El
       * número puede no resultar totalmente factorizado ni se
       * garantiza que los factores no triviales encontrados sean
       * además primos.
       * 
       * @param n Puntero al entero del que obtener los factores no
       * triviales. Tras el retorno del método, habrá sido dividido
       * entre los factores que se hubieran encontrado.
       * @param factores Puntero a MiVec<Z> donde se almacenarán los
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
  /** Cadena de factorizaciones por omisión.
   *
   * Se realiza una secuencia de factorización utilizando los métodos
   * del tipo FactorZ que la librería implementa por omisión.
   */
  class CadenaAlgFactor : public Factoriza
  {
    public:
      virtual MiVec<Z> factoriza(const Z& num);

      virtual ~CadenaAlgFactor(){}
  };


//  /** Algoritmo de factorización por TODO
//   *
//   * Descrito en %TODO.
//   */
//  class SQUFOF : public FactorZ
//  {
//    public:
//      virtual bool factorZ(Z* n, MiVec<Z>* factores);
//
//    protected:
//      /** Implementa la "reducción \f$rho\f$ como se describe en %TODO
//       * */
//      void reduccionRho(Z& A, Z& B, Z& C, const Z& D, const Z& d);
//      /** Reduce completamente mediante "reducción \f$rho\f$" */
//      void reducir(Z& A, Z& B, Z& C, const Z& D, const Z& d);
//  };
 
  /** Implementación del algoritmo de factorización de la \f$rho\f$ de
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
 
  /** Implementación del algoritmo de factorización por cribado.
   *
   * Descrito en 
   * The Art of Computer Programming Vol.2 pág. 364;\n
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
      
