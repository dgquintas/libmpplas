#include "Vector.h"
#include <iostream>


using namespace mpplas;
using namespace std;


int main(){

  Vector<int> vec("[1324 21 3 4 5 6 -7542 8 9]");

  cout << vec << endl;
  cout << vec.toString() << endl;
  cout << vec(1) << " " << vec(3) << endl;

  vec.transpose();

  cout << vec << endl;
  cout << vec.toString() << endl;




  return 0;
}
