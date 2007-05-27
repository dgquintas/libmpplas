/*
* $Id$
*/

#ifndef __CPUINFO_H
#define __CPUINFO_H

#include <vector>
#include <string>

#include "SingletonMixIn.h"
namespace mpplas{

  class CPUInfo{
    
    public:

      /** Returns the byte size of the L1 cache.
       *
       * Only the data cache is considered.
       */ 
      virtual int getCacheL1Size() const = 0;
      virtual int getCacheL2Size() const = 0;
      virtual int getCacheL3Size() const = 0;

      virtual std::string getModelName() const = 0;
      virtual std::string getArchName() const = 0;

      virtual std::vector<std::string> getSIMDCapabilities() const = 0;
      virtual int getDigitBitWidth() const = 0;

      virtual ~CPUInfo() {};



  };

}
#endif

