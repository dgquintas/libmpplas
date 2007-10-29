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

#include "MPPDataType.h"
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

std::set<clientId_t> _idsInUse;
RuntimeData<mpplas::MPPDataType*> table;

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

        bool res = false;
        const int clientId(paramList.getInt(0));
        paramList.verifyEnd(1);
    
        //remove data from the data table
        table.eraseClient(clientId);

        std::set<clientId_t>::iterator it = _idsInUse.find(clientId);
        if( it != _idsInUse.end() ){
          _idsInUse.erase(it);
        }
        res = true;

        *retvalP = xmlrpc_c::value_boolean(res);
      }

};


/***********************************************
 ************** INTEGERS ***********************
 ***********************************************/


class RunGC: public xmlrpc_c::method {
  public:
    
    RunGC() {
      this->_signature = "n:iA";
      this->_help = "This method garbage collects the internal table of Z's";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::vector<xmlrpc_c::value> tmp = paramList.getArray(1);

        paramList.verifyEnd(2);

        std::vector< RuntimeData<mpplas::Z>::varId_t > usedSlots( tmp.size() );
        for(int i=0; i< tmp.size(); i++){
          usedSlots.push_back( xmlrpc_c::value_string( tmp[i] ) );
        }

        table.runGC(clientId, usedSlots);

        *retvalP = xmlrpc_c::value_nil();
      }
};


class ZCreate: public xmlrpc_c::method {
  public:
    
    ZCreate() {
      this->_signature = "s:is";
      this->_help = "This method creates a new integer";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        mpplas::Z* const op( new mpplas::Z(paramList.getString(1)));

        paramList.verifyEnd(2);

        const std::string varId(table.set(clientId, op, "Z"));

        *retvalP = xmlrpc_c::value_string(varId);
      }
};

class GetData: public xmlrpc_c::method {
  public:
    
    GetData() {
      this->_signature = "s:is";
      this->_help = "To retrieve data";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId(paramList.getString(1));

        paramList.verifyEnd(2);

        try{
          const mpplas::MPPDataType* const data( table.get(clientId, varId));
          *retvalP = xmlrpc_c::value_string(data->toString() );
        }
        catch(const NoSuchVariable& e){
          throw(girerr::error(e.what()));
        }

      }
};

class ZAddMethod : public xmlrpc_c::method {
  public:
    
    ZAddMethod() {
      this->_signature = "s:iss";
      this->_help = "This method adds two integers together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
          const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::Z(op1+op2), "Z");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};
class ZSubMethod : public xmlrpc_c::method {
  public:
    
    ZSubMethod() {
      this->_signature = "s:iss";
      this->_help = "This method substracts two integers";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
          const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::Z(op1-op2), "Z");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};
class ZMulMethod : public xmlrpc_c::method {
  public:
    
    ZMulMethod() {
      this->_signature = "s:iss";
      this->_help = "This method multiplies two integers together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
          const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::Z(op1 * op2), "Z");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};
class ZDivMethod : public xmlrpc_c::method {
  public:
    
    ZDivMethod() {
      this->_signature = "s:iss";
      this->_help = "This method divides (integer division) two integers";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
          const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::Z(op1/op2), "Z");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};
class ZModMethod : public xmlrpc_c::method {
  public:
    
    ZModMethod() {
      this->_signature = "s:iss";
      this->_help = "This method calculates de remainder of the integer division of two integers";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
          const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::Z(op1%op2), "Z");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};

class ZFactorialMethod : public xmlrpc_c::method {
  public:
    
    ZFactorialMethod() {
      this->_signature = "s:is";
      this->_help = "This method returns the factorial of the given integer"; 
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));

        paramList.verifyEnd(2);

        mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
 
        const std::string varId = table.set(clientId, new mpplas::Z( op1.factorial() ), "Z");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};
class ZPowMethod : public xmlrpc_c::method {
  public:
    
    ZPowMethod() {
      this->_signature = "s:iss";
      this->_help = "This method returns the exponentiation of the first argument (base) by the second (exponent)"; 
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(1));

