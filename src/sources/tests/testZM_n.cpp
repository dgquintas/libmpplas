#include <iostream>
#include "ZM_n.h"
#include "Z_n.h"
#include "Profiling.h"

using namespace mpplas;
using namespace std;

int main(){

  ZM_n zm2(Z("43531213242235236235325"),Z("3202342424227"));
  Z_n zn(Z("43531213242235236235325"),zm2.getMod());
  Z exp("123456789987654321");

//  ZM_n x(Z("43531213242235236235329"),Z("9607027272681"));
//  ZM_n supposedInv(x);
//
//  supposedInv.inverse();
//  
//  cout << x.toZ() << endl;
//  cout << supposedInv.toZ() << endl;
//
//  cout << (supposedInv * x).toZ() << endl;

  Profiling& prof( Profiling::getReference() );
  ProfResults pr1, pr2;
  
  prof.reset();
  zm2.inverse();
//  zm2 ^= exp;
  cout << prof << endl;
  pr1 = prof.getResults();

  prof.reset();
  zn.inverse();
//  zn ^= exp;
  cout << prof << endl;
  pr2 = prof.getResults();

  cout << "Diff: " << endl;
  cout << pr1 - pr2 << endl;

  cout << zn << endl;
  cout << zm2.toZ() << endl;

  return 0;
}
