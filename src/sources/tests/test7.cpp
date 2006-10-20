#include <iostream>
#include "Z.h"
#include "Z_n.h"

using namespace std;
using namespace numth;

int main()
{
  unsigned long ul;
  signed long sl;

  Z z1,z2;

  cin >> ul >> sl >> z1 >> z2;

  cout << z1 << " + " << ul << endl;
  cout << z1 + ul << endl;
  
  cout << z1 << " - " << ul << endl;
  cout << z1 - ul << endl;
  
  cout << z1 << " * " << ul << endl;
  cout << z1 * ul << endl;
  
  cout << z1 << " / " << ul << endl;
  cout << z1 / ul << endl;
  
  cout << z1 << " % " << ul << endl;
  cout << z1 % ul << endl;
  

  cout << ul << " + " << z1 << endl;
  cout << ul + z1 << endl;
 
  cout << ul << " - " << z1 << endl;
  cout << ul - z1 << endl;
  
  cout << ul << " * " << z1 << endl;
  cout << ul * z1 << endl;
  
  cout << ul << " / " << z1 << endl;
  cout << ul / z1 << endl;
  
  cout << ul << " % " << z1 << endl;
  cout << ul % z1 << endl;
 

  cout << z1 << " + " << sl << endl;
  cout << z1 + sl << endl;
 
  cout << z1 << " - " << sl << endl;
  cout << z1 - sl << endl;
  
  cout << z1 << " * " << sl << endl;
  cout << z1 * sl << endl;
  
  cout << z1 << " / " << sl << endl;
  cout << z1 / sl << endl;
  
  cout << z1 << " % " << sl << endl;
  cout << z1 % sl << endl;


  cout << sl << " + " << z1 << endl;
  cout << sl + z1 << endl;
 
  cout << sl << " - " << z1 << endl;
  cout << sl - z1 << endl;
  
  cout << sl << " * " << z1 << endl;
  cout << sl * z1 << endl;
  
  cout << sl << " / " << z1 << endl;
  cout << sl / z1 << endl;
  
  cout << sl << " % " << z1 << endl;
  cout << sl % z1 << endl;



  cout << z1 << " + " << z2 << endl;
  cout << z1 + z2 << endl;

  cout << z1 << " - " << z2 << endl;
  cout << z1 - z2 << endl;
  
  cout << z1 << " * " << z2 << endl;
  cout << z1 * z2 << endl;
  
  cout << z1 << " / " << z2 << endl;
  cout << z1 / z2 << endl;
  
  cout << z1 << " % " << z2 << endl;
  cout << z1 % z2 << endl;




  cout << endl << endl;

  long m ;
  cin >> m;

  Z_n z1n(m);
  Z_n z2n(m);

  cin >> ul >> sl >> z1n >> z2n;

  cout << "(" << z1n << " + " << ul << ") % " << m << endl;
  cout << z1n + ul << endl;
  
  cout << "(" << z1n << " - " << ul << ") % " << m << endl;
  cout << z1n - ul << endl;
  
  cout << "(" << z1n << " * " << ul << ") % " << m << endl;
  cout << z1n * ul << endl;
  
  cout << "(" << z1n << " / " << ul << ") % " << m << endl;
  cout << z1n / ul << endl;
  

  cout << "(" << ul << " + " << z1n << ") % " << m << endl;
  cout << ul + z1n << endl;
 
  cout << "(" << ul << " - " << z1n << ") % " << m << endl;
  cout << ul - z1n << endl;
  
  cout << "(" << ul << " * " << z1n << ") % " << m << endl;
  cout << ul * z1n << endl;
  
  cout << "(" << ul << " / " << z1n << ") % " << m << endl;
  cout << ul / z1n << endl;
  
 

  cout << "(" << z1n << " + " << sl << ") % " << m << endl;
  cout << z1n + sl << endl;
 
  cout << "(" << z1n << " - " << sl << ") % " << m << endl;
  cout << z1n - sl << endl;
  
  cout << "(" << z1n << " * " << sl << ") % " << m << endl;
  cout << z1n * sl << endl;
  
  cout << "(" << z1n << " / " << sl << ") % " << m << endl;
  cout << z1n / sl << endl;
  


  cout << "(" << sl << " + " << z1n << ") % " << m << endl;
  cout << sl + z1n << endl;
 
  cout << "(" << sl << " - " << z1n << ") % " << m << endl;
  cout << sl - z1n << endl;
  
  cout << "(" << sl << " * " << z1n << ") % " << m << endl;
  cout << sl * z1n << endl;
  
  cout << "(" << sl << " / " << z1n << ") % " << m << endl;
  cout << sl / z1n << endl;
  


  cout << "(" << z1n << " + " << z2n << ") % " << m << endl;
  cout << z1n + z2n << endl;

  cout << "(" << z1n << " - " << z2n << ") % " << m << endl;
  cout << z1n - z2n << endl;
  
  cout << "(" << z1n << " * " << z2n << ") % " << m << endl;
  cout << z1n * z2n << endl;
  
  cout << "(" << z1n << " / " << z2n << ") % " << m << endl;
  cout << z1n / z2n << endl;

  
  return 0;
}
  
