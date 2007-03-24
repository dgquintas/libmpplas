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

   /** Clase base de algoritmos que implementen la reducción de
    * Barrett.
   */
  class RedBarrett  : public AbstractMethod
  {
    public:
      /** Reducción de Barrett.
       *
       * @param num Puntero a entero. Si es NULL, se lanza una
       * excepción de tipo Errores::PunteroNulo. En él se dejará
       * almacenado, al final, su valor inicial reducido módulo @a
       * mod.
       * @param mod Entero reductor.
       * @param precomp El entero \f$\mu\f$, precomputación descrita
       * por el método de Barrett.
       */
      virtual void redBarrett(Z* num, const Z& mod, const Z& precomp);

      /**  Realiza las precomputaciones del método. 
       *  @param modulo Entero representando el módulo reductor para
       *  el que se realizarán las precomputaciones.
       */
      virtual Z precomputaciones(const Z& modulo);
      
      virtual ~RedBarrett() {}


      typedef RedBarrett DFL;
//      
//    private:
//      Z mod_;
//      Z mu_;
  };
 
  /** Clase base de algoritmos que implementen la reducción de
    * Montgomery.
   */
  class RedMontgomery  : public AbstractMethod
  {
    public:
       /** Reducción de Montgomery.
       *
       * @param num Puntero a entero. Si es NULL, se lanza una
       * excepción de tipo Errores::PunteroNulo. En él se dejará
       * almacenado, al final, su valor inicial reducido módulo @a
       * mod.
       * @param mod Entero reductor.
       * @param precomp El entero \f$\mu\f$, precomputación descrita
       * por el método de Montgomery.
       */
      virtual void redMontgomery(Z* num, const Z& mod, const Z& precomp);
       /**  Realiza las precomputaciones del método. 
       *  @param modulo Entero representando el módulo reductor para
       *  el que se realizarán las precomputaciones.
       */
     virtual Z precomputaciones(const Z& modulo);

     virtual ~RedMontgomery() {}


     typedef RedMontgomery DFL;
//      
//    private:
//      Z mod_;
//      Z modPrima_;
  };
  

   /** Clase base de algoritmos que implementan reducción especial.
    * (ver descripción).
    *
    * La redución especial referida es aquella para la cual el módulo
    * tiene la forma \f$BASE^t - c\f$  con   \f$ \log_2(c) < t \f$.
   */
  class RedModularALaMersenne : public AbstractMethod // mod ~ BASE^t - c    ( lg_2(c) < t ) 
  {
    public:
       /** Reducción especial.
       *
       * Reducción para módulos de la forma
       * \f$BASE^t - c\f$  con   \f$ \log_2(c) < t \f$.
       *
       * @param num Puntero a entero. Si es NULL, se lanza una
       * excepción de tipo Errores::PunteroNulo. En él se dejará
       * almacenado, al final, su valor inicial reducido módulo @a
       * mod.
       * @param t Exponente de \f$BASE\f$ de la forma del módulo
       * anteriormente citada.
       * @param c Sustraendo del módulo 
       * anteriormente citado.
       */
      virtual void redModularALaMersenne(Z* num, const CifraSigno t, const CifraSigno c);

      virtual ~RedModularALaMersenne(){}


      typedef RedModularALaMersenne DFL;
  };

}

#endif
  
