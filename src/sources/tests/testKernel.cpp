#include <string>
#include "kernel.h"
#include "BasicTypedefs.h"
#include "Constants.h"

using namespace std;
using namespace mpplas;

Digit one;
Digit two;
Digit three;
Digit zero;

Digit overflow;
Digit resto;

void setup(){
  one = (Digit)1;
  two = (Digit)2;
  three = (Digit)3;
  zero = (Digit)0;

  overflow = resto = 0;
}

int main(){

  setup();
  two == BasicCPU::Sub(three, one, overflow) ;
  zero == overflow ;

  one == BasicCPU::Sub(three, two, overflow) ;
  zero == overflow ;

  setup();
  one == BasicCPU::Subx(three, two, overflow) ;
  zero == overflow;

  zero == BasicCPU::Subx(three, three, overflow) ;
  zero ==  overflow ;
  
( (Digit)(Constants::CIFRASIGNO_MAX)+1 == BasicCPU::Sub(Constants::CIFRA_MAX, (Digit)Constants::CIFRASIGNO_MAX,overflow) );
( zero ==  overflow );

  Constants::CIFRA_MAX == BasicCPU::Sub(zero, one, overflow) ;
  one ==  overflow ;

  zero == BasicCPU::Subx(three, two, overflow) ;
  zero ==  overflow ;

  Constants::CIFRA_MAX == BasicCPU::Sub(zero, one, overflow) ;
  one ==  overflow ;

  Constants::CIFRA_MAX == BasicCPU::Subx(two, two, overflow) ;
  one ==  overflow ;

  return 0;
}

