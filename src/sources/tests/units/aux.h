/*
 * $Id$
 */

#ifndef __AUX_H
#define __AUX_H

#include <cstdlib>
#include <ctime>
#include <cassert>

inline int brand(int a, int b){
  if( a==b ){
    return a;
  }
  static bool firstTime(true);
  if( firstTime ) {
    srand( time(NULL) );
    firstTime = false;
  }

  assert(a < b);

  int x = rand() % (b-a);
  return x+a;
}


#endif
