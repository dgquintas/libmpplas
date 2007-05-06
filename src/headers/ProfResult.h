/*
 * $Id$
 */

#ifndef __PROFRESULS_H
#define __PROFRESULS_H

#include <iostream>

namespace mpplas{

  typedef long OpsCount;

  class ProfResult {

    public:
      enum OpsEnum { 
        ADD = 0, ADDX, 
        SUB, SUBX, 
        MUL, ADDMUL, 
        DIV, SHIFTL, SHIFTLR, 
        MNOB,
        __OpsEnum_SIZE
      };

      ProfResult();
      void reset();

      ProfResult& operator+=(const ProfResult& rhs);
      ProfResult& operator-=(const ProfResult& rhs);
      const OpsCount& operator[](const size_t) const;
      OpsCount& operator[](const size_t) ;

      OpsCount getTotalOps() const;


    private:
      OpsCount _opsCount[__OpsEnum_SIZE] ;

      friend std::ostream& operator<<(std::ostream&, const ProfResult&);

  };

  ProfResult operator+(ProfResult lhs, const ProfResult& rhs);
  ProfResult operator-(ProfResult lhs, const ProfResult& rhs);

  ////////////////////////////////////////////////////////////////////

  
}
#endif

