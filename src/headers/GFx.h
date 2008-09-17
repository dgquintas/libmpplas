/*
 * $Id$
 */

#ifndef __GFX_H
#define __GFX_H

#include "Field.h"
#include "Z.h"
#include "Z_px.h"
#include "GF.h"

namespace mpplas{


  /** Finite field element. 
   *
   * Represents an element from a finite field. 
   * The actual generator field is always associated with 
   * the element, as to avoid operating with elements 
   * from two different finite fields. It is therefore
   * not possible to directly instantiate this class. 
   * The intended way to obtain finite field elements is 
   * to use the @a getElement methods of mpplas::GF.
   *
   * One exception to this rule is the default constructor
   * GF(). It is needed in order to be able
   * to integrate this type in methods colections
   * such as those found in the Matrix type.
   *
   * @sa mpplas::GF
   *
   * */
  class GFx : public Z_px , public Field< GFx >  {
  
    public:

      /** Dummy constructor.
       *
       * The sole purpose of this "dummy" constructor
       * is to make it possible to 
       * to integrate this type in methods colections
       * such as those found in the Matrix type.
       *
       * The created instance @e must always be assigned
       * a properly constructed (ie, from one of the 
       * @a getElement methods of mpplas::GF) element
       * before being used. */
      GFx();

      /** Copy constructor */
      GFx(const GFx& src);

      /** Assignment operator */
      GFx& operator=(const GFx& src);

      /** Cumulative addition */
      GFx& operator+=(const GFx& rhs);

      /** Cumulative substraction */
      GFx& operator-=(const GFx& rhs);

      /** Cumulative product */
      GFx& operator*=(const GFx& rhs);

      /** In place squaring */
      virtual GFx& square();

      /** Cumulative division.
       *
       * Note that this method first inverts @a *this, 
       * by means of @a invert(), 
       * and then multiplies the result by @a rhs. */
      GFx& operator/=(const GFx& rhs);

      /** In place inversion. 
       *
       * @throw Errors::NonInvertibleElement element not invertible
       * @return a reference to *this
       * */
      GFx& invert() ;

      /** Inverse.
       *
       * @throw Errors::NonInvertibleElement element not invertible
       * 
       * @return the inverse of the current finite field element. */
      GFx getInverse() const ;


      /** Cumulative exponentiation.
       *
       * @a exp the exponent. It may be negative.
       *
       * @return a reference to *this. */
      GFx& operator^=(const Z& exp);

      /** Conversion to an integer.
       *
       * @return the integer representation
       * of the current finite field element. */
      Z getIntegerValue() const;
      /** Conversion from an integer. 
       *
       * Converts the integer @a src to
       * an element of the finite field associated with
       * the current finite field element and assigns 
       * the converted value to it.
       *
       * @return a reference to *this. */
      GFx& setIntegerValue(const Z& src);


      /** Conversion to polynomial.
       *
       * @return the current finite field element as a polynomial. */
      Z_px getPolynomialValue() const;
      /**  Conversion from polynomial.
       *
       * Converts the polynomial @a src to
       * an element of the finite field associated
       * with the current finite field element and
       * assigns the converted value to it.
       *
       * @return a reference to *this */
      GFx& setPolynomialValue(const Z_px& src);

      /** The finite field generator.
       *
       * @return a reference to the generator
       * associated to the current element.
       */
      inline const GF& getGenerator() const;

      /** Set Polynomial Basis Representation on output.
       *
       * When printing a human readable representation
       * of the element, if @printPBR is true,
       * use its polynomial basis
       * representation, that is, the underlying
       * polynomial in \f$ \mathbf{Z}_p \f$.
       * Otherwise, print its integer equivalent.
       *
       * @param printPBR true if the PBR is to be used. false
       * for the integer representation.
       */
      static void setShowPBR(const bool printPBR);

      /** Check if the polynomial basis representation
       * if being used when printing human readable strings.
       *
       * @return true if the polynomial basis representation
       * if being used when printing human readable strings.
       * false otherwise. */
      static bool isShowPBR();

      virtual std::string toHRString() const;
      std::string getPBRString() const;

