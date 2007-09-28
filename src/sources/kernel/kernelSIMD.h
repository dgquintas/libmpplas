/* 
 * $Id$
 */
#ifndef __KERNELSIMD_H
#define __KERNELSIMD_H

#include <ostream>


/** Generic SIMD kernel 
 *
 * Design based on the guidelines given at:
 * \par Why Not Specialize Function Templates?
 *  C/C++ Users Journal, 19(7), July 2001.
 *
 * @sa http://www.gotw.ca/publications/mill17.htm
 */

namespace mpplas{
  
 template <typename T, int A >
   class SSEAlloc {
     public:
       // type definitions
       typedef T        value_type;
       typedef T*       pointer;
       typedef const T* const_pointer;
       typedef T&       reference;
       typedef const T& const_reference;
       typedef std::size_t    size_type;
       typedef std::ptrdiff_t difference_type;

       // rebind allocator to type U
       template <class U>
         struct rebind {
           typedef SSEAlloc<U,A> other;
         };

       // return address of values
       pointer address (reference value) const {
         return &value;
       }
       const_pointer address (const_reference value) const {
         return &value;
       }

       /* constructors and destructor
        * - nothing to do because the allocator has no state
        */
       SSEAlloc() throw() {
       }
       SSEAlloc(const SSEAlloc&) throw() {
       }
       template <class U>
         SSEAlloc (const SSEAlloc<U,A>&) throw() {
         }
       ~SSEAlloc() throw() {
       }

       // return maximum number of elements that can be allocated
       size_type max_size () const throw() {
         return std::numeric_limits<std::size_t>::max() / sizeof(T);
       }

       // allocate but don't initialize num elements of type T
       pointer allocate (size_type num, const void* = 0) {
         void* mem;
         posix_memalign( &mem, A, num * sizeof( value_type ) );
         //mem = _mm_malloc(num * sizeof(value_type), A);
         pointer ret = reinterpret_cast< pointer >( mem );
         return ret;
       }

       // initialize elements of allocated storage p with value value
       void construct (pointer p, const T& value) {
         // initialize memory with placement new
         new((void*)p)T(value);
       }

       // destroy elements of initialized storage p
       void destroy (pointer p) {
         // destroy objects by calling their destructor
         p->~T();
       }

       // deallocate storage p of deleted elements
       void deallocate (pointer p, size_type num) {
         //_mm_free( (void*) p );
         free( (void*) p );
       }
   }; 

  /** Basic SIMD datatype.
   *
   * This datatype is meant to be used by structures and/or operators supporting
   * a SIMD schema. */
  template<typename T>
    struct SIMDDigit {
      SIMDDigit() {}
      SIMDDigit( const SIMDDigit<T>& src )
        : data(src.data) {}

      typedef typename SIMDtoBasicTypes<T>::BasicType BasicType;

      inline SIMDDigit& operator+=(const SIMDDigit<T>& rhs);
      inline SIMDDigit& operator-=(const SIMDDigit<T>& rhs);
      inline SIMDDigit& operator*=(const SIMDDigit<T>& rhs);
      inline SIMDDigit& operator/=(const SIMDDigit<T>& rhs);

      inline SIMDDigit& operator=(const SIMDDigit<T>& rhs);

        inline SIMDDigit& pack(const BasicType* const src);
        inline BasicType* unpack(BasicType* const out) const;
        inline BasicType sum() const;


      inline short getSize() const;

      T data;
    };

  namespace SIMDCPU {

        /** SIMD addition.
         *
         * Add two SIMDDigit.
         *
         * @param out The resulting SIMDDigit containing the sums
         * @param arg1 SIMDDigit containing the first addend
         * @param arg2 SIMDDigit containing the second addend  */
    template<typename SIMDTYPE>
        inline void Add(SIMDDigit<SIMDTYPE>& out, const SIMDDigit<SIMDTYPE>& arg1, const SIMDDigit<SIMDTYPE>& arg2);

        /** SIMD subtraction.
         *
         * Subtract two SIMDDigit.
         *
         * @param out The resulting SIMDDigit containing the differences
         * @param arg1 SIMDDigit containig the minuends
         * @param arg2 SIMDDigit containig the subtrahends  */
    template<typename SIMDTYPE>
        inline void Sub(SIMDDigit<SIMDTYPE>& out, const SIMDDigit<SIMDTYPE>& arg1, const SIMDDigit<SIMDTYPE>& arg2);

        /** SIMD multiplication.
         *
         * Multiply two SIMDDigit.
         *
         * @param out The resulting SIMDDigit containing the products
         * @param arg1 SIMDDigit containing the first factors
         * @param arg2 SIMDDigit containing the second factors  */
    template<typename SIMDTYPE>
        inline void Mul(SIMDDigit<SIMDTYPE>& out, const SIMDDigit<SIMDTYPE>& arg1, const SIMDDigit<SIMDTYPE>& arg2);

