/*
* $Id$
*/

#ifndef __CPUINFO_X86_64_H
#define __CPUINFO_X86_64_H

#include "CPUInfo.h"

namespace mpplas{

  class CPUInfo_x86_64 : public CPUInfo, 
                         public SingletonMixIn< CPUInfo_x86_64 >  
  
  {
    protected:

      CPUInfo_x86_64();

      enum { EAX = 0, EBX, ECX, EDX };
      uint32_t _regs[4]; /* EAX, EBX, ECX, EDX */
      inline void _invokeCPUID(uint32_t eax);
      void _getCacheSizes();
      void _getSIMDInfo();
      void _getModelName();

      friend class SingletonMixIn< CPUInfo_x86_64 >;

  };

}
#endif

