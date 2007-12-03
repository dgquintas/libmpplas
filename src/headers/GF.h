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

  class GF : public MPPDataType {
    public:
      GF(const Z& p, const int n = 1, const bool usePrimitiveMod = false);
      GF(const Z& p, const Z_px& fx, const bool checkForIrred = true, const bool checkForPrim = true);
      GF(const GF& src);
     
      GF& operator=(const GF& src);

      GFx getElement(const Z_px& poly) const;
      GFx getElement(const std::string& poly) const;
      GFx getElement(const Z& value) const ;
      GFx getElement() const;

      bool operator==(const GF& rhs);
      bool operator!=(const GF& rhs);

      /** Number of elements of the finite field */
      inline Z getOrder() const;
      inline const Z_px& getMod() const;
      inline int getDegree() const;
      inline Z getCharacteristic() const;
      inline bool isModPrimitive() const;

      virtual std::string toString() const;
      virtual std::string toHRString() const;

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