        paramList.verifyEnd(3);

        const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
        const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));


        const std::string varId = table.set(clientId, new mpplas::Z(  op1 ^ op2 ), "Z");
        
        *retvalP = xmlrpc_c::value_string( varId );

      }
};


class ZBitLength: public xmlrpc_c::method {
  public:
    
    ZBitLength() {
      this->_signature = "i:ii";
      this->_help = "This method returns the bit-length of an integer";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId(paramList.getString(1));

        paramList.verifyEnd(2);

          const mpplas::Z z( *((mpplas::Z*)table.get(clientId, varId)));
        const int res( z.getBitLength() );

        *retvalP = xmlrpc_c::value_int(res);
      }
};


/***********************************************
 **************   REALS  ***********************
 ***********************************************/

class RCreate: public xmlrpc_c::method {
  public:
    
    RCreate() {
      this->_signature = "s:is";
      this->_help = "This method creates a new real";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        mpplas::R* const op( new mpplas::R(paramList.getString(1)));

        paramList.verifyEnd(2);

        const std::string varId = table.set(clientId, op, "R");

        *retvalP = xmlrpc_c::value_string(varId);
      }
};

class RAddMethod : public xmlrpc_c::method {
  public:
    
    RAddMethod() {
      this->_signature = "s:iii";
      this->_help = "This method adds two reals together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::R op1( *((mpplas::R*)table.get(clientId, varId1)));
        const mpplas::R op2( *((mpplas::R*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::R(op1+op2), "R");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};


class RSubMethod : public xmlrpc_c::method {
  public:
    
    RSubMethod() {
      this->_signature = "s:iss";
      this->_help = "This method substracts two reals";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::R op1( *((mpplas::R*)table.get(clientId, varId1)));
          const mpplas::R op2( *((mpplas::R*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::R(op1-op2), "R");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};
class RMulMethod : public xmlrpc_c::method {
  public:
    
    RMulMethod() {
      this->_signature = "s:iss";
      this->_help = "This method multiplies two reals together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::R op1( *((mpplas::R*)table.get(clientId, varId1)));
          const mpplas::R op2( *((mpplas::R*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::R(op1 * op2), "R");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};
class RDivMethod : public xmlrpc_c::method {
  public:
    
    RDivMethod() {
      this->_signature = "s:iss";
      this->_help = "This method divides two reals";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::R op1( *((mpplas::R*)table.get(clientId, varId1)));
          const mpplas::R op2( *((mpplas::R*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::R(op1/op2), "R");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};

class RPowMethod : public xmlrpc_c::method {
  public:
    
    RPowMethod() {
      this->_signature = "s:iss";
      this->_help = "This method returns the exponentiation of the first argument (base) by the second (exponent)"; 
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(1));

        paramList.verifyEnd(3);

        const mpplas::R op1( *((mpplas::R*)table.get(clientId, varId1)));
        const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));


        const std::string varId = table.set(clientId, new mpplas::R(  op1 ^ op2 ), "R");
        
        *retvalP = xmlrpc_c::value_string( varId );

      }
};







class RBitLength: public xmlrpc_c::method {
  public:
    
    RBitLength() {
      this->_signature = "i:ii";
      this->_help = "This method returns the bit-length of an integer";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId(paramList.getString(1));

        paramList.verifyEnd(2);

        const mpplas::R r( *((mpplas::R*)table.get(clientId, varId)));
        const int res( r.getBitLength() );

        *retvalP = xmlrpc_c::value_int(res);
      }
};



/***********************************************
 *************  MODULAR INTEGERS ***************
 ***********************************************/
class ModExpMethod : public xmlrpc_c::method {
  public:
    
    ModExpMethod() {
      this->_signature = "s:isss";
      this->_help = "This method returns the result of the modular exponentiation (arg1 ^ arg2) MOD arg3"; 

      mpplas::MethodsFactory::getInstance()->getFunc(pmod);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));
        const std::string varId3(paramList.getString(3));

        paramList.verifyEnd(4);

        mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
        const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));
        const mpplas::Z op3( *((mpplas::Z*)table.get(clientId, varId3)));

        pmod->potModular(&op1,op2,op3);
        const std::string varId = table.set(clientId, new mpplas::Z( op1 ), "Z");
        
        *retvalP = xmlrpc_c::value_string( varId );
      }

  private:
    mpplas::PotModular* pmod;
};

class ModInverseMethod : public xmlrpc_c::method {
  public:
    
    ModInverseMethod() {
      this->_signature = "s:iss";
      this->_help = "This method returns the result of the modular inverse (arg1 ^ -1) MOD arg2"; 

      mpplas::MethodsFactory::getInstance()->getFunc(pmod);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
        const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));

        mpplas::Z* newInst; 
        try {
          newInst = new mpplas::Z( pmod->inversa(op1,op2) );
        }
        catch(const std::exception& e){
          throw(girerr::error(e.what()));
        }

        const std::string varId = table.set(clientId, newInst , "Z");
        
        *retvalP = xmlrpc_c::value_string( varId );

      }

  private:
    mpplas::PotModular* pmod;
};







/***********************************************
 ************** INTEGER MATRICES ****************
 ***********************************************/
class MZCreate: public xmlrpc_c::method {
  public:
    
    MZCreate() {
      this->_signature = "s:is";
      this->_help = "This method creates a new integer matrix";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        mpplas::MatrixZ* const op( new mpplas::MatrixZ(paramList.getString(1)));

        paramList.verifyEnd(2);

        const std::string varId(table.set(clientId, op, "MZ"));

        *retvalP = xmlrpc_c::value_string(varId);
      }
};

class MZAddMethod : public xmlrpc_c::method {
  public:
    
    MZAddMethod() {
      this->_signature = "s:iss";
      this->_help = "This method adds two integer matrices together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::MatrixZ op1( *((mpplas::MatrixZ*)table.get(clientId, varId1)));
        const mpplas::MatrixZ op2( *((mpplas::MatrixZ*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::MatrixZ(op1+op2), "MZ");

        *retvalP = xmlrpc_c::value_string( varId );
      }

};
class MZMulMethod : public xmlrpc_c::method {
  public:
    
    MZMulMethod() {
      this->_signature = "s:iss";
      this->_help = "This method multiplies two integer matrices";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::MatrixZ op1( *((mpplas::MatrixZ*)table.get(clientId, varId1)));
        const mpplas::MatrixZ op2( *((mpplas::MatrixZ*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::MatrixZ(op1*op2), "MZ");

        *retvalP = xmlrpc_c::value_string( varId );
      }

};


class MZPPrintMethod : public xmlrpc_c::method {
  public:
    
    MZPPrintMethod() {
      this->_signature = "s:is";
      this->_help = "This method returns an alternative representation of the matrix, more human readable";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId(paramList.getString(1));

        const mpplas::MatrixZ* const op1( (mpplas::MatrixZ*)table.get(clientId, varId));
        
        paramList.verifyEnd(2);

        std::ostringstream oss;
        oss << (*op1);

        *retvalP = xmlrpc_c::value_string( oss.str() );
      }
};



/***********************************************
 ************** RANDOM Z ***********************
 ***********************************************/
class RandomZMethod : public xmlrpc_c::method {
  public:
    
    RandomZMethod() {
      this->_signature = "s:ii";
      this->_help = "This method returns a random interger of the specified number of bits"; 

      mpplas::MethodsFactory::getInstance()->getFunc(rnd);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

      const int clientId(paramList.getInt(0));
      const int bits = paramList.getInt(1);
      paramList.verifyEnd(2);

      mpplas::Z* const op( new mpplas::Z(rnd->getInteger( bits )));
      const std::string varId = table.set(clientId, op, "Z");

      *retvalP = xmlrpc_c::value_string(varId);
    }

  private:
    mpplas::RandomFast* rnd;
};

class RandomZLessThanMethod : public xmlrpc_c::method {
  public:
    
    RandomZLessThanMethod() {
      this->_signature = "s:is";
      this->_help = "This method returns a random interger that is less than the given one"; 

      mpplas::MethodsFactory::getInstance()->getFunc(rnd);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
      const int clientId(paramList.getInt(0));
      const std::string varId1(paramList.getString(1));

      paramList.verifyEnd(2);

      const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));

      const std::string varId = table.set(clientId, new mpplas::Z( rnd->getIntegerBounded(op1)), "Z");

      *retvalP = xmlrpc_c::value_string(varId);
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
      this->_signature = "s:ii";
      this->_help = "This method returns a prime of at least the specified number of bits"; 

      mpplas::MethodsFactory::getInstance()->getFunc(primes);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
      const int clientId(paramList.getInt(0));
      const int bits = paramList.getInt(1);
      paramList.verifyEnd(2);

      try{
        mpplas::Z* const op( new mpplas::Z(primes->getPrime( bits ) ));
        const std::string varId = table.set(clientId, op, "Z");

        *retvalP = xmlrpc_c::value_string(varId);
      }
      catch( const std::exception &e ){
        throw girerr::error( e.what() );
      }

    }

  private:
    mpplas::GenPrimos* primes;
};

class PrimeTestMethod : public xmlrpc_c::method {
  public:
    
    PrimeTestMethod() {
      this->_signature = "b:is";
      this->_help = "This method returns true if its argument is prime"; 

      mpplas::MethodsFactory::getInstance()->getFunc(primeTest);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

      const int clientId(paramList.getInt(0));
      const std::string varId(paramList.getString(1));
      paramList.verifyEnd(2);

      const mpplas::Z op( *((mpplas::Z*)table.get(clientId, varId)));

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
      this->_signature = "s:iss";
      this->_help = "This method returns a the greatest common divisor of both integer arguments"; 

      mpplas::MethodsFactory::getInstance()->getFunc(gcd);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

      const int clientId(paramList.getInt(0));
      const std::string varId1(paramList.getString(1));
      const std::string varId2(paramList.getString(2));
      paramList.verifyEnd(3);

      const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
      const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));
 
      try{
        const std::string varId = table.set(clientId, new mpplas::Z(gcd->gcd(op1,op2)), "Z");
        *retvalP = xmlrpc_c::value_string( varId );
      }
      catch(const std::exception& e){
        throw(girerr::error(e.what()));
      }
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
      this->_signature = "s:iAA";
      this->_help = "This method returns the modular eq. system defined by the two arrays of integers given";

      mpplas::MethodsFactory::getInstance()->getFunc(crt);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

      const int clientId(paramList.getInt(0));
      std::vector<xmlrpc_c::value> y = paramList.getArray(1);
      std::vector<xmlrpc_c::value> m = paramList.getArray(2);

      paramList.verifyEnd(3);
      if ( y.size() != m.size() ){
        throw(girerr::error("Array parameters for the CRT should have the same length"));
      }

      mpplas::MiVec<mpplas::Z> yZ, mZ;
      for( int i = 0; i < y.size(); i++ ){ //both 
        yZ.push_back( mpplas::Z(( xmlrpc_c::value_string(y[i]) ) ));
        mZ.push_back( mpplas::Z(( xmlrpc_c::value_string(m[i]) ) ));
      }
      
      try{
        const std::string varId = table.set(clientId, new mpplas::Z( crt->crt(yZ, mZ) ), "Z");
        *retvalP = xmlrpc_c::value_string( varId );
      }
      catch(const std::exception& e){
        throw(girerr::error(e.what()));
      }

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
      this->_signature = "S:i";
      this->_help = "This method returns a map with some information about the host system";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {

      paramList.verifyEnd(1); //the clientId isn't used
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

      std::pair<std::string, xmlrpc_c::value> maxNumOfThreads("MaxNumberOfThreads", 
          xmlrpc_c::value_int( mpplas::SystemInfo::getMaxNumberOfThreads() ));

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
      structData.insert(maxNumOfThreads);
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
      this->_signature = "n:i";
      this->_help = "This method marks the starting point in time for profiling clock";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {

      paramList.verifyEnd(1); //the clientId isn't used
      mpplas::Profiling::getReference().startClock();

      *retvalP = xmlrpc_c::value_nil();
    }

};
class StopProfilingClockMethod: public xmlrpc_c::method { 
  public:

    StopProfilingClockMethod() {
      this->_signature = "d:i";
      this->_help = "This method returns the time elapsed since the profiling clock was set to run";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {

      paramList.verifyEnd(1); //the clientId isn't used
      double x =  mpplas::Profiling::getReference().stopClock();
      *retvalP = xmlrpc_c::value_double(x);
    }

};

class GetProfilingResultsMethod: public xmlrpc_c::method { 
  public:

    GetProfilingResultsMethod() {
      this->_signature = "A:i";
      this->_help = "This method returns an array containing the profiling counters"
        "for each thread.";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {
      paramList.verifyEnd(1); //clientId isn't used
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
      this->_signature = "n:i";
      this->_help = "This method resets the profiling counters";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {

      paramList.verifyEnd(1);//clientId isn't used
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


    xmlrpc_c::methodPtr const GetDataP(new GetData);

    xmlrpc_c::methodPtr const RunGCP(new RunGC);
    xmlrpc_c::methodPtr const ZCreateP(new ZCreate);
    xmlrpc_c::methodPtr const ZAddMethodP(new ZAddMethod);
    xmlrpc_c::methodPtr const ZSubMethodP(new ZSubMethod);
    xmlrpc_c::methodPtr const ZMulMethodP(new ZMulMethod);
    xmlrpc_c::methodPtr const ZDivMethodP(new ZDivMethod);
    xmlrpc_c::methodPtr const ZModMethodP(new ZModMethod);
    xmlrpc_c::methodPtr const ZPowMethodP(new ZPowMethod);
    xmlrpc_c::methodPtr const ZBitLengthP(new ZBitLength);

    xmlrpc_c::methodPtr const ZFactorialMethodP(new ZFactorialMethod);

    xmlrpc_c::methodPtr const RCreateP(new RCreate);
    xmlrpc_c::methodPtr const RAddMethodP(new RAddMethod);
    xmlrpc_c::methodPtr const RSubMethodP(new RSubMethod);
    xmlrpc_c::methodPtr const RMulMethodP(new RMulMethod);
    xmlrpc_c::methodPtr const RDivMethodP(new RDivMethod);
    xmlrpc_c::methodPtr const RPowMethodP(new RPowMethod);
    xmlrpc_c::methodPtr const RBitLengthP(new RBitLength);


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


    myRegistry.addMethod("getData", GetDataP);

    myRegistry.addMethod("_runGC", RunGCP);
    myRegistry.addMethod("zCreate", ZCreateP);
    myRegistry.addMethod("zAdd", ZAddMethodP);
    myRegistry.addMethod("zSub", ZSubMethodP);
    myRegistry.addMethod("zMul", ZMulMethodP);
    myRegistry.addMethod("zDiv", ZDivMethodP);
    myRegistry.addMethod("zMod", ZModMethodP);
    myRegistry.addMethod("zPow", ZPowMethodP);
    myRegistry.addMethod("zBitLength", ZBitLengthP);

    myRegistry.addMethod("rCreate", RCreateP);
    myRegistry.addMethod("rAdd", RAddMethodP);
    myRegistry.addMethod("rSub", RSubMethodP);
    myRegistry.addMethod("rMul", RMulMethodP);
    myRegistry.addMethod("rDiv", RDivMethodP);
    myRegistry.addMethod("rPow", RPowMethodP);
    myRegistry.addMethod("rBitLength", RBitLengthP);


    myRegistry.addMethod("zFactorial", ZFactorialMethodP);

    xmlrpc_c::methodPtr const MZCreateP(new MZCreate);
    xmlrpc_c::methodPtr const MZAddMethodP(new MZAddMethod);
    xmlrpc_c::methodPtr const MZMulMethodP(new MZMulMethod);
    myRegistry.addMethod("mzCreate", MZCreateP);
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

    myRegistry.addMethod("getSystemInfo", SysInfoMethodP);


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
