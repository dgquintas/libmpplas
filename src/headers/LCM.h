/* 
 * $Id$
 */

#ifndef __LCM_H
#define __LCM_H

#include "Z.h"
#include "AbstractMethod.h"

namespace mpplas{

  class LCMViaGCD;

   /** Interfaz para la función del mínimo común múltiplo. 
   * 
   * Clase base para algoritmos que implementen el cálculo del
   * mínimo común múltiplo.
   * 
   */
 class LCM : public AbstractMethod
  {
    public:

      LCM();

      /** Mínimo común múltiplo.
       *
       * Realiza el cálculo del mínimo común múltiplo de dos enteros.
       * 
       *  @param u,v Enteros de los que calcular el mínimo común
       *  múltiplo.
       * 
       * @return El mínimo común múltiplo de @a u y @a v.
       */
      virtual Z lcm(Z u, Z v ) = 0;
     /** Mínimo común múltiplo, versión especial precisión simple.
       *
       * Realiza el cálculo del mínimo común múltiplo de un entero y un
       * dato de precisión simple Digit.
       * 
       *  @param u Entero del que calcular el mínimo común múltiplo
       *  junto con @a v.
       *  @param v Digit de precisión simple de la que calcular el mínimo común múltiplo
       *  junto con @a u.
       *  
       * @return El mínimo común múltiplo de @a u y @a v.
       */
      virtual Z lcm(Z u, Digit v ); 

      /** Mínimo común múltiplo, versión especial precisión simple
       * con signo.
       *
       * Método análogo a gcd(Z u, Digit v).
       * Su razón de ser es evitar problemas si @a v es un tipo con
       * signo, por las conversiones automáticas que realiza C++.
       */
      virtual Z lcm(Z u, SignedDigit v ); 


      virtual ~LCM(){}


      typedef LCMViaGCD DFL;

    protected:
      Functions* const funcs;
  };

  
  /* implementaciones */
  /** Cálculo del mínimo común multiplo mediante relación con el
   * máximo común divisor.
   *
   * Se calcula el mínimo común múltiplo en base a que éste es igual a
   * \f$ \frac{|uv|}{\gcd(u,v)} \f$, con \f$\gcd(u,v)\f$ la función
   * del máximo común divisor. 
   */
  class LCMViaGCD : public LCM
  {
    public:
      using LCM::lcm;
      virtual Z lcm(Z u, Z v);
  };
  
}

#endif
  

  
