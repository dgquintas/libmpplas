#include <iostream>
#include "funciones.h"
#include "Z.h"

using namespace std;

int main()
{
 
    numth::Z entero;
    unsigned long div;

    cin >> entero >> div;
    
    cout << (entero % div) << endl;

}
