/*
* $Id$
*/

#ifndef __CPUINFO_H
#define __CPUINFO_H

#include <vector>
#include <string>

#include "SingletonMixIn.h"
namespace mpplas{

  /** Provides some information about the physical CPU 
   * on which the library is being executed.
   *
   * If the library has been built using "generic" as the
   * architecture, the virtual CPU of the library is considered.
   *
   * */
  class CPUInfo{
    
    public:

      /** L1 cache size.
       *
       * Only the data cache is considered.
       *
       * @return the byte size of the L1 data cache.
       */ 
      virtual int getCacheL1Size() const;
 
      /** L2 cache size.
       *
       * @return the byte size of the L2 cache.
       * */ 
      virtual int getCacheL2Size() const;

      /** L3 cache size.
       *
       * @return the byte size of the L3 cache.If there is no L3 cache, zero is returned.
       * */ 
      virtual int getCacheL3Size() const;

      /** Model of the CPU.
       *
       * @return a string containing the model name of CPU. */
      virtual std::string getModelName() const;

      /** Architecture of the CPU.
       *
       * @return a string containing the model name of CPU. */
      virtual std::string getArchName() const;

      /** SIMD extensions supported by the CPU.
       *
       * @returns a vector containg the names of the SIMD technologies supported by the CPU. */
      virtual std::vector<std::string> getSIMDCapabilities() const;

      /** Bit witdh of the basic integer data type.
       *
       * @return the bit width of the basic integer data type for the CPU. */
      virtual int getDigitBitWidth() const;

      /** Number of available execution units.
       *
       * @return the number of available execution units. */
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

