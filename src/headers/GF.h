/*
 * $Id$
 */

#ifndef __GF_H
#define __GF_H

#include "Z.h"
#include "Z_px.h"
#include "MPPDataType.h"


namespace mpplas{

  class GFx;

  /** Finite field. 
   *
   * Represents finite fields (also called a Galois Fields, GF). 
   * 
   * @par
   * These instances serve as "generators" of the actual
   * finite field elements, represented by the class GFx.
   *
   * @sa mpplas::GFx
   */
  class GF : public MPPDataType {
    public:

      /** Constructor for finite fields.
       *
       * Constructs a finite field with characteristic @a p and degree @a n. 
       * The reducing polynomial (modulus) is randomly generated. If @a usePrimitiveMod
       * is true, this polynomial will be primitive. 
       *
       * @pre
       * @a p must be prime and @n must be > 0
       * */
      GF(const Z& p, const int n = 1, const bool usePrimitiveMod = false);

      /** Constructor for finite fields.
       *
       * Constructs a finite field given the reducing (modulus) polynomial @a fx.
       * If @a checkForIrred is true, @a fx will be check for irreducibility. Likewise,
       * if @a checkForPrim is true, it will be checked if @a fx is primitive. 
       *
       * @pre
       * @a p must be prime 
       * */
      GF(const Z& p, const Z_px& fx, const bool checkForIrred = true, const bool checkForPrim = true);

      /** Copy constructor */
      GF(const GF& src);
     
      /** Assignment operator */
      GF& operator=(const GF& src);

      /** Get an element from the finite field.
       *
       * @return the finite field's element corresponding to the
       * given polynomial @a poly. */
      GFx getElement(const Z_px& poly) const;
 
      /** Get an element from the finite field.
       *
       * @return the finite field's element corresponding to the
       * polynomial corresponding to the textual description given 
       * by @a poly. */
      GFx getElement(const std::string& poly) const;
 
      /** Get an element from the finite field.
       *
       * @return the finite field's element corresponding to the
       * given integer @a value. */
      GFx getElement(const Z& value) const ;

      /** Get an element from the finite field.
       *
       * @return the zero element of the finite field. */
      GFx getElement() const;


      /** Comparison for equality.
       *
       * Two finite fields are considered equal to one another if
       * and only if 
       * <ul>
       *  <li> They share the same reducing polynomial.
       *  <li> They share the same characteristic.
       *  <li> They share the same degree (this is redundant, as the first
       *  condition implies it).
       * </ul> 
       * 
       * @return true if the current finite field equals @a rhs. false otherwise. */
      bool operator==(const GF& rhs);

      /** Comparason for inequality.
       *
       * @sa operator==(const GF&)
       *
       * @return true if the current finite field is @e not equal to @a rhs. false
       * otherwise. */
      bool operator!=(const GF& rhs);

      /** Order of the finite field 
       *
       * That is to say, the number of elements in the finite field.
       * If this field has been defined as \f$ GF( p^n ) \f$, that would
       * account for an order equal to \f$ p^n \in \mathbf{Z} \f$.
       *
       * @return the order (number of elements) of the finite field.
       * */
      inline Z getOrder() const;

      /** Reducing polynomial.
       *
       * @return the polynomial being used a a modulus. */
      inline const Z_px& getMod() const;

      /** Degree of the finite field.
       *
       * The @e degree of an extension field (such as these 
       * finite fields) corresponds to the \f$ n \f$ when the finite
       * field is defined as \f$ GF( p^n ) \f$.
       *
       * @return the field of the finite field. */
      inline int getDegree() const;

      /** Characteristic of the finite field. 
       *
       * The number \f$ n \f$ verifying that, 
       * for some element \f$ e \f$ of the finite
       * field, \f$ \underbrace{e + \cdots e = 0}_{n\textrm{ times}}\f$.
       *
       * @note
       * Given the fact that we are working with finite fields
       * of the form \f$ p ^ n\f$, for \f$ p \f$ a prime, the characteristic
       * of these fields will always correspond to this \f$ p \f$.
       *
       * @return the characteristic of the finite field. */
      inline Z getCharacteristic() const;

      /** Is the polynomial modulus primitive?
       *
       * @return true if the reducing polynomial if primitive. false otherwise. */
      inline bool isModPrimitive() const;

      virtual std::string toString() const;
      virtual std::string toHRString() const;

      /** Read the finite field from a textual definition.
       *
       * Sets the current finite field according to the textual
       * definition given in @a str. */
      void fromString(const std::string& str);

      static const GF NULL_GF;

    protected:

      Z _p;
      int _n;
      Z_px _fx;
      
      Z _order;

      bool _primitiveMod;

  }; /* class GF */




  inline Z GF::getOrder() const{
    return _order;
  }
  inline const Z_px& GF::getMod() const{
    return _fx;
  }

  inline int GF::getDegree() const{
    return _n;
  }

  inline Z GF::getCharacteristic() const{
    return _p;
  }


  inline bool GF::isModPrimitive() const{
    return _primitiveMod;
  }

} /* namespace mpplas */


#endif
