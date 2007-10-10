#include <cassert>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <utility>
#include <set>
#include <limits>

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>
#include <xmlrpc-c/abyss.h>

#include "MiVec.h"
#include "Z.h"
#include "MatrixZ.h"
#include "R.h"
#include "Random.h"
#include "Primos.h"
#include "GCD.h"
#include "CRT.h"
#include "Potencia.h"
#include "MethodsFactory.h"
#include "SystemInfo.h"
#include "BasicTypedefs.h"
#include "Profiling.h"
#include "Errors.h"

#include "RuntimeData.h"


/* XML-RPC SIGNATURES 
 *
 *  case 'i':  "int";              
 *  case 'b':  "boolean";          
 *  case 'd':  "double";           
 *  case 's':  "string";           
 *  case '8':  "dateTime.iso8601"; 
 *  case '6':  "base64";           
 *  case 'S':  "struct";           
 *  case 'A':  "array";            
 *  case 'n':  "nil";              
 *
 */

std::set<int> _idsInUse;
RuntimeData<mpplas::Z> tableZ;

class RequestClientId: public xmlrpc_c::method {
  public:
    
    RequestClientId() {
      this->_signature = "i:";
      this->_help = "This method returns a valid clientId";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        paramList.verifyEnd(0);
        int rnd;
        do{
         rnd = rand();
        } while( _idsInUse.find(rnd) != _idsInUse.end() );
        _idsInUse.insert(rnd);

        *retvalP = xmlrpc_c::value_int(rnd);
      }

};

class DiscardClientId: public xmlrpc_c::method {
  public:
    
    DiscardClientId() {
      this->_signature = "b:i";
      this->_help = "This method discards the given clientId and all the date associated with it";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        paramList.verifyEnd(1);
    
        std::set<int>::iterator it = _idsInUse.find(clientId);
        bool res = false;
        if( it != _idsInUse.end() ){
          _idsInUse.erase(it);
      
          //TODO: remove data from the tables
          res = true;
        }

        *retvalP = xmlrpc_c::value_boolean(res);
      }

};


/***********************************************
 ************** INTEGERS ***********************
 ***********************************************/


class ZRunGC: public xmlrpc_c::method {
  public:
    
    ZRunGC() {
      this->_signature = "n:iA";
      this->_help = "This method garbage collects the internal table of Z's";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::vector<xmlrpc_c::value> tmp = paramList.getArray(1);

        paramList.verifyEnd(2);

        std::vector<int> usedSlots( tmp.size() );
        for(int i=0; i< tmp.size(); i++){
          usedSlots.push_back( xmlrpc_c::value_int( tmp[i] ) );
        }

        tableZ.runGC(clientId, usedSlots);

        *retvalP = xmlrpc_c::value_nil();
      }
};


class ZCreate: public xmlrpc_c::method {
  public:
    
    ZCreate() {
      this->_signature = "i:is";
      this->_help = "This method creates a new integer";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const mpplas::Z op(paramList.getString(1));

        paramList.verifyEnd(2);

        int idx = tableZ.set(clientId, op);

        *retvalP = xmlrpc_c::value_int(idx);
      }
};

class ZGet: public xmlrpc_c::method {
  public:
    
    ZGet() {
      this->_signature = "s:ii";
      this->_help = "This method retrieves an integer";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const int varId(paramList.getInt(1));

        paramList.verifyEnd(2);

        const mpplas::Z z(tableZ.get(clientId, varId));

        *retvalP = xmlrpc_c::value_string(z.toString() );
      }
};

class ZAddMethod : public xmlrpc_c::method {
  public:
    
    ZAddMethod() {
      this->_signature = "i:iii";
      this->_help = "This method adds two integers together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const int varId1(paramList.getInt(1));
        const int varId2(paramList.getInt(2));

        paramList.verifyEnd(3);

        const mpplas::Z op1( tableZ.get(clientId, varId1 ) );
        const mpplas::Z op2( tableZ.get(clientId, varId2 ) );

        int idx = tableZ.set(clientId, op1+op2);

        *retvalP = xmlrpc_c::value_int( idx );
      }
};
class ZSubMethod : public xmlrpc_c::method {
  public:
    
