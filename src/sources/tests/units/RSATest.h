/*
 * $Id$
 */

#ifndef __RSATEST_H
#define __RSATEST_H

#include <string>
#include "qtunit/TestCase.h"

using namespace std;

namespace com_uwyn_qtunit{

  class RSATest : public TestCase {

    public:
    RSATest();
    void setUp();
    void tearDown();

    protected:
    /* The actual tests */
    void testRSA();
    private:
    string sourceString;
    string resString;
  };
}
#endif
