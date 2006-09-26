#include <iostream>
#include "funciones.h"
#include "Z.h"

using namespace std;

int main()
{
    numth::Z entero;
    numth::Z entero2;

    cin >> entero;
    cin >> entero2;

    numth::Z f1;
    numth::Z f2;
    numth::Z mcd;
    
    mcd = numth::gcdExt(entero, entero2, f1, f2);

    cout << "(" << f1 << ")*" << entero << " + " << "(" << f2 << ")*" << entero2 << endl;
    cout << "Deberia ser = " << mcd << endl;
    


}
