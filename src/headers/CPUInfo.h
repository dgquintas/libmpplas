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
      virtual int getCacheL1Size() const;
      virtual int getCacheL2Size() const;
      virtual int getCacheL3Size() const;

      virtual std::string getModelName() const;
      virtual std::string getArchName() const;

      virtual std::vector<std::string> getSIMDCapabilities() const;
      virtual int getDigitBitWidth() const;

      virtual int getAvailableCPUs() const ;

      virtual ~CPUInfo() {};

    protected:
      int _l1Size;
      int _l2Size;
      int _l3Size;

      std::string _modelName;
      std::string _archName;

      std::vector<std::string> _simdCap;

      //shouldn't be possible to instantiate
      //this class directly (it's supposed 
      //to be abstract).
      CPUInfo() {};


  };

}
#endif

