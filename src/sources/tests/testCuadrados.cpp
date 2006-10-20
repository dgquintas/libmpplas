#include <iostream>
#include "Z.h"

using namespace std;
using namespace numth;

int main()
{
  Z num;
  while(true){
    cin >> num;
    cout << cuadrado(num) << endl;
    cout << raizCuadrada(num) << endl;
    cout << esCuadrado(num) << endl;
  }
}
