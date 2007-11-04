/* 
 * $Id$
 */

#ifndef __GCD_H
#define __GCD_H

#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "Z.h"
#include "MiVec.h"
#include "AbstractMethod.h"
#include "Errors.h"
#include "omp_mock.h"
#include "SystemInfo.h"

namespace mpplas{

  class GCDLehmer;
  class GCDExtBinario;

  /** Interfaz para la función del máximo común divisor. 
   * 
   * Clase base para algoritmos que implementen el cálculo del
   * máximo común divisor.
   * 
   */
  template<typename T>
  class GCDBase  : public AbstractMethod  {
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
      virtual T gcd(T u, T v ) = 0;
      T gcd( const MiVec<T>& nums ) throw(Errors::InvalidArgument) ;

      virtual ~GCDBase(){}
  };
  template<typename T>
    class GCD {};

  /** Interfaz para la versión extendida del máximo común divisor. 
   * 
   * Clase base para algoritmos que implementen el cálculo de la
   * versión extendida máximo común divisor.
   * Esto es, que devuelvan los coeficientes \f$C\f$ y \f$D\f$ de la
   * ecuación \f$d = Ca + Db\f$ para \f$d = \gcd(a,b)\f$.
   * 
   */
  template<typename T>
  class GCDExtBase : public AbstractMethod
  {
    public: 
      /** Cálculo del máximo común divisor y coeficientes.
         *
         * @param x,y Enteros de los que calcular el máximo común
         * divisor.
         * @param C,D Coeficientes de @a x e @a y respectivamente en la
         * relación \f$d = Cx + Dy\f$ para \f$d = \gcd(x,y)\f$.
         */
      virtual T gcdext(T x, T y, T* const C, T* const D) = 0;
      virtual ~GCDExtBase(){}
  };
  template<typename T>
    class GCDExt {};


  /////////////////////////////////////////////////////////////

  template<>
    class GCD<Z> : public GCDBase<Z> {
      public:
        /** Máximo común divisor, versión especial precisión simple.
         *
         * Realiza el cálculo del máximo común divisor de un entero y un
         * dato de precisión simple Digit.
         * 
         *  @param u Entero del que calcular el máximo común divisor
         *  junto con @a v.
         *  @param v Digit de precisión simple de la que calcular el máximo común divisor
         *  junto con @a u.
         *  
         * @return El máximo común divisor de @a u y @a v.
         *
         * @note La razón de ser de este método es que suele servir de
         * caso base para el método más general de los dos parámetros
         * enteros.
         * 
         */
        Z _gcd(Z u, Digit v ); //Euclides

        /** Máximo común divisor, versión especial precisión simple
         * con signo.
         *
         * Método análogo a gcd(Z u, Digit v).
         * Su razón de ser es evitar problemas si @a v es un tipo con
         * signo, por las conversiones automáticas que realiza C++.
         */
        Z _gcd(Z u, SignedDigit v ); 

        virtual ~GCD(){};
        typedef GCDLehmer DFL;
    };

  template<>
    class GCDExt<Z> : public GCDExtBase<Z> {
      public:
        virtual ~GCDExt(){}
        typedef GCDExtBinario DFL;
    };







  //////////////////////////////////////////////////////////////


  /* implementaciones */
  /** Cálculo del máximo común divisor por el método de Lehmer.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.57
   *
   * @note Es el método que la librería utiliza por omisión.
   */
  class GCDLehmer : public GCD<Z> {
    public:
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
  class GCDExtBinario : public GCDExt<Z>
  {
    public:
      virtual Z gcdext(Z x, Z y, Z* const C, Z* const D);

      virtual ~GCDExtBinario(){}
  };



//////////////////////////////////////////////////////////////////

  template<typename T>
  T GCDBase<T>::gcd( const MiVec<T>& nums ) throw( Errors::InvalidArgument ){
    if( nums.empty() ){
      throw Errors::InvalidArgument("Empty list for multiple-argument GCD");
    }
    else if( nums.size() == 1 ){
      return nums[0];
    }
 
    T* const gcds(new T[omp_get_max_threads()]);
    const int chunk_size = (int)ceil( ((float)nums.size())/omp_get_max_threads() );
    
    const int listSize( nums.size() );
    int cont = 1;

#pragma omp parallel for schedule(static,1)
    for( int i=0; i < listSize; i+= chunk_size){

      T d;
      if( (listSize - i) == 1 ){
        d = nums[i];
      }
      else{
        d = gcd( nums[i], nums[i+1] );
        if( d == T::getMultIdentity() ){
#pragma omp atomic
          cont--;

        }
        else{
#undef min
          const int real_cs = std::min( chunk_size, (int)listSize - i );
          for( int j = 0; (j < real_cs-2) && cont; j++){
            d = gcd(d, nums[i+2+j]);
            if( d == T::getMultIdentity() ){
#pragma omp atomic
              cont--;

            }
          }
        }
      }

      gcds[omp_get_thread_num()] = d;
    } //end omp parallel for

    T commonGCD;
    if( !cont ) { //at least one gcd was 1
      commonGCD = T::getMultIdentity();
    }
    else{
      if( SystemInfo::getMaxNumberOfThreads() == 1 ){
        commonGCD = gcds[0];
      }
      else{
        commonGCD = gcd(gcds[0], gcds[1]);
        for(int i = 2; i < SystemInfo::getMaxNumberOfThreads(); i++){
          commonGCD = gcd( commonGCD, gcds[i] );
          if( commonGCD == T::getMultIdentity() ){
            break;
          }
        }
      }
    }

    delete[] gcds;
    return commonGCD;

  }
}
      
      
#endif 
