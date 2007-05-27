/*
* $Id$
*/

#ifndef __CPUINFO_X86_H
#define __CPUINFO_X86_H

#include "CPUInfo.h"

namespace mpplas{

  class CPUInfo_x86 : public CPUInfo, public SingletonMixIn< CPUInfo_x86 >  {
    
    public:


      virtual int getCacheL1Size() const ;
      virtual int getCacheL2Size() const ;
      virtual int getCacheL3Size() const ;

      virtual std::string getModelName() const ;
      virtual std::string getArchName() const ;

      virtual std::vector<std::string> getSIMDCapabilities() const ;

      virtual int getDigitBitWidth() const;

    private:

      CPUInfo_x86();

      enum { EAX = 0, EBX, ECX, EDX };
      uint32_t _regs[4]; /* EAX, EBX, ECX, EDX */
      inline void _invokeCPUID(uint32_t eax);
      void _getCacheSizes();
      void _getSIMDInfo();

      int _l1Size;
      int _l2Size;
      int _l3Size;

      std::string _modelName;
      std::string _archName;

      std::vector<std::string> _simdCap;

      friend class SingletonMixIn< CPUInfo_x86 >;

  };

}
#endif

