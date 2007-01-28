/*
 * $Id$
 */

#ifndef __MPTEST_H
#define __MPTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "mp.h"


using namespace numth;

class MPTest : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE( MPTest );
    CPPUNIT_TEST( testAddMP );
  CPPUNIT_TEST_SUITE_END();
  
  public:
    void setUp();
    void tearDown();
    
    /* The actual tests */
    void testAddMP();
    void testSubMP();
    void testMulMP();
    void testDivMP();
  private:
    vCPUVectorial mpCPU(1);

    numth::MiVec<Cifra> a,b,c;
    numth::MiVec<Cifra> res;

};

#endif