      virtual inline GFx& makeZero(){ Z_px::makeZero(); return *this;} 
      virtual inline GFx& makeOne() { Z_px::makeOne();  return *this;}

      virtual bool isZero() const { return Z_px::isZero(); }
      virtual bool isOne() const {  return Z_px::isOne(); }
      virtual inline GFx& invertSign(){ Z_px::changeSign(); return *this; }

      /* Ring, Group and Field methods */
      static const GFx ZERO;
      static const GFx ONE;

      static const bool addCommutative;
      static const bool groupCyclic;

      static const bool unitaryRing;
      static const bool multCommutative;
      static const bool multAssociative;
      static const bool divisionRing;

      GFx getMultInverse() const {
        return this->getInverse();
      }
      static const GFx& getMultIdentity() {
        return GFx::ONE ;
      };
      static const GFx& getAddIdentity() {
        return GFx::ZERO;
      };
      GFx getAddInverse() const{
        return GFx(Z_px::getAddInverse(), _gfGenerator);
      };
      static const GFx& getGroupGenerator() {
        return GFx::ONE;
      }

    protected:

      /** Construct finite field element.
       *
       * Constructs the finite field element
       * corresponding to the polynomial @a poly
       * on the finite field defined by @a generator. 
       *
       * @param poly polynomial whose value to use
       * as that of the element.
       * @param generator finite field to which the
       * constructed element will belong.
       *
       * */
      GFx(const Z_px& poly, const GF& generator);

      /** Construct finite field element.
       *
       * Constructs the finite field element
       * corresponding to the integer @a value 
       * on the finite field defined by @a generator. 
       * 
       * @param value integer whose value to use
       * as that of the element.
       * @param generator finite field to which the
       * constructed element will belong. */
      GFx(const Z& value, const GF& generator);

      /** Construct finite field element.
       *
       * Constructs the zero element of the 
       * finite field defined by @a generator.
       *
       * @param generator finite field to which
       * the constructed element will belong. */
      GFx(const GF& generator);

    private:
      GF _gfGenerator;
      static bool _showPBR;

      friend class mpplas::GF;

  };

  /** Non-cumulative addition.
   *
   * @param lhs left hand side operator.
   * @param rhs right hand side operator.
   *
   * @return the sum of @a lhs and @a rhs. */
  GFx operator+(GFx lhs, const GFx& rhs);

  /** Non-cumulative substraction.
   *
   * @param lhs left hand side operator.
   * @param rhs right hand side operator.
   *
   * @return the difference of @a lhs minus @a rhs. */
  GFx operator-(GFx lhs, const GFx& rhs); 

  /** Non-cumulative product.
   *
   * @param lhs left hand side operator.
   * @param rhs right hand side operator.
   *
   * @return the product of @a lhs by @a rhs. */
  GFx operator*(GFx lhs, const GFx& rhs);

  /** Non-cumulative division.
   *
   * @param lhs dividend.
   * @param rhs divisor.
   *
   * @return the quotient of @a lhs divided by @a rhs. */
  GFx operator/(GFx lhs, const GFx& rhs);


  /** Non-cumulative exponentiation.
   *
   * @param lhs the base.
   * @param rhs the exponent.
   *
   * @return the result of the exponentiation. */
  GFx operator^(GFx lhs, const Z& rhs);

  /** Ouput operator.
   *
   * @param out output stream to which to append.
   * @param elem finite field element to ouput.
   *
   * @note
   * Its format depends on the value of the
   * @a showPBR property. @sa setShowPBR and @sa isShowPBR
   *
   * @return a reference to the output stream.
   * */
  std::ostream& operator<<(std::ostream& out, const GFx& elem);

  /** Input operator
   *
   * Expects the same textual representation as
   * the input operator for @a mpplas::Z_px.
   * 
   * @sa operator>>(std::istream&, Z_px&)
   *
   * @param in input stream.
   * @param elem finite field elemen to which to input.
   *
   * @return a reference to the input stream.
   */
  std::istream& operator>>(std::istream& in, GFx& elem);

  inline const GF& GFx::getGenerator() const{
    return this->_gfGenerator;
  }


}


#endif
