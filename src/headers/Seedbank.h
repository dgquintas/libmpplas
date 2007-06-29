/*
 * $Id$
 */

#ifndef __SEEDBANK_H
#define __SEEDBANK_H

#include "Z.h"
#include <fstream>

namespace mpplas{

 
  /** Source of random seeds.
   *
   * "Storage" class for <em>real</em> entropy. This is stored in the form 
   * of seeds for the methods that might require them.
   */
  class Seedbank
  {
    public: 
      Seedbank(void);
   
      ~Seedbank(void);
      
      /** Get a <em>real</em> random seed. 
       *
       *
       * Reads and packs as a seed the required number of bytes, obtained 
       * from a real entropy source.
       *
       * @param numBytes Length of the seed to get, in bytes. 
       * @return An integer (seed) of @a numBytes bytes.
       *
       * @warning Calls to this method might block if not enough entropy is available 
       * at the moment. They would eventually unblock as it becomes available.
       *
       * @note Do <b>not</b> abuse this mechanism: real entropy is an scarce resource. If just
       * a non really random seed/data is required, use the getSeed(size_t numBytes) method instead.
       */
      Z getSecureSeed(const size_t numBytes);
      
      /** Get pseudorandom seed.
       *
       * Reads and packs as a seed the required number of bytes, obtained after applying 
       * a "strong mixing function" (see RFC1750, section 6.1.2) to an initially truly random 
       * seed. After UMBRAL_SEMILLA calls, this mixing function is fed with real entropy again.
       *
       * @param numBytes Length of the seed to get, in bytes.
       * @return An integer (seed) of @a numBytes bytes.
       *
       * @warning Calls to this method might block if not enough entropy is available 
       * at the moment of feeding the mixing function with real entropy. This could only happen
       * after UMBRAL_SEMILLA calls to the method. Blocking is therefore highly unlikely. */
      Z getSeed(const size_t numBytes);


    private:
      MiVec<uint8_t> _source(const size_t numBytes);
      MiVec<uint8_t> _randomData;
  };

}

#endif
