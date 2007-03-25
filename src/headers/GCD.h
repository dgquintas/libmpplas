/* 
 * $Id$
 */

#ifndef __GCD_H
#define __GCD_H

#include "Z.h"
#include "AbstractMethod.h"

namespace mpplas{

  class GCDLehmer;
  class GCDExtBinario;

  /** Interfaz para la funci�n del m�ximo com�n divisor. 
   * 
   * Clase base para algoritmos que implementen el c�lculo del
   * m�ximo com�n divisor.
   * 
   */
  class GCD  : public AbstractMethod
  {
    public:
      /** M�ximo com�n divisor.
       *
       * Realiza el c�lculo del m�ximo com�n divisor de dos enteros.
       * 
       *  @param u,v Enteros de los que calcular el m�ximo com�n
       *  divisor.
       * 
       * @return El m�ximo com�n divisor de @a u y @a v.
       */
      virtual Z gcd(Z u, Z v ) = 0;

      /** M�ximo com�n divisor, versi�n especial precisi�n simple.
       *
       * Realiza el c�lculo del m�ximo com�n divisor de un entero y un
       * dato de precisi�n simple Cifra.
       * 
       *  @param u Entero del que calcular el m�ximo com�n divisor
       *  junto con @a v.
       *  @param v Cifra de precisi�n simple de la que calcular el m�ximo com�n divisor
       *  junto con @a u.
       *  
       * @return El m�ximo com�n divisor de @a u y @a v.
       *
       * @note La raz�n de ser de este m�todo es que suele servir de
       * caso base para el m�todo m�s general de los dos par�metros
       * enteros.
       * 
       */
      virtual Z gcd(Z u, Cifra v ); //Euclides

      /** M�ximo com�n divisor, versi�n especial precisi�n simple
       * con signo.
       *
       * M�todo an�logo a gcd(Z u, Cifra v).
       * Su raz�n de ser es evitar problemas si @a v es un tipo con
       * signo, por las conversiones autom�ticas que realiza C++.
       */
      virtual Z gcd(Z u, CifraSigno v ); 

      virtual ~GCD(){}

      typedef GCDLehmer DFL;
  };
 
  /** Interfaz para la versi�n extendida del m�ximo com�n divisor. 
   * 
   * Clase base para algoritmos que implementen el c�lculo de la
   * versi�n extendida m�ximo com�n divisor.
   * Esto es, que devuelvan los coeficientes \f$C\f$ y \f$D\f$ de la
   * ecuaci�n \f$d = Ca + Db\f$ para \f$d = \gcd(a,b)\f$.
   * 
   */
  class GCDExt : public AbstractMethod
  {
    public:
      /** C�lculo del m�ximo com�n divisor y coeficientes.
       *
       * @param x,y Enteros de los que calcular el m�ximo com�n
       * divisor.
       * @param C,D Coeficientes de @a x e @a y respectivamente en la
       * relaci�n \f$d = Cx + Dy\f$ para \f$d = \gcd(x,y)\f$.
       */
      virtual Z gcdext(Z x, Z y, Z& C, Z& D) = 0;

      virtual ~GCDExt(){}

      typedef GCDExtBinario DFL;
  };


  /* implementaciones */
  /** C�lculo del m�ximo com�n divisor por el m�todo de Lehmer.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.57
   *
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
   */
  class GCDLehmer : public GCD
  {
    public:
      using GCD::gcd;
      virtual Z gcd(Z u, Z v);

      virtual ~GCDLehmer(){}
  };

  /** C�lculo del m�ximo com�n divisor extendido por el m�todo binario.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.61\n
   * The Art of Computer Programing Vol. 2, p�g. 329, Alg. L
   *
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
   */
  class GCDExtBinario : public GCDExt
  {
    public:
      virtual Z gcdext(Z x, Z y, Z& C, Z& D);

      virtual ~GCDExtBinario(){}
      
  };
}

      
      
#endif 