    ZSubMethod() {
      this->_signature = "s:ss";
      this->_help = "This method substracts the second integer from the first";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::Z const op1(paramList.getString(0));
        mpplas::Z const op2(paramList.getString(1));

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

        mpplas::Z const op1(paramList.getString(0));
        mpplas::Z const op2(paramList.getString(1));

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

        mpplas::Z const op1(paramList.getString(0));
        mpplas::Z const op2(paramList.getString(1));

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

        mpplas::Z const op1(paramList.getString(0));
        mpplas::Z const op2(paramList.getString(1));

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

        mpplas::Z op1(paramList.getString(0));

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

        mpplas::Z op1(paramList.getString(0));
        mpplas::Z op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1 ^ op2).toString() );
      }
};


/***********************************************
 **************   REALS  ***********************
 ***********************************************/

class RAddMethod : public xmlrpc_c::method {
  public:
    
    RAddMethod() {
      this->_signature = "s:ss";
      this->_help = "This method adds two reals together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::R const op1(paramList.getString(0));
        mpplas::R const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1+op2).toString() );
      }
};
class RSubMethod : public xmlrpc_c::method {
  public:
    
    RSubMethod() {
      this->_signature = "s:ss";
      this->_help = "This method substracts the second real from the first";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::R const op1(paramList.getString(0));
        mpplas::R const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1 - op2).toString() );
      }
};
class RMulMethod : public xmlrpc_c::method {
  public:
    
    RMulMethod() {
      this->_signature = "s:ss";
      this->_help = "This method multiplies two reals together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::R const op1(paramList.getString(0));
        mpplas::R const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1 * op2).toString() );
      }
};
class RDivMethod : public xmlrpc_c::method {
  public:
    
    RDivMethod() {
      this->_signature = "s:ss";
      this->_help = "This method divides the first real by the second"; 
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::R const op1(paramList.getString(0));
        mpplas::R const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1 / op2).toString() );
      }
};

class RPowMethod : public xmlrpc_c::method {
  public:
    
    RPowMethod() {
      this->_signature = "s:s";
      this->_help = "This method returns the exponentiation of the first argument (base) by the second (exponent)"; 
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::R op1(paramList.getString(0));
        mpplas::SignedDigit op2;
        std::stringstream ss(paramList.getString(1));
        ss >> op2;

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

      mpplas::MethodsFactory::getInstance()->getFunc(pmod);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::Z op1(paramList.getString(0));
        mpplas::Z const op2(paramList.getString(1));
        mpplas::Z const op3(paramList.getString(2));

        paramList.verifyEnd(3);

        pmod->potModular(&op1,op2,op3);
        
        *retvalP = xmlrpc_c::value_string( op1.toString() );
      }

  private:
    mpplas::PotModular* pmod;
};

class ModInverseMethod : public xmlrpc_c::method {
  public:
    
    ModInverseMethod() {
      this->_signature = "s:ss";
      this->_help = "This method returns the result of the modular inverse (arg1 ^ -1) MOD arg2"; 

      mpplas::MethodsFactory::getInstance()->getFunc(pmod);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::Z const op1(paramList.getString(0));
        mpplas::Z const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        mpplas::Z res;
        
        try {
          res = pmod->inversa(op1,op2);
        }
        catch(mpplas::Errors::NonInvertibleElement e){
          res.hacerCero();
          throw(girerr::error(e.what()));
        }
          
        
        
        *retvalP = xmlrpc_c::value_string( res.toString() );
      }

  private:
    mpplas::PotModular* pmod;
};







/***********************************************
 ************** INTEGER MATRICES ****************
 ***********************************************/

class MZAddMethod : public xmlrpc_c::method {
  public:
    
    MZAddMethod() {
      this->_signature = "s:ss";
      this->_help = "This method adds two integer matrices together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::MatrixZ const op1(paramList.getString(0));
        mpplas::MatrixZ const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1+op2).toString() );
      }
};
class MZMulMethod : public xmlrpc_c::method {
  public:
    
    MZMulMethod() {
      this->_signature = "s:ss";
      this->_help = "This method multiplies two integer matrices";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::MatrixZ const op1(paramList.getString(0));
        mpplas::MatrixZ const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( (op1*op2).toString() );
      }
};


class MZPPrintMethod : public xmlrpc_c::method {
  public:
    
    MZPPrintMethod() {
      this->_signature = "s:s";
      this->_help = "This method returns an alternative representation of the matrix, more human readable";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::MatrixZ const op1(paramList.getString(0));

        paramList.verifyEnd(1);

        std::ostringstream oss;
        oss << op1;

        *retvalP = xmlrpc_c::value_string( oss.str() );
      }
};



/***********************************************
 ************** RANDOM Z ***********************
 ***********************************************/
