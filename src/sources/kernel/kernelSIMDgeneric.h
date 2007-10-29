/* 
 * $Id$
 *
 */

#ifndef __KERNELSIMDGENERIC_H
#define __KERNELSIMDGENERIC_H

namespace mpplas{

  namespace SIMDCPU{ 
 
    template<typename T> 
      short getElementsPerSIMDDigit(){
        typedef typename SIMDDigit<T>::BasicType BasicType;
        return (sizeof(T)/sizeof(BasicType));
      }

    template<typename T>
      inline void Add(SIMDDigit<T>& out,const SIMDDigit<T>& arg1, const SIMDDigit<T>& arg2){
        typedef typename SIMDDigit<T>::BasicType BasicType;
        const BasicType* const a( (const BasicType* const) (&(arg1.data)) );
        const BasicType* const b( (const BasicType* const) (&(arg2.data)) );
        BasicType* const  c( (BasicType* const) (&(out.data)) );

        for(int i=0; i < getElementsPerSIMDDigit<T>(); i++){
          c[i] = a[i] + b[i];
        }
      }
 
    template<typename T>
      inline void Sub(SIMDDigit<T>& out,const SIMDDigit<T>& arg1, const SIMDDigit<T>& arg2){
        typedef typename SIMDDigit<T>::BasicType BasicType;
        const BasicType* const a( (const BasicType* const) (&(arg1.data)) );
        const BasicType* const b( (const BasicType* const) (&(arg2.data)) );
        BasicType*  const c( (BasicType* const)(&(out.data)) );

        for(int i=0; i < getElementsPerSIMDDigit<T>(); i++){
          c[i] = a[i] - b[i];
        }

      }

    template<typename T>
      inline void Mul(SIMDDigit<T>& out,const SIMDDigit<T>& arg1, const SIMDDigit<T>& arg2){
        typedef typename SIMDDigit<T>::BasicType BasicType;
        const BasicType* const a( (const BasicType* const) (&(arg1.data)) );
        const BasicType* const b( (const BasicType* const) (&(arg2.data)) );
        BasicType* const c( (BasicType* const) (&(out.data)) );

        for(int i=0; i < getElementsPerSIMDDigit<T>(); i++){
          c[i] = a[i] * b[i];
        }

      }

    template<typename T>
      inline void Div(SIMDDigit<T>& out,const SIMDDigit<T>& arg1, const SIMDDigit<T>& arg2){
        typedef typename SIMDDigit<T>::BasicType BasicType;
        const BasicType* const a( (const BasicType* const) (&(arg1.data)) );
        const BasicType* const b( (const BasicType* const) (&(arg2.data)) );
        BasicType* const c( (BasicType* const) (&(out.data)) );


        for(int i=0; i < getElementsPerSIMDDigit<T>(); i++){
          c[i] = a[i] / b[i];
        }

      }

    template<typename T>
      inline void Sum(typename SIMDDigit<T>::BasicType& out, SIMDDigit<T> arg1){
        typedef typename SIMDDigit<T>::BasicType BasicType;
        const BasicType* const in( (const BasicType* const) (&(arg1.data)) );
        out = BasicType();

        for( int i=0; i < getElementsPerSIMDDigit<T>(); i++){
          out += in[i];
        }
      }


    template<typename T>
      inline void Pack(SIMDDigit<T>& out, const typename SIMDDigit<T>::BasicType* const src){
        typedef typename SIMDDigit<T>::BasicType BasicType;
        BasicType* const c( (BasicType* const) (&(out.data)) );

        for(int i=0; i < getElementsPerSIMDDigit<T>(); i++){
          c[i] = src[i];
        }
      }


    template<typename T>
      inline void Unpack(typename SIMDDigit<T>::BasicType* const out, const SIMDDigit<T>& src ){
        typedef typename SIMDDigit<T>::BasicType BasicType;
        const BasicType* const c( (const BasicType* const) (&(src.data)) );

        for(int i=0; i < getElementsPerSIMDDigit<double2xSIMD_t>(); i++){
          out[i] = c[i];
        }
      }
  } /* namespace SIMDCPU */
} /* namespace mpplas */


#endif
