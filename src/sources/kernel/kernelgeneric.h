/* 
 * $Id$
 */
#ifdef ARCH_generic

#include "Constants.h"

namespace mpplas{

  namespace BasicCPU{


    inline Digit HIGHHALF(Digit x) { return (x >> Constants::BITS_IN_HALFCIFRA); }
    inline Digit LOWHALF(Digit x) { return (x & Constants::MASK_CIFRALOW); }

    /**********************************
     *   GENERIC IMPLEMENTATION
     **********************************/ 

    inline Digit Add(Digit arg1, Digit arg2, Digit& overflow)
    {
      const Digit ret = arg1 + arg2;
      overflow = ( ret < arg1 );
      return ret; 
    }

    inline Digit Addx(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      const Digit ret = arg1 + arg2 + overflow;
      overflow = (ret < arg1 || (ret==arg1 && overflow));
      return ret; 
    }


    inline Digit Sub(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      const Digit ret = arg1-arg2;
      overflow = ( ret > arg1 );
      return ret; 
    }
    inline Digit Subx(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      const Digit ret = arg1-arg2-overflow;
      overflow = (ret > arg1 || (ret == arg1 && overflow) );

      return ret; 
    }

    inline Digit Mul(Digit arg1,Digit arg2, Digit& resto) 
    { 
      // based on pari-gp's implementation by Peter Montgomery
      const Digit xlo = LOWHALF(arg1), xhi = HIGHHALF(arg1);
      const Digit ylo = LOWHALF(arg2), yhi = HIGHHALF(arg2);
      Digit xylo,xymid,xyhi,xymidhi,xymidlo;
      Digit xhl,yhl;

      xylo = xlo*ylo; xyhi = xhi*yhi;
      xhl = xhi+xlo; yhl = yhi+ylo;
      xymid = xhl*yhl - (xyhi+xylo);

      xymidhi = HIGHHALF(xymid);
      xymidlo = xymid << Constants::BITS_IN_HALFCIFRA;

      xylo += xymidlo;
      resto = xyhi + xymidhi + (xylo < xymidlo)
        + ((((xhl + yhl) >> 1) - xymidhi) & Constants::MASK_CIFRAHIGH);

      return xylo;
    }

    inline Digit Addmul(Digit arg1,Digit arg2, Digit& resto) 
    { 
      // based on pari-gp's implementation by Peter Montgomery
      const Digit xlo = LOWHALF(arg1), xhi = HIGHHALF(arg1);
      const Digit ylo = LOWHALF(arg2), yhi = HIGHHALF(arg2);
      Digit xylo,xymid,xyhi,xymidhi,xymidlo;
      Digit xhl,yhl;

      xylo = xlo*ylo; xyhi = xhi*yhi;
      xhl = xhi+xlo; yhl = yhi+ylo;
      xymid = xhl*yhl - (xyhi+xylo);

      xylo += resto; xyhi += (xylo < resto);

      xymidhi = HIGHHALF(xymid);
      xymidlo = xymid << Constants::BITS_IN_HALFCIFRA;

      xylo += xymidlo;
      resto = xyhi + xymidhi + (xylo < xymidlo)
        + ((((xhl + yhl) >> 1) - xymidhi) & Constants::MASK_CIFRAHIGH);

      return xylo;
    }

    inline Digit Div(Digit arg1, Digit arg2, Digit& resto) 
    { 
      //FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      uint64_t x = resto;
      x <<= Constants::BITS_EN_CIFRA;
      x |= arg1;
      const Digit ret = x/arg2; 
      resto = x % arg2;

      return ret;
    }


    inline Digit Shiftl(Digit arg1,Digit arg2, Digit& resto) 
    { 
      resto = arg1 >> (Constants::BITS_EN_CIFRA-arg2);
      return (arg1 << arg2) ; 
    }

    inline Digit Shiftlr(Digit arg1,Digit arg2, Digit& resto) 
    { 
      resto = arg1 << (Constants::BITS_EN_CIFRA-arg2);
      return (arg1 >> arg2);
    }

    inline Digit Mnob(Digit arg1) 
    {
      int res = 0;

      static const Digit masks[] = { 0x2, 0xc, 0xf0, 0xff00, 0xffff0000, 0xffffffff }; //FIXME:generate at compiletime

      //for 64 bit archs
      if( arg1 > masks[5] ){
        arg1 >>= 31; arg1 >>= 1; //to avoid the warning on 32 bit archs
        res += 32;
      }
      if( arg1 & masks[4] ){
        arg1 >>= 16;
        res += 16;
      }
      if( arg1 & masks[3] ){
        arg1 >>= 8;
        res += 8;
      }
      if( arg1 & masks[2] ){
        arg1 >>= 4;
        res += 4;
      }
      if(arg1 & masks[1] ){
        arg1 >>= 2;
        res += 2;
      }
      switch(arg1){
        case 3:
        case 2:
          return res +2 ;
        default: /* 0 and 1 */
          return res + 1;
      }
    }
  }
}
#endif
