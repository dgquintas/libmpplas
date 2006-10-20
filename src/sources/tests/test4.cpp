/*
 * $Id: test4.cpp,v 1.1.1.1 2005/12/16 17:44:39 dgquintas Exp $
 */

#include "Z_n.h"
#include <iostream>

using namespace std;


int main()
{
  try{
    long mod;
    cin >> mod;
    numth::Z_n num(mod);
    cin >> num;
    
    long expS;
    cin >> expS;
    cout << (num^expS) << endl; 

    unsigned long expUS;
    cin >> expUS;
    cout << (num^expUS) << endl; 

    numth::Z expZ;
    cin >> expZ;
    cout << (num^expZ) << endl; 


  }
  catch(numth::Errores::Excepcion &ex)
  {
    cerr << ex.info() << endl;
  }

}
