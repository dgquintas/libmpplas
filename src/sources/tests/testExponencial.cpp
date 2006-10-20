/*
 * $Id: testExponencial.cpp,v 1.1.1.1 2005/12/16 17:44:42 dgquintas Exp $
 */

#include "Z.h"
#include "R.h"
#include <iostream>
#include <stdexcept>
#include "err.h"
#include "Funciones.h"

using namespace std;
using namespace numth;


int main()
{
  try{
    Funciones funcs;
    Exponencial* exp = funcs.exponencial();
    R::precisionSalida(35);
    
    R x;
    cout << "Mete el x pa e^x" << endl;
    cin >> x ;

    cout << exp->exponencial(x) << endl;
  }
  catch(numth::Errores::Excepcion &ex)
  {
    cerr << ex.info() << endl;
  }
  catch(std::out_of_range)
  {
    cerr << "vector de meirda" << endl;
  }

}
