/*
 * $Id$
 */

#ifndef __AUX_H
#define __AUX_H

#include <cstdlib>
#include <cassert>

inline int brand(int a, int b){

  assert(a < b);

  int x = rand() % (b-a);
  return x+a;
}


#endif
