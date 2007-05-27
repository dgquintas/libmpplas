#include "Vector.h"
#include <iostream>


using namespace mpplas;
using namespace std;


int main(){

  Vector<float> vec("[1324.32 21.32 3.1 4435.2 5.325 6.3 -75423.1 -328.1 -9]");

  cout << vec << endl;
  cout << vec.toString() << endl;
  cout << vec(1) << " " << vec(3) << endl;

  vec.transpose();

  cout << vec << endl;
  cout << vec.toString() << endl;




  return 0;
}
