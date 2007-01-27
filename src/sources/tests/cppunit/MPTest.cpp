/*
 * $Id $
 */

#include <cppunit/TestCase.h>
#include <string>
#include "template.h"

using namespace std;
using namespace numth;

CPPUNIT_TEST_SUITE_REGISTRATION( Test );

void Test::setUp(){
  //a = 4389769082470968274309587214235235235346435634
  a.push_back(5888742215302434354);
  a.push_back(16503331602097851919);
  a.push_back(12900371);

  //b = 979857908789074689743689746357394739434345345
  b.push_back(4425000026617140097);
  b.push_back(10901569078006243540)
  b.push_back(2879543)
}
void Test::tearDown(){
//empty. new is not used
}

void Test::testAddMP(){
  c.push_back(10313742241919574451);
  c.push_back(8958156606394543843);
  c.push_back(15779915);

  res = mpCPU.sumaMP(a,b);  

  CPPUNIT_ASSERT( c.size() == res.size() );
  for(int i=0; i < c.size(); i++){
    CPPUNIT_ASSERT( c[0] == res[0] );
  }
}
void Test::testSubMP(){
  res = mpCPU.restaMP(a,b);  
}
void Test::testMulMP(){
  res = mpCPU.multMP(a,b);  
}
void Test::testDivMP(){
  res = mpCPU.divMP(a,b);  
}
