/* 
 * $Id$
 */

#ifndef __LCM_H
#define __LCM_H

#include "Z.h"
#include "AbstractMethod.h"

namespace mpplas{

  class LCMViaGCD;

   /** Interfaz para la funci�n del m�nimo com�n m�ltiplo. 
   * 
   * Clase base para algoritmos que implementen el c�lculo del
   * m�nimo com�n m�ltiplo.
   * 
   */
 class LCM : public AbstractMethod
  {
    public:

      LCM();

      /** M�nimo com�n m�ltiplo.
       *
       * Realiza el c�lculo del m�nimo com�n m�ltiplo de dos enteros.
       * 
       *  @param u,v Enteros de los que calcular el m�nimo com�n
       *  m�ltiplo.
       * 
       * @return El m�nimo com�n m�ltiplo de @a u y @a v.
       */
      virtual Z lcm(Z u, Z v ) = 0;
     /** M�nimo com�n m�ltiplo, versi�n especial precisi�n simple.
       *
       * Realiza el c�lculo del m�nimo com�n m�ltiplo de un entero y un
       * dato de precisi�n simple Digit.
       * 
       *  @param u Entero del que calcular el m�nimo com�n m�ltiplo
       *  junto con @a v.
       *  @param v Digit de precisi�n simple de la que calcular el m�nimo com�n m�ltiplo
       *  junto con @a u.
       *  
       * @return El m�nimo com�n m�ltiplo de @a u y @a v.
       */
      virtual Z lcm(Z u, Digit v ); 

      /** M�nimo com�n m�ltiplo, versi�n especial precisi�n simple
       * con signo.
       *
       * M�todo an�logo a gcd(Z u, Digit v).
       * Su raz�n de ser es evitar problemas si @a v es un tipo con
       * signo, por las conversiones autom�ticas que realiza C++.
       */
      virtual Z lcm(Z u, SignedDigit v ); 


      virtual ~LCM(){}


      typedef LCMViaGCD DFL;

    protected:
      Functions* const funcs;
  };

  
  /* implementaciones */
  /** C�lculo del m�nimo com�n multiplo mediante relaci�n con el
   * m�ximo com�n divisor.
   *
   * Se calcula el m�nimo com�n m�ltiplo en base a que �ste es igual a
   * \f$ \frac{|uv|}{\gcd(u,v)} \f$, con \f$\gcd(u,v)\f$ la funci�n
   * del m�ximo com�n divisor. 
   */
  class LCMViaGCD : public LCM
  {
    public:
      using LCM::lcm;
      virtual Z lcm(Z u, Z v);
  };
  
}

#endif
  

  