class RandomZMethod : public xmlrpc_c::method {
  public:
    
    RandomZMethod() {
      this->_signature = "S:ii";
      this->_help = "This method returns a random interger of the specified number of bits"; 

      mpplas::MethodsFactory::getInstance()->getFunc(rnd);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

      const int clientId(paramList.getInt(0));
      const int bitsOrVarId = paramList.getInt(1);
      int bits;
      mpplas::Z z;
      sleep(5);

      if( bitsOrVarId < 0 ){ //it's a varId
        z = tableZ.get(clientId, bitsOrVarId);
        if( z.getBitLength() > std::numeric_limits<int>::digits ){
          mpplas::Errors::TooBig toobig;
          throw girerr::error( toobig.what() );
        }
        else{
          bits = (int)z[0]; //the cast from unsigned should be safe
        }
      }
      else{
        bits = bitsOrVarId;
      }

      paramList.verifyEnd(2);

      try{
        const mpplas::Z& op(rnd->getInteger( bits ));
        int idx = tableZ.set(clientId, op);

        std::map<std::string, xmlrpc_c::value> structData;
        std::pair<std::string, xmlrpc_c::value> type("type", xmlrpc_c::value_string("Z"));
        std::pair<std::string, xmlrpc_c::value> value("varId", xmlrpc_c::value_int(idx));
        structData.insert(type);
        structData.insert(value);
        *retvalP = xmlrpc_c::value_struct( structData );
      }
      catch( const std::exception &e ){
        throw girerr::error( e.what() );
      }


    }

  private:
    mpplas::RandomFast* rnd;
};

class RandomZLessThanMethod : public xmlrpc_c::method {
  public:
    
    RandomZLessThanMethod() {
      this->_signature = "s:s";
      this->_help = "This method returns a random interger that is less than the given one"; 

      mpplas::MethodsFactory::getInstance()->getFunc(rnd);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::Z const op1(paramList.getString(0));
        paramList.verifyEnd(1);
        
        *retvalP = xmlrpc_c::value_string( (rnd->getIntegerBounded( op1 )).toString() );
      }

  private:
    mpplas::RandomFast* rnd;
};

/***********************************************
 **************** Primes ***********************
 ***********************************************/
class GenPrimeMethod : public xmlrpc_c::method {
  public:
    
    GenPrimeMethod() {
      this->_signature = "s:s";
      this->_help = "This method returns a prime of at least the specified number of bits"; 

      mpplas::MethodsFactory::getInstance()->getFunc(primes);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int bits = std::atoi( paramList.getString(0).c_str() );
        paramList.verifyEnd(1);
        
        *retvalP = xmlrpc_c::value_string( (primes->getPrime( bits )).toString() );
      }

  private:
    mpplas::GenPrimos* primes;
};

class PrimeTestMethod : public xmlrpc_c::method {
  public:
    
    PrimeTestMethod() {
      this->_signature = "b:s";
      this->_help = "This method returns true if its argument is prime"; 

      mpplas::MethodsFactory::getInstance()->getFunc(primeTest);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::Z const op(paramList.getString(0));
        paramList.verifyEnd(1);
        
        *retvalP = xmlrpc_c::value_boolean( primeTest->esPrimo( op ) );
      }

  private:
    mpplas::TestPrimoProb* primeTest;
};

/***********************************************
 ****************    GCD    ********************
 ***********************************************/
class GCDMethod : public xmlrpc_c::method {
  public:
    
    GCDMethod() {
      this->_signature = "s:ss";
      this->_help = "This method returns a the greatest common divisor of both integer arguments"; 

      mpplas::MethodsFactory::getInstance()->getFunc(gcd);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        mpplas::Z const op1(paramList.getString(0));
        mpplas::Z const op2(paramList.getString(1));

        paramList.verifyEnd(2);

        
        *retvalP = xmlrpc_c::value_string( (gcd->gcd(op1,op2)).toString() );
      }

  private:
    mpplas::GCD* gcd;
};

/***********************************************
 ****************    CRT    ********************
 ***********************************************/
class CRTMethod : public xmlrpc_c::method {
  public:
    
