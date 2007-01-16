/*
 * $Id$
 */

#ifndef __RSATEST_H
#define __RSATEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

using namespace std;

class RSATest : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE( RSATest );
    CPPUNIT_TEST( testRSA );
  CPPUNIT_TEST_SUITE_END();
  
  public:
    void setUp();
    void tearDown();
    
    /* The actual tests */
    void testRSA();
  private:
    string sourceString;
    string resString;
};

#endif
