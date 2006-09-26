#include <iostream>
#include "Z.h"

using namespace std;
using namespace numth;

int main()
{

  Z x,y,z;
  
  while(true){
    cin >> x >> y;
    
    cout << x << " & " << y << endl;
    cout << (x & y) << endl << endl;
 
    cout << x << " | " << y << endl;
    cout << (x | y) << endl << endl;

    cout << "xor(" << x << ", " <<  y << ")" << endl;
    cout << XOR(x,y) << endl << endl;

  }
}

