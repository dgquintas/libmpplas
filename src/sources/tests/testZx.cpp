#include "Zx.h"
#include "Polynomial.h"

#include <iostream>
#include <vector>


int main(){

//  std::vector<mpplas::Z> coefs;
//  coefs.push_back(mpplas::Z(1));
//  coefs.push_back(mpplas::Z(0));
//  coefs.push_back(mpplas::Z(3));
//  coefs.push_back(mpplas::Z(0));
//  coefs.push_back(mpplas::Z(4));
//
//  mpplas::Zx p(coefs);
//
//  coefs.push_back(mpplas::Z(-2));
//
//  mpplas::Zx p2(coefs);
//
//  std::cout << p << std::endl;
//  std::cout << p.evaluate(1488) << std::endl;
//  std::cout << p2 << std::endl;
//  std::cout << p2.evaluate(1488) << std::endl;
//
//  p *= p2;

//  mpplas::Zx u("[(1,8)(1,6)(-3,4)(-3,3)(8,2)(2,1)(-5,0)]");
  mpplas::Zx u("[(168,0)(-177,1)(+76,2)(-7,3)(+28,4)(-25,5)(39,6)(-15,7)(9,8)]");
  mpplas::Zx v("[(3,6)(5,4)(-4,2)(-9,1)(21,0)]");
  std::cout << "u = " << u << std::endl;
  std::cout << "v = " << v << std::endl;

//  mpplas::GCDExt< mpplas::Rx >* gcdext;
//
  const mpplas::Zx d ( mpplas::Zx::gcd(u,v) );
  std::cout << "d = " << d << std::endl;
  mpplas::GCD< mpplas::Polynomial< mpplas::Z> >* gcd = new mpplas::GCDPolyKnuth< mpplas::Z >;
  mpplas::MethodsFactory::getReference().setFunc(gcd);
  const mpplas::Zx d2 ( mpplas::Zx::gcd(u,v) );
  std::cout << "d2 = " << d << std::endl;

  mpplas::Zx q,r;
  mpplas::Zx::divAndMod( u, d, &q, &r);
  std::cout << "q = " << q << std::endl;
  std::cout << "r = " << r << std::endl;
  std::cout << r.isZero() << std::endl;
//  mpplas::Rx s,t;
//  std::cout << gcdext->gcdext(v,u, s,t) << std::endl;
//  std::cout << "s = " << s << std::endl;
//  std::cout << "t = " << t << std::endl;

  



//  mpplas::Zx qq,r;
//  u.pseudoDivide(v, &qq, &r );
//
//  std::cout << "q = " << qq << std::endl;
//  std::cout << "r = " << r << std::endl;

//  std::cout << p << std::endl;
//  std::cout << p.toString() << std::endl;
//
//  std::cout << p.evaluate(1488) << std::endl;
//  
//  mpplas::Zx q(p.toString());
//  std::cout << q << std::endl;

  return 0;
}
