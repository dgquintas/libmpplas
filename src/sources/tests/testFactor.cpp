#include "Z.h"
#include "Factor.h"
#include "Random.h"
#include "MethodsFactory.h"
#include <iostream>

using namespace std;
using namespace mpplas;

int main()
{
  Z num;
  Random* rnd;
  Factoriza* factor;
  MethodsFactory::getReference().getFunc(rnd);
  MethodsFactory::getReference().getFunc(factor);

    num = rnd->getInteger(64);
    cout << num << endl;
    MiVec< pair<Z, int> > facs = factor->factorsWithExps(num);
    for( int i = 0; i < facs.size(); i++){
        cout << facs[i].first << " " << facs[i].second << endl ;
    }

  return 0;
}

  
