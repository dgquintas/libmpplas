/*
 * $Id$
 */

#ifndef __GCDTEST_H
#define __GCDTEST_H


#include "qtunit/TestCase.h"
#include "GCD.h"
#include "Random.h"

#include <pari/pari.h>
using namespace mpplas;

namespace com_uwyn_qtunit{
 
  class GCDTest : public TestCase {

    public:
    GCDTest();

    void setUp();
    void tearDown();

    protected:
    /* The actual tests */
    void testGCDLehmer();
    void testGCDExtBinario();
    void testGCDList();

    Z z1,z2;

    GEN x,y;
    RandomFast* rnd;

  };
}
#endif
