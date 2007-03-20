#include <cassert>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>
#include <xmlrpc-c/abyss.h>

#include "MiVec.h"
#include "Z.h"
#include "Random.h"
#include "Primos.h"
#include "GCD.h"
#include "CRT.h"
#include "Potencia.h"
#include "Funciones.h"

/***********************************************
 ************** INTEGERS ***********************
 ***********************************************/

class ZAddMethod : public xmlrpc_c::method {
  public:
    
    ZAddMethod() {
      this->_signature = "s:ss";
      this->_help = "This method adds two integers together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z const op1(paramList.getString(0));
        numth::Z const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1+op2).toString() );
      }
};
class ZSubMethod : public xmlrpc_c::method {
  public:
    
    ZSubMethod() {
      this->_signature = "s:ss";
      this->_help = "This method substracts the second integer from the first";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z const op1(paramList.getString(0));
        numth::Z const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1 - op2).toString() );
      }
};
class ZMulMethod : public xmlrpc_c::method {
  public:
    
    ZMulMethod() {
      this->_signature = "s:ss";
      this->_help = "This method multiplies two integers together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z const op1(paramList.getString(0));
        numth::Z const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1 * op2).toString() );
      }
};
class ZDivMethod : public xmlrpc_c::method {
  public:
    
    ZDivMethod() {
      this->_signature = "s:ss";
      this->_help = "This method divides the first integer by the second (integer division)"; 
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z const op1(paramList.getString(0));
        numth::Z const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1 / op2).toString() );
      }
};
class ZModMethod : public xmlrpc_c::method {
  public:
    
    ZModMethod() {
      this->_signature = "s:ss";
      this->_help = "This method gives the remainder after the division of the first integer by the second"; 
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z const op1(paramList.getString(0));
        numth::Z const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1 % op2).toString() );
      }
};
class ZFactorialMethod : public xmlrpc_c::method {
  public:
    
    ZFactorialMethod() {
      this->_signature = "s:s";
      this->_help = "This method returns the factorial of the given integer"; 
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z op1(paramList.getString(0));

        paramList.verifyEnd(1);

        *retvalP = xmlrpc_c::value_string( (op1.factorial()).toString() );
      }
};
class ZPowMethod : public xmlrpc_c::method {
  public:
    
    ZPowMethod() {
      this->_signature = "s:s";
      this->_help = "This method returns the exponentiation of the first argument (base) by the second (exponent)"; 
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z op1(paramList.getString(0));
        numth::Z op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1 ^ op2).toString() );
      }
};
/***********************************************
 *************  MODULAR INTEGERS ***************
 ***********************************************/
class ModExpMethod : public xmlrpc_c::method {
  public:
    
    ModExpMethod() {
      this->_signature = "s:sss";
      this->_help = "This method returns the result of the modular exponentiation (arg1 ^ arg2) MOD arg3"; 

      numth::Funciones::getInstance()->getFunc(pmod);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z op1(paramList.getString(0));
        numth::Z const op2(paramList.getString(1));
        numth::Z const op3(paramList.getString(2));

        paramList.verifyEnd(3);

        pmod->potModular(&op1,op2,op3);
        
        *retvalP = xmlrpc_c::value_string( op1.toString() );
      }

  private:
    numth::PotModular* pmod;
};

class ModInverseMethod : public xmlrpc_c::method {
  public:
    
    ModInverseMethod() {
      this->_signature = "s:ss";
      this->_help = "This method returns the result of the modular inverse (arg1 ^ -1) MOD arg2"; 

      numth::Funciones::getInstance()->getFunc(pmod);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z const op1(paramList.getString(0));
        numth::Z const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        numth::Z res;
        
        try {
          res = pmod->inversa(op1,op2);
        }
        catch(numth::Errores::ElementoNoInvertible e){
          res.hacerCero();
          throw(girerr::error(e.what()));
        }
          
        
        
        *retvalP = xmlrpc_c::value_string( res.toString() );
      }

  private:
    numth::PotModular* pmod;
};




/***********************************************
 ************** RANDOM Z ***********************
 ***********************************************/
class RandomZMethod : public xmlrpc_c::method {
  public:
    
    RandomZMethod() {
      this->_signature = "s:s";
      this->_help = "This method returns a random interger of the specified number of bits"; 

      numth::Funciones::getInstance()->getFunc(rnd);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int bits = std::atoi( paramList.getString(0).c_str() );
        paramList.verifyEnd(1);
        
        *retvalP = xmlrpc_c::value_string( (rnd->leerBits( bits )).toString() );
      }

  private:
    numth::RandomRapido* rnd;
};

class RandomZLessThanMethod : public xmlrpc_c::method {
  public:
    
    RandomZLessThanMethod() {
      this->_signature = "s:s";
      this->_help = "This method returns a random interger that is less than the given one"; 

      numth::Funciones::getInstance()->getFunc(rnd);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z const op1(paramList.getString(0));
        paramList.verifyEnd(1);
        
        *retvalP = xmlrpc_c::value_string( (rnd->leerEntero( op1 )).toString() );
      }

  private:
    numth::RandomRapido* rnd;
};

/***********************************************
 **************** Primes ***********************
 ***********************************************/
class GenPrimeMethod : public xmlrpc_c::method {
  public:
    
    GenPrimeMethod() {
      this->_signature = "s:s";
      this->_help = "This method returns a prime of at least the specified number of bits"; 

      numth::Funciones::getInstance()->getFunc(primes);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int bits = std::atoi( paramList.getString(0).c_str() );
        paramList.verifyEnd(1);
        
        *retvalP = xmlrpc_c::value_string( (primes->leerPrimoProb( bits )).toString() );
      }

  private:
    numth::GenPrimos* primes;
};

