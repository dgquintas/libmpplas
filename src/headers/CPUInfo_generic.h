/*
* $Id$
*/

#ifndef __CPUINFO_GENERIC_H
#define __CPUINFO_GENERIC_H

#include "CPUInfo.h"

namespace mpplas{

  class CPUInfo_generic : 
    public CPUInfo, public SingletonMixIn< CPUInfo_generic >  
  {
    protected:

      CPUInfo_generic();

      void _getCacheSizes();
      void _getSIMDInfo();
      void _getModelName();

      friend class SingletonMixIn< CPUInfo_generic >;

  };

}
#endif

