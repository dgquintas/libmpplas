/*
 * $Id$
 */

#ifndef __PROFRESULS_H
#define __PROFRESULS_H

#include <ostream>

#include "BasicTypedefs.h"

namespace mpplas{

  typedef Digit OpsCount;

  class ProfResult {

    public:

      ProfResult();
      void reset();

      ProfResult& operator+=(const ProfResult& rhs);
      ProfResult& operator-=(const ProfResult& rhs);
      const OpsCount& operator[](const int) const;
      OpsCount& operator[](const int) ;

      OpsCount getTotalOps() const;


    private:
      OpsCount _opsCount[BasicCPU::__OpsEnum_SIZE] ;

      friend std::ostream& operator<<(std::ostream&, const ProfResult&);

  };

  ProfResult operator+(ProfResult lhs, const ProfResult& rhs);
  ProfResult operator-(ProfResult lhs, const ProfResult& rhs);

  ////////////////////////////////////////////////////////////////////

  
}
#endif

