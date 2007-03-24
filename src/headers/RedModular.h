/* 
 * $Id$
 */

#ifndef __REDMODULAR_H
#define __REDMODULAR_H

#include "Z.h"
#include "AbstractMethod.h"

namespace numth{

//  class RedModular
//  {
//    public:
//      virtual void redModular(Z* num, const Z& mod) = 0;
//      virtual Z redModular(Z num, const Z& mod);
//  };
// 
//  class RedModularEspecial
//  {
//    public:
//      virtual void redModularEspecial(Z* num, const CifraSigno t, const CifraSigno c) = 0;
//      virtual Z redModularEspecial(Z num, const CifraSigno t, const CifraSigno c);
//  };
 
  
  /* IMPLEMENTACIONES */

   /** Clase base de algoritmos que implementen la reducci�n de
    * Barrett.
   */
  class RedBarrett  : public AbstractMethod
  {
    public:
      /** Reducci�n de Barrett.
       *
       * @param num Puntero a entero. Si es NULL, se lanza una
       * excepci�n de tipo Errores::PunteroNulo. En �l se dejar�
       * almacenado, al final, su valor inicial reducido m�dulo @a
       * mod.
       * @param mod Entero reductor.
       * @param precomp El entero \f$\mu\f$, precomputaci�n descrita
       * por el m�todo de Barrett.
       */
      virtual void redBarrett(Z* num, const Z& mod, const Z& precomp);

      /**  Realiza las precomputaciones del m�todo. 
       *  @param modulo Entero representando el m�dulo reductor para
       *  el que se realizar�n las precomputaciones.
       */
      virtual Z precomputaciones(const Z& modulo);
      
      virtual ~RedBarrett() {}


      typedef RedBarrett DFL;
//      
//    private:
//      Z mod_;
//      Z mu_;
  };
 
  /** Clase base de algoritmos que implementen la reducci�n de
    * Montgomery.
   */
  class RedMontgomery  : public AbstractMethod
  {
    public:
       /** Reducci�n de Montgomery.
       *
       * @param num Puntero a entero. Si es NULL, se lanza una
       * excepci�n de tipo Errores::PunteroNulo. En �l se dejar�
       * almacenado, al final, su valor inicial reducido m�dulo @a
       * mod.
       * @param mod Entero reductor.
       * @param precomp El entero \f$\mu\f$, precomputaci�n descrita
       * por el m�todo de Montgomery.
       */
      virtual void redMontgomery(Z* num, const Z& mod, const Z& precomp);
       /**  Realiza las precomputaciones del m�todo. 
       *  @param modulo Entero representando el m�dulo reductor para
       *  el que se realizar�n las precomputaciones.
       */
     virtual Z precomputaciones(const Z& modulo);

     virtual ~RedMontgomery() {}


     typedef RedMontgomery DFL;
//      
//    private:
//      Z mod_;
//      Z modPrima_;
  };
  

   /** Clase base de algoritmos que implementan reducci�n especial.
    * (ver descripci�n).
    *
    * La reduci�n especial referida es aquella para la cual el m�dulo
    * tiene la forma \f$BASE^t - c\f$  con   \f$ \log_2(c) < t \f$.
   */
  class RedModularALaMersenne : public AbstractMethod // mod ~ BASE^t - c    ( lg_2(c) < t ) 
  {
    public:
       /** Reducci�n especial.
       *
       * Reducci�n para m�dulos de la forma
       * \f$BASE^t - c\f$  con   \f$ \log_2(c) < t \f$.
       *
       * @param num Puntero a entero. Si es NULL, se lanza una
       * excepci�n de tipo Errores::PunteroNulo. En �l se dejar�
       * almacenado, al final, su valor inicial reducido m�dulo @a
       * mod.
       * @param t Exponente de \f$BASE\f$ de la forma del m�dulo
       * anteriormente citada.
       * @param c Sustraendo del m�dulo 
       * anteriormente citado.
       */
      virtual void redModularALaMersenne(Z* num, const CifraSigno t, const CifraSigno c);

      virtual ~RedModularALaMersenne(){}


      typedef RedModularALaMersenne DFL;
  };

}

#endif
  
