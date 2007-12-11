/*
 * $Id$
 */

#ifndef __PROFILING_H
#define __PROFILING_H

#include <iostream>

#include "SingletonMixIn.h"
#include "ProfResults.h"

namespace mpplas{

  /** Singleton class encompassing the profiling mechanisms. */
  class Profiling : public SingletonMixIn< Profiling > {
    public:
      /** Sets the starting point in time for the clock.
       *
       * @sa stopClock()   */
      inline void startClock();

      /** Stops and checks clock value.
       *
       * Stops the profiling clock and returns its value.
       * This value is defined as the time (in seconds)
       * elapsed between the startup of this clock (@a 
       * startClock()) and the invokation of this method.
       * The precission is system dependant.
       *
       * More over, when OpenMP is enabled, please 
       * refer to the @c omp_get_wtime function documentation
       * for more details.
       *
       * @sa startClock()
       *
       * @return The time (in seconds)
       * elapsed between the startup of this clock 
       * and the invokation of this method.   */
      inline double stopClock() const ;

      /** Reset the profiling counters.
       *
       * Resets to zero all the profiling counters.
       */
      void reset();

      /** Get the profiling results for a given thread.
       *
       * @param threadNum The number of the thread whose profiling resuls to retrive. Begins at 0.
       *
       * @return A reference to the profiling results for thread @a threadNum.
       */
      ProfResult& operator[](int threadNum);

      /** Get the profiling results for a given thread (const version)
       *
       * @param threadNum the number of the thread whose profiling resuls to retrive. Begins at 0.
       *
       * @return a constant reference to the profiling results for thread @a threadNum.
       */
      const ProfResult& operator[](int threadNum) const;

      /** Get the profiling results for all threads.
       *
       * @return A reference to a ProfResults object containing the profiling results for all the threads being profiled.
       */
      ProfResults& getResults();
      /** Get the profiling results for all threads. (const version)
       *
       * @return A reference to a constant ProfResults object containing the profiling results for all the threads being profiled.
       */
      const ProfResults& getResults() const;

      /** Checks whether profiling is enabled.
       *
       * @return @c true if the library was compiled with profiling support. @c false otherwise.
       */
      bool isEnabled() const;


      virtual ~Profiling();

    private:
      Profiling(); 
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
