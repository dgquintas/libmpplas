#include "Z_px.h"
#include "Zx.h"
#include <iostream>

int main(){
  mpplas::Z_px u("[(1,10)(1,9)(1,8)(1,6)(1,5)(1,4)(1,0)]",2);
  mpplas::Z_px v("[(1,9)(1,6)(1,5)(1,3)(1,2)(1,0)]",2);
  mpplas::Z_px q(2),r(2);
  std::cout << u << std::endl;
  std::cout << v << std::endl;

//  mpplas::GCDExtPoly< mpplas::Z_p > gcdext;
//  std::cout << gcdext.gcdext(u,v,&q, &r) << std::endl;
  mpplas::Z_px::gcd(u,v,&q,&r);

  std::cout << q << std::endl;
  std::cout << r << std::endl;

  mpplas::Z_px f("[(1,4)(1,1)(1,0)]",2);
  u = mpplas::Z_px("[(1,3)(1,2)(1,0)]",2);
  v = mpplas::Z_px("[(1,3)(1,0)]",2);
  u *= v;
  u %= f;
  std::cout << u << std::endl;


  mpplas::Z_px uu("[(1,3)(1,1)(1,0)]",2);
//  std::cout << gcdext.gcdext(uu,f,&q, &r) << std::endl;
  mpplas::Z_px::gcd(uu,f,&q,&r);

  std::cout << q << std::endl;

  uu *= q;
  uu %= f;
  std::cout << uu  << std::endl;

  return 0;
}



