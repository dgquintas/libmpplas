/*
 * $Id$
 */

#ifndef __AUX_H
#define __AUX_H

#include <cstdlib>
#include <ctime>
#include <cassert>

inline int brand(int a, int b){
  srand( time(NULL) );

  assert(a < b);

  int x = rand() % (b-a);
  return x+a;
}


#endif
