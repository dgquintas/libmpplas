#include "SystemInfo.h"

#include <iostream>
#include <cassert>

using namespace std;
using namespace mpplas;

int main(){
  const CPUInfo& ci(SystemInfo::getCPUInfo() );
  const CPUInfo& ci2(SystemInfo::getCPUInfo() );

  assert( (&ci) == (&ci2) );

  cout << ci.getCacheL1Size() / 1024 << endl;
  cout << ci.getCacheL2Size() / 1024 << endl;
  cout << ci.getCacheL3Size() / 1024 << endl;

  for( int i = 0 ; i < ci.getSIMDCapabilities().size() ; i++){
    cout << ci.getSIMDCapabilities()[i] << " ";
  }
  cout << endl;

  cout << ci.getModelName() << endl;
  cout << ci.getArchName() << endl;
  cout << ci.getDigitBitWidth() << endl;

  return 0;
}

