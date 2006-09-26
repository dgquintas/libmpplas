#ifndef __SIMBOLOSLEGENDRE_H
#define __SIMBOLOSLEGENDRE_H

#include "Z.h"

namespace numth{

  /** Interfaz para algoritmos que implementen el c�lculo del s�mbolo
   * de Legendre.
   */
  class SimboloLegendre
  {
    public:
      /** C�lculo del s�mbolo de Legendre.
       *
       * @param a,p Enteros correspondientes al s�mbolo de Legendre
       *            \f$ \left(\frac{a}{p}\right) \f$. \f$p\f$ ha de
       *            ser primo.
       *
       *  @return El s�mbolo de Legendre \f$ \left(\frac{a}{p}\right) \f$.
       *
       *  @note No se realizan comprobaciones de primalidad para
       *  \f$p\f$. El usuario es responsable de comprobar esto de
       *  antemano.
       */
      virtual Z simboloLegendre( Z a,  Z p) = 0;

      virtual ~SimboloLegendre(){}
  };

   /** Interfaz para algoritmos que implementen el c�lculo del s�mbolo
   * de Jacobi.
   */
class SimboloJacobi
  {
    public:
      /** C�lculo del s�mbolo de Jacobi.
       *
       * @param a,b Enteros correspondientes al s�mbolo de Jacobi
       *            \f$ \left(\frac{a}{b}\right) \f$. \f$b\f$ ha de
       *            ser impar.
       *
       *  @return El s�mbolo de Jacobi \f$ \left(\frac{a}{b}\right) \f$.
       *
       *  @note Si \f$b\f$ es par, se lanzar� una excepci�n de tipo Errores::ParEnSimboloJacobi.
       *  */
      virtual Z simboloJacobi( Z a,  Z b) = 0;

      virtual ~SimboloJacobi(){}
  };
 
  
   /** Interfaz para algoritmos que implementen el c�lculo del s�mbolo
   * de Kronecker.
   */
 class SimboloKronecker
  {
    public:
      /** C�lculo del s�mbolo de Kronecker.
       *
       * @param a,b Enteros correspondientes al s�mbolo de Kronecker
       *            \f$ \left(\frac{a}{b}\right) \f$. 
       *
       *  @return El s�mbolo de Kronecker \f$ \left(\frac{a}{b}\right) \f$.
       */
      virtual Z simboloKronecker( Z a,  Z b) = 0;

      virtual ~SimboloKronecker(){}
  };

  /* IMPLEMENTACIONES */

  /** Implementaci�n del s�mbolo de Legendre v�a el s�mbolo de Jacobi
   * */
  class SLegendreViaJacobi : public SimboloLegendre
  {
    public:
      Z simboloLegendre(Z a, Z p);
  };
  typedef SLegendreViaJacobi SimboloLegendreDFL;
  
   /** Implementaci�n del s�mbolo de Jacobi v�a el s�mbolo de
    * Kronecker
   * */
 class SJacobiViaKronecker : public SimboloJacobi
  {
    public:
      Z simboloJacobi(Z a, Z b);
  };
  typedef SJacobiViaKronecker SimboloJacobiDFL;
  
  
  /** Implementaci�n del s�mbolo de Kronecker segun Cohen.
   * 
   * Implementaci�n siguiendo lo dicho en 
   * A course in computational algebraic number theory, p�g. 29 
   */
  class SKroneckerCohen : public SimboloKronecker
  {
    public:
      SKroneckerCohen(void); //inicializa la tabla 
      virtual Z simboloKronecker( Z a,  Z b);

    private:
      CifraSigno tabla[8];

  };
  typedef SKroneckerCohen SimboloKroneckerDFL;

      
  
}






#endif