class PrimeTestMethod : public xmlrpc_c::method {
  public:
    
    PrimeTestMethod() {
      this->_signature = "b:s";
      this->_help = "This method returns true if its argument is prime"; 

      numth::Funciones::getInstance()->getFunc(primeTest);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z const op(paramList.getString(0));
        paramList.verifyEnd(1);
        
        *retvalP = xmlrpc_c::value_boolean( primeTest->esPrimo( op ) );
      }

  private:
    numth::TestPrimoProb* primeTest;
};

/***********************************************
 ****************    GCD    ********************
 ***********************************************/
class GCDMethod : public xmlrpc_c::method {
  public:
    
    GCDMethod() {
      this->_signature = "s:ss";
      this->_help = "This method returns a the greatest common divisor of both integer arguments"; 

      numth::Funciones::getInstance()->getFunc(gcd);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        numth::Z const op1(paramList.getString(0));
        numth::Z const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        
        *retvalP = xmlrpc_c::value_string( (gcd->gcd(op1,op2)).toString() );
      }

  private:
    numth::GCD* gcd;
};

/***********************************************
 ****************    CRT    ********************
 ***********************************************/
class CRTMethod : public xmlrpc_c::method {
  public:
    
    CRTMethod() {
      this->_signature = "s:AA";
      this->_help = "This method returns the modular eq. system defined by the two arrays of integers given";

      numth::Funciones::getInstance()->getFunc(crt);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

      std::vector<xmlrpc_c::value> y = paramList.getArray(0);
      std::vector<xmlrpc_c::value> m = paramList.getArray(1);

      paramList.verifyEnd(2);
      if ( y.size() != m.size() ){
          throw(girerr::error("Array parameters for the CRT should have the same length"));
      }

      numth::MiVec<numth::Z> yZ, mZ;
      for( int i = 0; i < y.size(); i++ ){ //both 

        yZ.push_back( numth::Z(( xmlrpc_c::value_string(y[i]) ) ));
        mZ.push_back( numth::Z(( xmlrpc_c::value_string(m[i]) ) ));
      }

      *retvalP = xmlrpc_c::value_string( (crt->crt(yZ, mZ)).toString() );
    }

  private:
    numth::CRT* crt;
};

int main(int const, const char ** const) {

    try {
        xmlrpc_c::registry myRegistry;

        xmlrpc_c::methodPtr const ZAddMethodP(new ZAddMethod);
        xmlrpc_c::methodPtr const ZSubMethodP(new ZSubMethod);
        xmlrpc_c::methodPtr const ZMulMethodP(new ZMulMethod);
        xmlrpc_c::methodPtr const ZDivMethodP(new ZDivMethod);
        xmlrpc_c::methodPtr const ZModMethodP(new ZModMethod);
        xmlrpc_c::methodPtr const ZPowMethodP(new ZPowMethod);
        
        xmlrpc_c::methodPtr const ZFactorialMethodP(new ZFactorialMethod);

        xmlrpc_c::methodPtr const ModExpMethodP(new ModExpMethod);
        xmlrpc_c::methodPtr const ModInverseMethodP(new ModInverseMethod);
        
        xmlrpc_c::methodPtr const RandomZMethodP(new RandomZMethod);
        xmlrpc_c::methodPtr const RandomZLessThanMethodP(new RandomZLessThanMethod);

        xmlrpc_c::methodPtr const GenPrimeMethodP(new GenPrimeMethod);
        xmlrpc_c::methodPtr const PrimeTestMethodP(new PrimeTestMethod);
        
        xmlrpc_c::methodPtr const GCDMethodP(new GCDMethod);
        
        xmlrpc_c::methodPtr const CRTMethodP(new CRTMethod);

        myRegistry.addMethod("zAdd", ZAddMethodP);
        myRegistry.addMethod("zSub", ZSubMethodP);
        myRegistry.addMethod("zMul", ZMulMethodP);
        myRegistry.addMethod("zDiv", ZDivMethodP);
        myRegistry.addMethod("zMod", ZModMethodP);
        myRegistry.addMethod("zPow", ZPowMethodP);

        myRegistry.addMethod("zFactorial", ZFactorialMethodP);

        
        myRegistry.addMethod("modExp", ModExpMethodP);
        myRegistry.addMethod("modInverse", ModInverseMethodP);
        
        myRegistry.addMethod("getRandomZ", RandomZMethodP);
        myRegistry.addMethod("getRandomZLessThan", RandomZLessThanMethodP);

        myRegistry.addMethod("getPrime", GenPrimeMethodP);
        myRegistry.addMethod("isPrime", PrimeTestMethodP);
        
        myRegistry.addMethod("gcd", GCDMethodP);
        
        myRegistry.addMethod("crt", CRTMethodP);


        
//        xmlrpc_c::serverAbyss abyssServer(xmlrpc_c::serverAbyss::constrOpt()
//            .registryP(&myRegistry)
//            .portNumber(1729)
//            );

	TServer abyssServer;
	MIMETypeAdd("text/html", "html");
	MIMETypeInit();
	MIMETypeAdd("text/html", "html");
	ServerCreate(&abyssServer, "XmlRpcServer", 1729,
                    "./",
	            "./abyss.log");

	xmlrpc_c::server_abyss_set_handlers(&abyssServer, &myRegistry);
	ServerInit(&abyssServer);
	
	MIMETypeAdd("text/html", "html");
	ServerRun(&abyssServer);
	MIMETypeAdd("text/html", "html");
//        abyssServer.run();
        // xmlrpc_c::serverAbyss.run() never returns
        assert(false);
    } catch (std::exception const& e) {
      std::cerr << "Something failed.  " << e.what() << std::endl;
    }
    return 0;
}
