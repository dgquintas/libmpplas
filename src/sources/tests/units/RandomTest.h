/*
 * $Id$
 */

#ifndef __RANDOMTEST_H
#define __RANDOMTEST_H

#include "qtunit/TestCase.h"
#include <string>
#include "Random.h"

using namespace mpplas;

namespace com_uwyn_qtunit{
 
  class RandomTest : public TestCase {

    public:
    RandomTest();

    void setUp();
    void tearDown();

    protected:
    /* The actual tests */
    void testRC4();
    void testCongruent();
    void testBBS();

    private:
    FIPS_140_1 fips_;
  };
}
#endif
