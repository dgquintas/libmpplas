/* 
 * $Id$
 */

#ifndef __POLYNOMIAL_H
#define __POLYNOMIAL_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <utility>
#include <set>
#include <cmath>

#include <iostream>

#include "Constraints.h"
#include "Ring.h"
#include "Field.h"
#include "MPPDataType.h"
#include "MiVec.h"
#include "Errors.h"
#include "MethodsFactory.h"
#include "GCD.h"
#include "Z.h"
#include "Z_p.h"
//#include "Digit_p.h"
#include "R.h"

namespace mpplas{

  template<typename S>
    class Polynomial : public MPPDataType {

      public: 
        /** Constructor for polynomials over S
         *
         * If @a ini is provided, the constant coefficient of the polynomial
         * is initialized with its value. Otherwise, S::getAddIdentity() is used.
         *
         * @param ini the value with which to initialize the polynomial's constant coefficient.
         * */
        Polynomial(const S& ini = S::getAddIdentity() );

        /** Constructor from textual representation. 
         *
         */
        Polynomial(const std::string& str, const S& ini = S() );

        /** Constructor from coefficient enumeration.
         *
         */
        Polynomial(const std::vector<S>& coeffs, const S& ini = S() );

        /** Constructor from a single coefficient.
         *
         */
        Polynomial(const S& coeff, const int exp, const S& ini = S() );



        /** Copy constructor for polynomials */
        Polynomial(const Polynomial<S>& src );

        /** Assignment operator */
        Polynomial<S>& operator=(const Polynomial<S>& src);


        Polynomial<S>& fromString(const std::string& str);

        inline S& operator[](int i);
        inline const S& operator[](int i) const;

        inline int getDegree() const;
        inline const S& getLeadingCoefficient() const;
        inline bool isMonic() const;
        Polynomial<S>& makeMonic() ;
        inline const S& getIni() const;

        bool isCoeffsDomainAField() const ;

        inline void makeZero();
        inline void makeOne();

        inline bool isZero() const;
        inline bool isOne() const;

        void changeSign();

        template<typename T>
          T evaluate(const T& x0) const;

        S getContent() const;
        Polynomial<S>& makePrimitive();

        bool operator==(const Polynomial<S>& rhs) const;
        bool operator<(const Polynomial<S>& rhs) const;

        virtual Polynomial<S>& operator+=(const Polynomial<S>& rhs);
        virtual Polynomial<S>& operator+=(const S& s);

        virtual Polynomial<S>& operator-=(const Polynomial<S>& rhs);
        virtual Polynomial<S>& operator-=(const S& s);

        virtual Polynomial<S>& operator*=(const Polynomial<S>& rhs);
        virtual Polynomial<S>& operator*=(const S& s); 
        virtual Polynomial<S>& square();

        virtual Polynomial<S>& operator/=(const Polynomial<S>& rhs);
        virtual Polynomial<S>& operator/=(const S& s); 

        virtual Polynomial<S>& operator%=(const Polynomial<S>& rhs);
        virtual Polynomial<S>& operator%=(const S& s); 

        static void divAndMod(Polynomial<S> lhs, const Polynomial<S>& rhs, Polynomial<S>* q, Polynomial<S>* r);

        virtual std::string toString() const;
        virtual std::string toHRString() const;

        virtual ~Polynomial(){
          //only conditions are that S must be a commutative ring 
          //with identity: Knuth 4.6 (p. 418). ie, a unique factorization domain (UFD)
          Constraints::must_have_base<S, Ring<S> > dummy1 __attribute__ ((__unused__));
          Constraints::must_have_base<S, MPPDataType > dummy2 __attribute__ ((__unused__));
          STATIC_ASSERT( S::multCommutative );
        }


      protected:


        /** Erase leading zeros.
         *
         * Makes the representation of a polynomial unique
         * by removing all the zero coefficients "in front" (ie, with a greater
         * exponent) of the non-zero coefficient with the greatest exponent.  */
        void _eraseLeadingZeros();


        /** Vector storing the coefficients from S */
        MiVec<S> _data;

        bool _isSaField;

        /** Value in S used as initialization value 
         * for the coefficients. 
         *
         * It is usually (and by default) S::getAddIdentitiy() */
        S _ini;

        template<typename U> 
          friend std::ostream& operator<<(std::ostream&, const Polynomial<U>& );