    CRTMethod() {
      this->_signature = "s:AA";
      this->_help = "This method returns the modular eq. system defined by the two arrays of integers given";

      mpplas::MethodsFactory::getInstance()->getFunc(crt);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

      std::vector<xmlrpc_c::value> y = paramList.getArray(0);
      std::vector<xmlrpc_c::value> m = paramList.getArray(1);

      paramList.verifyEnd(2);
      if ( y.size() != m.size() ){
          throw(girerr::error("Array parameters for the CRT should have the same length"));
      }

      mpplas::MiVec<mpplas::Z> yZ, mZ;
      for( int i = 0; i < y.size(); i++ ){ //both 

        yZ.push_back( mpplas::Z(( xmlrpc_c::value_string(y[i]) ) ));
        mZ.push_back( mpplas::Z(( xmlrpc_c::value_string(m[i]) ) ));
      }

      *retvalP = xmlrpc_c::value_string( (crt->crt(yZ, mZ)).toString() );
    }

  private:
    mpplas::CRT* crt;
};

/***********************************************
 ****************    MISC   ********************
 ***********************************************/
class SysInfoMethod : public xmlrpc_c::method { 
  public:

    SysInfoMethod() {
      this->_signature = "S:";
      this->_help = "This method returns a map with some information about the host system";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {

      paramList.verifyEnd(0);
      std::map<std::string, xmlrpc_c::value> structData;


      std::pair<std::string, xmlrpc_c::value> buildDate("BuildDate", 
          xmlrpc_c::value_string(mpplas::SystemInfo::getBuildDate()));

      std::pair<std::string, xmlrpc_c::value> buildTime("BuildTime", 
          xmlrpc_c::value_string(mpplas::SystemInfo::getBuildTime()));

      std::pair<std::string, xmlrpc_c::value> revisionNumber("RevisionNumber", 
          xmlrpc_c::value_int( mpplas::SystemInfo::getRevisionNumber() ));

      std::pair<std::string, xmlrpc_c::value> optimizationLevel("OptimizationLevel", 
          xmlrpc_c::value_int( mpplas::SystemInfo::getOptimizationLevel() ));

      std::pair<std::string, xmlrpc_c::value> isProfilingEnabled("ProfilingEnabled", 
          xmlrpc_c::value_boolean( mpplas::SystemInfo::isProfilingEnabled() ));

      std::pair<std::string, xmlrpc_c::value> isOpenMPEnabled("OpenMPEnabled", 
          xmlrpc_c::value_boolean( mpplas::SystemInfo::isOpenMPEnabled() ));

      std::pair<std::string, xmlrpc_c::value> isReleaseVersion("ReleaseVersion", 
          xmlrpc_c::value_boolean( mpplas::SystemInfo::isReleaseVersion() ));

      std::pair<std::string, xmlrpc_c::value> simdKernel("SIMDKernel", 
          xmlrpc_c::value_string( mpplas::SystemInfo::getSIMDKernel() ));

      std::pair<std::string, xmlrpc_c::value> compilerCmd("CompilerCmd", 
          xmlrpc_c::value_string( mpplas::SystemInfo::getCompilerCmd() ));

      const mpplas::CPUInfo& ci(mpplas::SystemInfo::getCPUInfo() );
      std::map<std::string, xmlrpc_c::value> cpuInfoData;
      std::pair<std::string, xmlrpc_c::value> l1Size("CacheL1Size",
          xmlrpc_c::value_int( ci.getCacheL1Size() ));
      std::pair<std::string, xmlrpc_c::value> l2Size("CacheL2Size",
          xmlrpc_c::value_int( ci.getCacheL2Size() ));
      std::pair<std::string, xmlrpc_c::value> l3Size("CacheL3Size",
          xmlrpc_c::value_int( ci.getCacheL3Size() ));
      std::pair<std::string, xmlrpc_c::value> modelName("ModelName",
          xmlrpc_c::value_string(ci.getModelName()));
      std::pair<std::string, xmlrpc_c::value> archName("ArchName",
          xmlrpc_c::value_string(ci.getArchName()));
      std::pair<std::string, xmlrpc_c::value> digitBitWidth("DigitBitWidth",
          xmlrpc_c::value_int( ci.getDigitBitWidth() ));

      std::vector<xmlrpc_c::value> arrayData;
      std::vector<std::string> simdCap = ci.getSIMDCapabilities();
      for(int i=0; i < simdCap.size(); i++){
        arrayData.push_back(xmlrpc_c::value_string( simdCap[i] ));
      }

      std::pair<std::string, xmlrpc_c::value> simdCapabilities("SIMDCapabilities",
          xmlrpc_c::value_array( xmlrpc_c::value_array(arrayData) ));

      cpuInfoData.insert(l1Size);
      cpuInfoData.insert(l2Size);
      cpuInfoData.insert(l3Size);
      cpuInfoData.insert(modelName);
      cpuInfoData.insert(archName);
      cpuInfoData.insert(digitBitWidth);
      cpuInfoData.insert(simdCapabilities);

      std::pair<std::string, xmlrpc_c::value> cpuInfo("CPUInfo", xmlrpc_c::value_struct(cpuInfoData) );

      structData.insert(buildDate);
      structData.insert(buildTime);
      structData.insert(revisionNumber);
      structData.insert(optimizationLevel );
      structData.insert(isProfilingEnabled );
      structData.insert(isOpenMPEnabled );
      structData.insert(isReleaseVersion );
      structData.insert(simdKernel );
      structData.insert(compilerCmd );
      structData.insert(cpuInfo);

      // Make an XML-RPC struct out of it
      *retvalP  = xmlrpc_c::value_struct(structData);
    }

  private:

};

/////////////// PROFILING //////////////////////////////

class StartProfilingClockMethod: public xmlrpc_c::method { 
  public:

