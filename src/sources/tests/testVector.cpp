#include "VectorFloat.h"
#include "VectorInt.h"
#include "VectorDouble.h"
#include <iostream>
#include <cstdlib>
#include "Profiling.h"


using namespace mpplas;
using namespace std;


int main(int argc, char** argv){

  Profiling& prof( Profiling::getReference() );
  const int SIZE = atoi(argv[1]);
  VectorFloat vec(SIZE);
  VectorFloat vec2(SIZE);
  float tmp[4]   __attribute__((aligned(16)));
  float tmp2[4]  __attribute__((aligned(16)));

  for( int i = 0; i < SIZE/4 ; i++){
    for(int j = 0 ; j < 4; j++){
      tmp[j] = float(rand())/rand();
      tmp2[j] = float(rand())/rand();
    }
    vec(i).pack(tmp);
    vec2(i).pack(tmp2);
  }

//  cout << vec - vec2  << endl;
//  cout << vec * vec2  << endl;
//  cout << vec / vec2  << endl;

  prof.startClock();
  for( int i = 0 ; i < 10 ; i++ ){
    vec *= vec2;
  }
  cout <<  prof.stopClock() << endl ;




  return 0;
}
