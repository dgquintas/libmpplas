/* 
 * $Id$
 */

#ifndef __SIMBOLOSLEGENDRE_H
#define __SIMBOLOSLEGENDRE_H

#include "Z.h"
#include "AbstractMethod.h"

namespace mpplas{

  class SLegendreViaJacobi;
  class SJacobiViaKronecker;
  class SKroneckerCohen;
  /** Interfaz para algoritmos que implementen el cálculo del símbolo
   * de Legendre.
   */
  class SimboloLegendre : public AbstractMethod
  {
    public:
      /** Cálculo del símbolo de Legendre.
       *
       * @param a,p Enteros correspondientes al símbolo de Legendre
       *            \f$ \left(\frac{a}{p}\right) \f$. \f$p\f$ ha de
       *            ser primo.
       *
       *  @return El símbolo de Legendre \f$ \left(\frac{a}{p}\right) \f$.
       *
       *  @note No se realizan comprobaciones de primalidad para
       *  \f$p\f$. El usuario es responsable de comprobar esto de
       *  antemano.
       */
      virtual Z simboloLegendre( Z a,  Z p) = 0;

      virtual ~SimboloLegendre(){}

      typedef SLegendreViaJacobi DFL;
  };

   /** Interfaz para algoritmos que implementen el cálculo del símbolo
   * de Jacobi.
   */
class SimboloJacobi : public AbstractMethod
  {
    public:
      /** Cálculo del símbolo de Jacobi.
       *
       * @param a,b Enteros correspondientes al símbolo de Jacobi
       *            \f$ \left(\frac{a}{b}\right) \f$. \f$b\f$ ha de
       *            ser impar.
       *
       *  @return El símbolo de Jacobi \f$ \left(\frac{a}{b}\right) \f$.
       *
       *  @note Si \f$b\f$ es par, se lanzará una excepción de tipo Errores::EvenInJacobiSymbol.
       *  */
      virtual Z simboloJacobi( Z a,  Z b) = 0;

      virtual ~SimboloJacobi(){}
  
      typedef SJacobiViaKronecker DFL;
  };
 
  
   /** Interfaz para algoritmos que implementen el cálculo del símbolo
   * de Kronecker.
   */
 class SimboloKronecker : public AbstractMethod
  {
    public:
      /** Cálculo del símbolo de Kronecker.
       *
       * @param a,b Enteros correspondientes al símbolo de Kronecker
       *            \f$ \left(\frac{a}{b}\right) \f$. 
       *
       *  @return El símbolo de Kronecker \f$ \left(\frac{a}{b}\right) \f$.
       */
      virtual Z simboloKronecker( Z a,  Z b) = 0;

      virtual ~SimboloKronecker(){}
  
      typedef SKroneckerCohen DFL;
  };

  /* IMPLEMENTACIONES */

  /** Implementación del símbolo de Legendre vía el símbolo de Jacobi
   * */
  class SLegendreViaJacobi : public SimboloLegendre
  {
    public:
      Z simboloLegendre(Z a, Z p);
  };
  
   /** Implementación del símbolo de Jacobi vía el símbolo de
    * Kronecker
   * */
 class SJacobiViaKronecker : public SimboloJacobi
  {
    public:
      Z simboloJacobi(Z a, Z b);
  };
  
  
  /** Implementación del símbolo de Kronecker segun Cohen.
   * 
   * Implementación siguiendo lo dicho en 
   * A course in computational algebraic number theory, pág. 29 
   */
  class SKroneckerCohen : public SimboloKronecker
  {
    public:
      SKroneckerCohen(void); //inicializa la tabla 
      virtual Z simboloKronecker( Z a,  Z b);

    private:
      SignedDigit tabla[8];

  };

      
  
}






#endif
