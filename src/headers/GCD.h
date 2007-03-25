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

  /** Interfaz para la función del máximo común divisor. 
   * 
   * Clase base para algoritmos que implementen el cálculo del
   * máximo común divisor.
   * 
   */
  class GCD  : public AbstractMethod
  {
    public:
      /** Máximo común divisor.
       *
       * Realiza el cálculo del máximo común divisor de dos enteros.
       * 
       *  @param u,v Enteros de los que calcular el máximo común
       *  divisor.
       * 
       * @return El máximo común divisor de @a u y @a v.
       */
      virtual Z gcd(Z u, Z v ) = 0;

      /** Máximo común divisor, versión especial precisión simple.
       *
       * Realiza el cálculo del máximo común divisor de un entero y un
       * dato de precisión simple Cifra.
       * 
       *  @param u Entero del que calcular el máximo común divisor
       *  junto con @a v.
       *  @param v Cifra de precisión simple de la que calcular el máximo común divisor
       *  junto con @a u.
       *  
       * @return El máximo común divisor de @a u y @a v.
       *
       * @note La razón de ser de este método es que suele servir de
       * caso base para el método más general de los dos parámetros
       * enteros.
       * 
       */
      virtual Z gcd(Z u, Cifra v ); //Euclides

      /** Máximo común divisor, versión especial precisión simple
       * con signo.
       *
       * Método análogo a gcd(Z u, Cifra v).
       * Su razón de ser es evitar problemas si @a v es un tipo con
       * signo, por las conversiones automáticas que realiza C++.
       */
      virtual Z gcd(Z u, CifraSigno v ); 

      virtual ~GCD(){}

      typedef GCDLehmer DFL;
  };
 
  /** Interfaz para la versión extendida del máximo común divisor. 
   * 
   * Clase base para algoritmos que implementen el cálculo de la
   * versión extendida máximo común divisor.
   * Esto es, que devuelvan los coeficientes \f$C\f$ y \f$D\f$ de la
   * ecuación \f$d = Ca + Db\f$ para \f$d = \gcd(a,b)\f$.
   * 
   */
  class GCDExt : public AbstractMethod
  {
    public:
      /** Cálculo del máximo común divisor y coeficientes.
       *
       * @param x,y Enteros de los que calcular el máximo común
       * divisor.
       * @param C,D Coeficientes de @a x e @a y respectivamente en la
       * relación \f$d = Cx + Dy\f$ para \f$d = \gcd(x,y)\f$.
       */
      virtual Z gcdext(Z x, Z y, Z& C, Z& D) = 0;

      virtual ~GCDExt(){}

      typedef GCDExtBinario DFL;
  };


  /* implementaciones */
  /** Cálculo del máximo común divisor por el método de Lehmer.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.57
   *
   * @note Es el método que la librería utiliza por omisión.
   */
  class GCDLehmer : public GCD
  {
    public:
      using GCD::gcd;
      virtual Z gcd(Z u, Z v);

      virtual ~GCDLehmer(){}
  };

  /** Cálculo del máximo común divisor extendido por el método binario.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.61\n
   * The Art of Computer Programing Vol. 2, pág. 329, Alg. L
   *
   * @note Es el método que la librería utiliza por omisión.
   */
  class GCDExtBinario : public GCDExt
  {
    public:
      virtual Z gcdext(Z x, Z y, Z& C, Z& D);

      virtual ~GCDExtBinario(){}
      
  };
}

      
      
#endif 