        template<typename U>
          friend std::istream& operator>>(std::istream&, Polynomial<U>& ) ;

      private:
        template<typename T>
          void _horner2ndOrder(T* const result, const T& x0) const ;
        void _ufdDivide(const Polynomial<S>& rhs, Polynomial<S>* const q, const bool reduce); 
        void _fieldDivide(const Polynomial<S>& rhs, Polynomial<S>* const q, const bool reduce ) ;
        void _reduce(const Polynomial<S>& rhs);
        void _divide(const Polynomial<S>& rhs);
        
  
  }; /* class polynomial */


  template<typename S>
    Polynomial<S> operator-(Polynomial<S> m); /**< Unary negation, sign inversion */

  template<typename S>
    Polynomial<S> operator+(Polynomial<S> lhs, const Polynomial<S>& rhs);
  template<typename S>
    Polynomial<S> operator-(Polynomial<S> lhs, const Polynomial<S>& rhs);
  template<typename S>
    Polynomial<S> operator*(Polynomial<S> lhs, const Polynomial<S>& rhs);
  template<typename S>
    Polynomial<S> operator/(Polynomial<S> lhs, const Polynomial<S>& rhs);
  template<typename S>
    Polynomial<S> operator%(Polynomial<S> lhs, const Polynomial<S>& rhs);

  template<typename S>
    Polynomial<S> operator+(Polynomial<S> lhs, const S& rhs);
  template<typename S>
    Polynomial<S> operator-(Polynomial<S> lhs, const S& rhs);
  template<typename S>
    Polynomial<S> operator*(Polynomial<S> lhs, const S& rhs);
  template<typename S>
    Polynomial<S> operator/(Polynomial<S> lhs, const S& rhs);
  template<typename S>
    Polynomial<S> operator%(Polynomial<S> lhs, const S& rhs);

  template<typename S>
    Polynomial<S> operator+(const S& lhs, Polynomial<S> rhs);
  template<typename S>
    Polynomial<S> operator-(const S& lhs, Polynomial<S> rhs);
  template<typename S>
    Polynomial<S> operator*(const S& lhs, Polynomial<S> rhs);
  template<typename S>
    Polynomial<S> operator/(const S& lhs, Polynomial<S> rhs);
  template<typename S>
    Polynomial<S> operator%(const S& lhs, Polynomial<S> rhs);


  ////////////////////////////////////////

  template<typename S>
  class GCDPolyCollins;

  template<typename S>
    class GCD< Polynomial<S> > : public GCDBase< Polynomial<S> > {
      public:
        virtual ~GCD(){};
        typedef GCDPolyCollins<S> DFL;
    };

  template<typename S>
  class GCDEuclid4Fields;


  template<typename S>
  class GCDExtPoly;

  template<typename S>
    class GCDExt< Polynomial<S> > : public GCDExtBase< Polynomial<S> > {
      public:
        virtual ~GCDExt(){}
        typedef GCDExtPoly<S> DFL;
    };

  template<>
  class GCD< Polynomial<Z_p> > : public GCDBase< Polynomial<Z_p> > {
    public:
      virtual ~GCD(){};
      typedef GCDEuclid4Fields<Z_p> DFL;
  };
  
//  template<>
//  class GCD< Polynomial<Digit_p> > : public GCDBase< Polynomial<Digit_p> > {
//    public:
//      virtual ~GCD(){};
//      typedef GCDEuclid4Fields<Digit_p> DFL;
//  };



  ////////////////////////////////////
  
  template<typename S>
    class GCDPolyKnuth : public GCD< Polynomial<S> >{
      public:
      virtual Polynomial<S> gcd( Polynomial<S> u, Polynomial<S> v );
    };
  template<typename S>
    class GCDPolyCollins: public GCD< Polynomial<S> >{
      public:
      virtual Polynomial<S> gcd( Polynomial<S> u, Polynomial<S> v );
    };
  
  template<typename S>
    class GCDExtPoly : public GCDExt< Polynomial<S> > {
      public:
        virtual Polynomial<S> gcdext(Polynomial<S> x, Polynomial<S> y, Polynomial<S>* const C, Polynomial<S>* const D);
    };
  template<typename S>
    class GCDEuclid4Fields: public GCD< Polynomial<S> >{
      public:
      virtual Polynomial<S> gcd( Polynomial<S> u, Polynomial<S> v );
    };


  #include "PolynomialImpl.h"

} /* namespace mpplas */

#endif
