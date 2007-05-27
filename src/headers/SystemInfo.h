 /*
  * $Id$
  */

#ifndef __SYSTEMINFO_H
#define __SYSTEMINFO_H

#include "CPUInfo.h"

namespace mpplas{


  namespace SystemInfo{

      /** Compilation date.
       *
       * @return A character array representing the date on which the library was compiled form "May 19 2007"
       */
      const char* const getBuildDate();

      /** Compilation time.
       *
       * @return A character array representing the time on which the library was compiled form "23:01:59"
       */
      const char* const getBuildTime();


      /** Revision number version.
       *
       * The (highest) version control revision version number of
       * any file included in the compilation process.
       *
       * It is meant to be a rough kind of version numbering.
       *
       * @return The version control revision version number.
       */
      const int getRevisionNumber();


      const CPUInfo& getCPUInfo();
  };


}



#endif
