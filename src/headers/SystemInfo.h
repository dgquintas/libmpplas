 /*
  * $Id$
  */

#ifndef __SYSTEMINFO_H
#define __SYSTEMINFO_H

#include "CPUInfo.h"

namespace mpplas{


  namespace SystemInfo{

    /** Get information about the host's CPU.
     *
     * @return A CPUInfo reference containing information
     * about the host's CPU.
     */
    const CPUInfo& getCPUInfo();

    /** Compilation date.
     *
     * @return A character array representing the date on 
     * which the library was compiled form "May 19 2007"
     */
    const char* getBuildDate();

    /** Compilation time.
     *
     * @return A character array representing the time on 
     * which the library was compiled form "23:01:59"
     */
    const char* getBuildTime();


    /** Revision number version.
     *
     * The (highest) version control revision version number of
     * any file included in the compilation process.
     *
     * It is meant to be a rough kind of version numbering.
     *
     * @return The version control revision version number.
     */
    int getRevisionNumber();

    /** Compiler optimization level.
     *
     * The value given to the optimization option
     * for the compiler used, if supported.
     * For example, in GCC, using -O3 would result 
     * in this function returning the integer 3.
     *
     * @return An integer representing the optimization 
     * level used at compile time or -1 if unknown.
     */
    int getOptimizationLevel();

    /** Checks for profiling support.
     *
     * @return true if profiling is available. false otherwise.
     */ 
    bool isProfilingEnabled();

    /** Checks for OpenMP support.
     *
     * @return true if OpenMP is being used. false otherwise.
     */ 
    bool isOpenMPEnabled();

    /** Check if this is a release version.
     *
     * Release versions have extra checks such as
     * vector bound checks and assertions disabled
     * for improved performance.
     *
     * @return true if this is a release version. false otherwise.
     */
    bool isReleaseVersion();

    /** SIMD Kernel version being used.
     *
     *
     * @return A std::string representing which SIMD kernel 
     * is being used. 
     *
     * @note In case no SIMD kernel was selected at compile
     * time, "nosimd" will be returned.
     */
    std::string getSIMDKernel();

    /** Compiler command line used.
     *
     * @return A std::string with the compiler command line
     * used to compile each of the source files into 
     * an object file.
     */
    std::string getCompilerCmd();


  };


}



#endif