    StartProfilingClockMethod() {
      this->_signature = "n:";
      this->_help = "This method marks the starting point in time for profiling clock";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {

      paramList.verifyEnd(0);
      mpplas::Profiling::getReference().startClock();

      *retvalP = xmlrpc_c::value_nil();
    }

};
class StopProfilingClockMethod: public xmlrpc_c::method { 
  public:

    StopProfilingClockMethod() {
      this->_signature = "d:";
      this->_help = "This method returns the time elapsed since the profiling clock was set to run";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {

      paramList.verifyEnd(0);
      double x =  mpplas::Profiling::getReference().stopClock();
      *retvalP = xmlrpc_c::value_double(x);
    }

};

class GetProfilingResultsMethod: public xmlrpc_c::method { 
  public:

    GetProfilingResultsMethod() {
      this->_signature = "A:";
      this->_help = "This method returns an array containing the profiling counters"
       "for each thread.";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {

      paramList.verifyEnd(0);
      std::vector<xmlrpc_c::value> threadsArray;

      const mpplas::Profiling& prof( mpplas::Profiling::getReference() );
      for( int i = 0; i < mpplas::SystemInfo::getMaxNumberOfThreads(); i++){
        const mpplas::ProfResult& profForThreadN( prof[i] );
        std::map<std::string, xmlrpc_c::value> threadResults;
        
        for( int j=0; j < mpplas::BasicCPU::__OpsEnum_SIZE; j++ ){
          const std::pair<std::string, xmlrpc_c::value> opTmp(
              mpplas::BasicCPU::OpsNames[j], 
              xmlrpc_c::value_int( profForThreadN[j] )
          );
          threadResults.insert( opTmp );
        }
        threadsArray.push_back(xmlrpc_c::value_struct(threadResults));
      }

      // Make an XML-RPC struct out of it
      *retvalP  = xmlrpc_c::value_array(threadsArray);

    }

};

class ResetProfilingCountersMethod: public xmlrpc_c::method { 
  public:

