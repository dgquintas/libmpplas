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
      /** Sets the starting point in time for the clock.
       *
       * @sa stopClock()
       * 
       */
      inline void startClock();

      /** Stops and checks clock value.
       *
       * Stops the profiling clock and returns its value.
       * This value is defined as the time (in seconds)
       * elapsed between the startup of this clock (@sa 
       * startClock()) and the invokation of this method.
       * The precission is system dependant.
       *
       * More over, when OpenMP is enabled, please 
       * refer to the @c omp_get_wtime function documentation
       * for more details.
       *
       * @return The time (in seconds)
       * elapsed between the startup of this clock 
       * and the invokation of this method.
       */
      inline double stopClock() const ;

      /** Reset the profiling counters.
       *
       * Resets to zero all the profiling counters.
       */
      void reset();

      ProfResult& operator[](size_t i);
      const ProfResult& operator[](size_t i) const;

      size_t getNumThreads() const;

      ProfResults& getResults();
      const ProfResults& getResults() const;

      bool isEnabled() const;


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