        /** SIMD division.
         *
         * Divide two SIMDDigit.
         *
         * @param out The resulting SIMDDigit containig the quotients
         * @param arg1 SIMDDigit containig the dividends
         * @param arg2 SIMDDigit containig the divisors */
    template<typename SIMDTYPE>
        inline void Div(SIMDDigit<SIMDTYPE>& out, const SIMDDigit<SIMDTYPE>& arg1, const SIMDDigit<SIMDTYPE>& arg2);

        /** Horizontal addition.
         *
         * Sums the individual values packed in @a arg1: \f$out = \sum_{e \in arg1} e$\f 
         *
         * @param out The resulting sum.
         * @param arg1 The SIMDDigit whose elements to sum. */
    template<typename SIMDTYPE>
        inline void Sum(typename SIMDDigit<SIMDTYPE>::BasicType& out, SIMDDigit<SIMDTYPE> arg1);

        /** Convert from an array of standard C++ types to SIMDDigit.
         *
         * @param out The resulting SIMDDigit containing the elements from @a src.
         * @param src An array of standard C++ type values   */
    template<typename SIMDTYPE>
        inline void Pack(SIMDDigit<SIMDTYPE>& out, const typename SIMDDigit<SIMDTYPE>::BasicType* const src);

        /** Convert from SIMDDigit to an array of standard C++ types.
         *
         * @param out An array of standard C++ type values containing
         * the values packed in @a src.
         * @param src A SIMDDigit. */
    template<typename SIMDTYPE>
        inline void Unpack(typename SIMDDigit<SIMDTYPE>::BasicType* const out, const SIMDDigit<SIMDTYPE>& src);

        /** Number of basic elements per SIMDDigit */
    template<typename SIMDTYPE>
        inline const short getElementsPerSIMDDigit();
      
  } /* namespace SIMDCPU */
} /* namespace mpplas */

#ifdef USESIMD_nosimd
#pragma __libmpplas_manual_include nosimd 
  #include "kernelSIMDgeneric.h"
#endif

  
#ifdef USESIMD_sse
#pragma __libmpplas_manual_include sse
  #include "kernelSIMDSSE.h"
#endif

#ifdef USESIMD_sse2
#pragma __libmpplas_manual_include sse2
  #include "kernelSIMDSSE2.h"
#endif

namespace mpplas{

  std::ostream& operator<<(std::ostream& out, const SIMDDigit<float4xSIMD_t>& v);
  std::ostream& operator<<(std::ostream& out, const SIMDDigit<double2xSIMD_t>& v);
  std::ostream& operator<<(std::ostream& out, const SIMDDigit<int8xSIMD_t>& v);


  template<typename T>
  SIMDDigit<T>& SIMDDigit<T>::operator+=(const SIMDDigit<T>& rhs){
    SIMDCPU::Add(*this, *this, rhs);
    return *this;
  }
  template<typename T>
  SIMDDigit<T>& SIMDDigit<T>::operator-=(const SIMDDigit<T>& rhs){
    SIMDCPU::Sub(*this, *this, rhs);
    return *this;
  }
  template<typename T>
  SIMDDigit<T>& SIMDDigit<T>::operator*=(const SIMDDigit<T>& rhs){
    SIMDCPU::Mul(*this, *this, rhs);
    return *this;
  }
  template<typename T>
  SIMDDigit<T>& SIMDDigit<T>::operator/=(const SIMDDigit<T>& rhs){
    SIMDCPU::Div(*this, *this, rhs);
    return *this;
  }

  template<typename T>
  SIMDDigit<T>& SIMDDigit<T>::operator=(const SIMDDigit<T>& rhs){
    this->data = rhs.data;
    return *this;
  }
  
  template<typename T>
    SIMDDigit<T>& SIMDDigit<T>::pack(const SIMDDigit<T>::BasicType* const src){
      SIMDCPU::Pack(*this, src);
      return *this;
    }

  template<typename T>
    typename SIMDDigit<T>::BasicType* SIMDDigit<T>::unpack(SIMDDigit<T>::BasicType* const out) const {
      SIMDCPU::Unpack(out, *this);
      return out;
    }
 
  template<typename T>
    typename SIMDDigit<T>::BasicType SIMDDigit<T>::sum() const{
      typename SIMDDigit<T>::BasicType res;
      SIMDCPU::Sum(res, *this);
      return res;
    }


  template<typename T>
    short SIMDDigit<T>::getSize() const{
      return SIMDCPU::getElementsPerSIMDDigit<T>();
    }
 


} /* namespace mpplas */


#endif
