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
#include "R.h"

namespace mpplas{

  template<typename S>
    class Polynomial : public MPPDataType {

      public: 
        Polynomial(const S& ini = S::getAddIdentity() );
        Polynomial(const Polynomial<S>& src );
        Polynomial<S>& operator=(const Polynomial<S>& src);

        inline S& operator[](int i);
        inline const S& operator[](int i) const;

        inline int getDegree() const;
        inline const S& getLeadingCoefficient() const;
        inline bool isMonic() const;
        inline const S& getIni() const;

        bool isCoeffsDomainAField() const ;

        inline void makeZero();
        inline void makeOne();

        inline bool isZero() const;
        inline bool isOne() const;

        void changeSign();

        S evaluate(const S& x0) const;

        S getContent() const;
        Polynomial<S>& makePrimitive();

        bool operator==(const Polynomial<S>& rhs) const;

        Polynomial<S>& operator+=(const Polynomial<S>& rhs);
        Polynomial<S>& operator+=(const S& s);

        Polynomial<S>& operator-=(const Polynomial<S>& rhs);
        Polynomial<S>& operator-=(const S& s);

        Polynomial<S>& operator*=(const Polynomial<S>& rhs);
        Polynomial<S>& operator*=(const S& s); 
        Polynomial<S>& square();

        Polynomial<S>& operator/=(const Polynomial<S>& rhs);
        Polynomial<S>& operator/=(const S& s); 

        Polynomial<S>& operator%=(const Polynomial<S>& rhs);
        Polynomial<S>& operator%=(const S& s); 

        static void divAndMod(Polynomial<S> lhs, const Polynomial<S>& rhs, Polynomial<S>* q, Polynomial<S>* r);

        virtual std::string toString() const;

        ~Polynomial(){
          //only conditions are that S must be a commutative ring 
          //with identity: Knuth 4.6 (p. 418). ie, a unique factorization domain (UFD)
          Constraints::must_have_base<S, Ring<S> > dummy1 __attribute__ ((__unused__));
          Constraints::must_have_base<S, MPPDataType > dummy2 __attribute__ ((__unused__));
          STATIC_ASSERT( S::multCommutative );
        }


      protected:
        Polynomial(const std::string& str, const S& ini = S() );
        Polynomial(const std::vector<S>& coeffs, const S& ini = S() );
        Polynomial(const S& coeff, const int exp, const S& ini = S() );


        MiVec<S> _data;
        bool _isSaField;

        S _ini;

        template<typename U> 
          friend std::ostream& operator<<(std::ostream&, const Polynomial<U>& );

        template<typename U>
          friend std::istream& operator>>(std::istream&, Polynomial<U>& ) ;

      private:
        void _eraseLeadingZeros();
        void _horner2ndOrder(S& result, const S& x0) const ;
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
