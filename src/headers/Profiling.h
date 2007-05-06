/*
 * $Id$
 */

#ifndef __PROFILING_H
#define __PROFILING_H

#include <iostream>

#include "SingletonMixIn.h"
#include "ProfResults.h"

namespace mpplas{
  class Profiling : public SingletonMixIn< Profiling > {
    public:

      inline void startClock();
      inline double stopClock() const ;

      void reset();

      ProfResult& operator[](size_t i);
      const ProfResult& operator[](size_t i) const;

      ProfResults& getResults();
      const ProfResults& getResults() const;

      virtual ~Profiling();

    private:
      Profiling(); 
      //boost::multi_array<unsigned long,2> _opsCount;
      ProfResults _profResults;
      double _wallClockTime;

  
      friend class SingletonMixIn< Profiling >;
      friend std::ostream& operator<<(std::ostream&,const Profiling&);
  };

  //////////////////////////////////////////////

  
  inline void Profiling::startClock(){
    _wallClockTime = omp_get_wtime();
    return;
  }

  inline double Profiling::stopClock() const {
    return omp_get_wtime() - _wallClockTime;
  }





}

#endif