    ResetProfilingCountersMethod() {
      this->_signature = "n:";
      this->_help = "This method resets the profiling counters";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {

      paramList.verifyEnd(0);
      mpplas::Profiling::getReference().reset();

      *retvalP = xmlrpc_c::value_nil();

    }

};



///////////////////////////////////////////////////////////////////////////////////

int main(int const, const char ** const) {

    try {
        xmlrpc_c::registry myRegistry;

        xmlrpc_c::methodPtr const RequestClientIdP(new RequestClientId);
        xmlrpc_c::methodPtr const DiscardClientIdP(new DiscardClientId);
        
        xmlrpc_c::methodPtr const ZRunGCP(new ZRunGC);
        xmlrpc_c::methodPtr const ZCreateP(new ZCreate);
        xmlrpc_c::methodPtr const ZGetP(new ZGet);
        xmlrpc_c::methodPtr const ZAddMethodP(new ZAddMethod);
        xmlrpc_c::methodPtr const ZSubMethodP(new ZSubMethod);
        xmlrpc_c::methodPtr const ZMulMethodP(new ZMulMethod);
        xmlrpc_c::methodPtr const ZDivMethodP(new ZDivMethod);
        xmlrpc_c::methodPtr const ZModMethodP(new ZModMethod);
        xmlrpc_c::methodPtr const ZPowMethodP(new ZPowMethod);
        
        xmlrpc_c::methodPtr const ZFactorialMethodP(new ZFactorialMethod);

        xmlrpc_c::methodPtr const RAddMethodP(new RAddMethod);
        xmlrpc_c::methodPtr const RSubMethodP(new RSubMethod);
        xmlrpc_c::methodPtr const RMulMethodP(new RMulMethod);
        xmlrpc_c::methodPtr const RDivMethodP(new RDivMethod);
        xmlrpc_c::methodPtr const RPowMethodP(new RPowMethod);


        xmlrpc_c::methodPtr const ModExpMethodP(new ModExpMethod);
        xmlrpc_c::methodPtr const ModInverseMethodP(new ModInverseMethod);
        
        xmlrpc_c::methodPtr const RandomZMethodP(new RandomZMethod);
        xmlrpc_c::methodPtr const RandomZLessThanMethodP(new RandomZLessThanMethod);

        xmlrpc_c::methodPtr const GenPrimeMethodP(new GenPrimeMethod);
        xmlrpc_c::methodPtr const PrimeTestMethodP(new PrimeTestMethod);
        
        xmlrpc_c::methodPtr const GCDMethodP(new GCDMethod);
        
        xmlrpc_c::methodPtr const CRTMethodP(new CRTMethod);
        
        xmlrpc_c::methodPtr const SysInfoMethodP(new SysInfoMethod);


        xmlrpc_c::methodPtr const StartProfilingClockMethodP(
            new StartProfilingClockMethod);
        xmlrpc_c::methodPtr const StopProfilingClockMethodP(
            new StopProfilingClockMethod);
        xmlrpc_c::methodPtr const GetProfilingResultsMethodP(
            new GetProfilingResultsMethod);
        xmlrpc_c::methodPtr const ResetProfilingCountersMethodP(
            new ResetProfilingCountersMethod);



        myRegistry.addMethod("_requestClientId", RequestClientIdP);
        myRegistry.addMethod("_discardClientId", DiscardClientIdP);

        myRegistry.addMethod("_zRunGC", ZRunGCP);
        myRegistry.addMethod("zCreate", ZCreateP);
        myRegistry.addMethod("zGet", ZGetP);
        myRegistry.addMethod("zAdd", ZAddMethodP);
        myRegistry.addMethod("zSub", ZSubMethodP);
        myRegistry.addMethod("zMul", ZMulMethodP);
        myRegistry.addMethod("zDiv", ZDivMethodP);
        myRegistry.addMethod("zMod", ZModMethodP);
        myRegistry.addMethod("zPow", ZPowMethodP);

        myRegistry.addMethod("rAdd", RAddMethodP);
        myRegistry.addMethod("rSub", RSubMethodP);
        myRegistry.addMethod("rMul", RMulMethodP);
        myRegistry.addMethod("rDiv", RDivMethodP);
        myRegistry.addMethod("rPow", RPowMethodP);


        myRegistry.addMethod("zFactorial", ZFactorialMethodP);

        xmlrpc_c::methodPtr const MZAddMethodP(new MZAddMethod);
        xmlrpc_c::methodPtr const MZMulMethodP(new MZMulMethod);
        myRegistry.addMethod("mzAdd", MZAddMethodP);
        myRegistry.addMethod("mzMul", MZMulMethodP);


        xmlrpc_c::methodPtr const MZPPrintMethodP(new MZPPrintMethod);
        myRegistry.addMethod("_mzPPrint", MZPPrintMethodP);



        
        myRegistry.addMethod("modExp", ModExpMethodP);
        myRegistry.addMethod("modInverse", ModInverseMethodP);
        
        myRegistry.addMethod("getRandomZ", RandomZMethodP);
        myRegistry.addMethod("getRandomZLessThan", RandomZLessThanMethodP);

        myRegistry.addMethod("getPrime", GenPrimeMethodP);
        myRegistry.addMethod("isPrime", PrimeTestMethodP);
        
        myRegistry.addMethod("gcd", GCDMethodP);
        
        myRegistry.addMethod("crt", CRTMethodP);
        
        myRegistry.addMethod("systemInfo", SysInfoMethodP);
        
        
        myRegistry.addMethod("startProfClock", 
            StartProfilingClockMethodP);
        myRegistry.addMethod("stopProfClock", 
            StopProfilingClockMethodP);
        myRegistry.addMethod("getProfRes", 
            GetProfilingResultsMethodP);
        myRegistry.addMethod("resetProf", 
            ResetProfilingCountersMethodP);


        
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
	ServerDefaultHandler(&abyssServer, NULL);
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
