/*
* $Id$
*/

#ifndef __CPUINFO_X86_64_H
#define __CPUINFO_X86_64_H

#include "CPUInfo_x86.h"

namespace mpplas{

  class CPUInfo_x86_64 : public CPUInfo_x86,
                         public SingletonMixIn< CPUInfo_x86_64 >                             
  {
    
    public:
      virtual std::string getArchName() const ;
      virtual int getDigitBitWidth() const;

    private:
      CPUInfo_x86_64();

      friend class SingletonMixIn< CPUInfo_x86_64 >;

  };

}
#endif

