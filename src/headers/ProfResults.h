/*
 * $Id$
 */

#ifndef __PROFRESULTS_H
#define __PROFRESULTS_H

#include <iostream>
#include <vector>

#include "ProfResult.h"

namespace mpplas{

  class ProfResults {

    public:

      ProfResults();
      void reset();

      ProfResults& operator+=(const ProfResults& rhs);
      ProfResults& operator-=(const ProfResults& rhs);

      const ProfResult& operator[](const size_t thread) const;
      ProfResult& operator[](const size_t thread) ;

      OpsCount getTotalOps() const;

      size_t size() const;


    private:
      std::vector< ProfResult > _perThreadResults;

      friend std::ostream& operator<<(std::ostream&, const ProfResults&);

  };

  ProfResults operator+(ProfResults lhs, const ProfResults& rhs);
  ProfResults operator-(ProfResults lhs, const ProfResults& rhs);

  
}
#endif

