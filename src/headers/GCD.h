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

  /** Interfaz para la funci�n del m�ximo com�n divisor. 
   * 
   * Clase base para algoritmos que implementen el c�lculo del
   * m�ximo com�n divisor.
   * 
   */
  template<typename T>
  class GCDBase  : public AbstractMethod  {
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
      virtual T gcd(T u, T v ) = 0;
      T gcd( const MiVec<T>& nums ) throw(Errors::InvalidArgument) ;

      virtual ~GCDBase(){}
  };
  template<typename T>
    class GCD {};

  /** Interfaz para la versi�n extendida del m�ximo com�n divisor. 
   * 
   * Clase base para algoritmos que implementen el c�lculo de la
   * versi�n extendida m�ximo com�n divisor.
   * Esto es, que devuelvan los coeficientes \f$C\f$ y \f$D\f$ de la
   * ecuaci�n \f$d = Ca + Db\f$ para \f$d = \gcd(a,b)\f$.
   * 
   */
  template<typename T>
  class GCDExtBase : public AbstractMethod
  {
    public: 
      /** C�lculo del m�ximo com�n divisor y coeficientes.
         *
         * @param x,y Enteros de los que calcular el m�ximo com�n
         * divisor.
         * @param C,D Coeficientes de @a x e @a y respectivamente en la
         * relaci�n \f$d = Cx + Dy\f$ para \f$d = \gcd(x,y)\f$.
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
        /** M�ximo com�n divisor, versi�n especial precisi�n simple.
         *
         * Realiza el c�lculo del m�ximo com�n divisor de un entero y un
         * dato de precisi�n simple Digit.
         * 
         *  @param u Entero del que calcular el m�ximo com�n divisor
         *  junto con @a v.
         *  @param v Digit de precisi�n simple de la que calcular el m�ximo com�n divisor
         *  junto con @a u.
         *  
         * @return El m�ximo com�n divisor de @a u y @a v.
         *
         * @note La raz�n de ser de este m�todo es que suele servir de
         * caso base para el m�todo m�s general de los dos par�metros
         * enteros.
         * 
         */
        Z _gcd(Z u, Digit v ); //Euclides

        /** M�ximo com�n divisor, versi�n especial precisi�n simple
         * con signo.
         *
         * M�todo an�logo a gcd(Z u, Digit v).
         * Su raz�n de ser es evitar problemas si @a v es un tipo con
         * signo, por las conversiones autom�ticas que realiza C++.
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
  /** C�lculo del m�ximo com�n divisor por el m�todo de Lehmer.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.57
   *
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
   */
  class GCDLehmer : public GCD<Z> {
    public:
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
