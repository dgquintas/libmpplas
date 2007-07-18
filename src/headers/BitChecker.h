/*
 * $Id$
 */

#ifndef __BIT_CHECKER_H
#define __BIT_CHECKER_H

#include "Z.h"

namespace mpplas{
  namespace Utils{
    class BitChecker{

      public:
        BitChecker( const Z& integer, const bool rightToLeft = false );

        int getPosition() const ;
        void setPosition(int pos);

        bool checkNext();
        bool hasNext() const ;

        bool checkPrevious();
        bool hasPrevious() const ;


      private:
        const Z _integer;
        int _digitPos;
        Digit _inDigitPosMask;
        int _bitPos;
        const size_t _bitLength;
        const bool _rightToLeft;

        void _init(const int bitPos, const bool rightToLeft);

    };
  }
}

#endif
