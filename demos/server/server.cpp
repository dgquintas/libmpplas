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
#include "Z_n.h"
#include "ZM_n.h"
#include "MatrixZ.h"
#include "MatrixR.h"
#include "MatrixGFx.h"
#include "R.h"
#include "Random.h"
#include "Primos.h"
#include "Factor.h"
#include "GCD.h"
#include "CRT.h"
#include "LCM.h"
#include "Potencia.h"
#include "MethodsFactory.h"
#include "SystemInfo.h"
#include "BasicTypedefs.h"
#include "Profiling.h"
#include "Errors.h"
#include "GF.h"
#include "GFx.h"

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
      this->_help = "Returns a valid clientId";
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
      this->_help = "Discards the given clientId and all the date associated with it";
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
class RunGC: public xmlrpc_c::method {
  public:
    
    RunGC() {
      this->_signature = "n:iA";
      this->_help = "Starts the garbage collection";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::vector<xmlrpc_c::value> tmp = paramList.getArray(1);

        paramList.verifyEnd(2);

        std::vector< varId_t > usedSlots( tmp.size() );
        for(int i=0; i< tmp.size(); i++){
          usedSlots.push_back( xmlrpc_c::value_string( tmp[i] ) );
        }

        table.runGC(clientId, usedSlots);

        *retvalP = xmlrpc_c::value_nil();
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


class GetHRStringMethod : public xmlrpc_c::method {
  public:
    
    GetHRStringMethod() {
      this->_signature = "s:is";
      this->_help = "Returns a human readable representation of the data";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId(paramList.getString(1));

        const mpplas::MPPDataType* const op1(table.get(clientId, varId));
        
        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_string( op1->toHRString() );
      }
};


/***********************************************
 ************** INTEGERS ***********************
 ***********************************************/

class ZCreate: public xmlrpc_c::method {
  public:
    
    ZCreate() {
      this->_signature = "s:is";
      this->_help = "Creates a new integer";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        mpplas::Z* const op( new mpplas::Z(paramList.getString(1)));

        paramList.verifyEnd(2);

        const std::string varId(table.set(clientId, op, "Z"));

        *retvalP = xmlrpc_c::value_string(varId);
      }
};


class ZAddMethod : public xmlrpc_c::method {
  public:
    
    ZAddMethod() {
      this->_signature = "s:iss";
      this->_help = "Adds two integers together";
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
      this->_help = "Substracts two integers";
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
      this->_help = "Multiplies two integers together";
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
      this->_help = "Divides (integer division) two integers";
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
      this->_help = "Calculates de remainder of the integer division of two integers";
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
      this->_help = "Returns the factorial of the given integer"; 
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
      this->_help = "Returns the exponentiation of the first argument (base) by the second (exponent)"; 
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

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
      this->_help = "Returns the bit-length of an integer";
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


class ZCompare: public xmlrpc_c::method {
  public:
    
    ZCompare() {
      this->_signature = "i:iss";
      this->_help = "Returns an integer constant encoding the relationship between the two integer arguments"
        "-1 meaning the first arg. is < then the second. 0 meaning they are equal. 1 meaning the first in > than the second;";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
        const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));

        int res;
        if( op1 < op2 ){
          res = -1;
        } 
        else if( op1 == op2 ){
          res = 0;
        }
        else if( op1 > op2 ){
          res = 1;
        }

        *retvalP = xmlrpc_c::value_int(res);
      }
};



/***********************************************
 *********** MODULAR INTEGERS ******************
 ***********************************************/

class Z_nCreate: public xmlrpc_c::method {
  public:
    
    Z_nCreate() {
      this->_signature = "s:is";
      this->_help = "Creates a new modular integer from the given modulus and initial value";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

      const int clientId(paramList.getInt(0));
      const std::string varId1(paramList.getString(1));
      const std::string varId2(paramList.getString(2));

      paramList.verifyEnd(3);

      const mpplas::Z ini( *((mpplas::Z*)table.get(clientId, varId1)));
      const mpplas::Z mod( *((mpplas::Z*)table.get(clientId, varId2)));

      mpplas::Z_n* const op( new mpplas::Z_n(ini,mod));

      const std::string varId(table.set(clientId, op, "Z_n"));

      *retvalP = xmlrpc_c::value_string(varId);
    }
};


class Z_nAddMethod : public xmlrpc_c::method {
  public:
    
    Z_nAddMethod() {
      this->_signature = "s:iss";
      this->_help = "Adds two modular integers together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::Z_n op1( *((mpplas::Z_n*)table.get(clientId, varId1)));
          const mpplas::Z_n op2( *((mpplas::Z_n*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::Z_n(op1+op2), "Z_n");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};
class Z_nSubMethod : public xmlrpc_c::method {
  public:
    
    Z_nSubMethod() {
      this->_signature = "s:iss";
      this->_help = "Substracts two modular integers";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::Z_n op1( *((mpplas::Z_n*)table.get(clientId, varId1)));
          const mpplas::Z_n op2( *((mpplas::Z_n*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::Z_n(op1-op2), "Z_n");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};
class Z_nMulMethod : public xmlrpc_c::method {
  public:
    
    Z_nMulMethod() {
      this->_signature = "s:iss";
      this->_help = "Multiplies two modular integers together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::Z_n op1( *((mpplas::Z_n*)table.get(clientId, varId1)));
          const mpplas::Z_n op2( *((mpplas::Z_n*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::Z_n(op1 * op2), "Z_n");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};
class Z_nDivMethod : public xmlrpc_c::method {
  public:
    
    Z_nDivMethod() {
      this->_signature = "s:iss";
      this->_help = "Divides (integer division) two modular integers";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::Z_n op1( *((mpplas::Z_n*)table.get(clientId, varId1)));
          const mpplas::Z_n op2( *((mpplas::Z_n*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::Z_n(op1/op2), "Z_n");

        *retvalP = xmlrpc_c::value_string( varId );
      }
};

class Z_nInvMethod : public xmlrpc_c::method {
  public:
    
    Z_nInvMethod() {
      this->_signature = "s:is";
      this->_help = "Returns the inverse (if it exists) of the given modular integer";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        paramList.verifyEnd(2);

        try{
          mpplas::Z_n op1( *((mpplas::Z_n*)table.get(clientId, varId1)));
          op1.inverse(); 
          const std::string varId = table.set(clientId, new mpplas::Z_n(op1), "Z_n");
          *retvalP = xmlrpc_c::value_string( varId );
        }
        catch(const std::exception& e){
          throw(girerr::error(e.what()));
        }
      }
};


class Z_nPowMethod : public xmlrpc_c::method {
  public:
    
    Z_nPowMethod() {
      this->_signature = "s:iss";
      this->_help = "Returns the exponentiation of the first argument (base) by the second (exponent)"; 
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::Z_n op1( *((mpplas::Z_n*)table.get(clientId, varId1)));
        const mpplas::Z op2( *((mpplas::Z_n*)table.get(clientId, varId2)));


        const std::string varId = table.set(clientId, new mpplas::Z_n(  op1 ^ op2 ), "Z_n");
        
        *retvalP = xmlrpc_c::value_string( varId );

      }
};



/***********************************************
 **************   REALS  ***********************
 ***********************************************/

class RSetInternalPrecision: public xmlrpc_c::method {
  public:
    
    RSetInternalPrecision() {
      this->_signature = "i:ii";
      this->_help = "Changes the internal precision (in bits) used to represent real numbers";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const int prec( paramList.getInt(1) );
        paramList.verifyEnd(2);

        mpplas::R::precision(prec);

        *retvalP = xmlrpc_c::value_int(prec);
      }
};

class RSetOutputPrecision: public xmlrpc_c::method {
  public:
    RSetOutputPrecision() {
      this->_signature = "i:ii";
      this->_help = "Changes the precision (in digits) with which real numbers "
        "will be displayed. A value of 0 means to use the maximum posible precision";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const int prec( paramList.getInt(1) );
        paramList.verifyEnd(2);

        mpplas::R::precisionSalida(prec);

        *retvalP = xmlrpc_c::value_int(prec);
      }
};


class RGetInternalPrecision: public xmlrpc_c::method {
  public:
    
    RGetInternalPrecision() {
      this->_signature = "i:i";
      this->_help = "Returns the internal precision (in bits) used to represent real numbers";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const int prec( paramList.getInt(1) );
        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_int(mpplas::R::precision());
      }
};

class RGetOutputPrecision: public xmlrpc_c::method {
  public:
    RGetOutputPrecision() {
      this->_signature = "i:ii";
      this->_help = "Returns the precision (in digits) with which real numbers "
        "will be displayed. A value of 0 means to use the maximum posible precision";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const int prec( paramList.getInt(1) );
        paramList.verifyEnd(2);

        *retvalP = xmlrpc_c::value_int(mpplas::R::precisionSalida());
      }
};



class RCreate: public xmlrpc_c::method {
  public:
    
    RCreate() {
      this->_signature = "s:is";
      this->_help = "Creates a new real";
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
      this->_help = "Adds two reals together";
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
      this->_help = "Substracts two reals";
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
      this->_help = "Multiplies two reals together";
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
      this->_help = "Divides two reals";
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
      this->_help = "Returns the exponentiation of the first argument (base) by the second (exponent)"; 
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
      this->_help = "Returns the bit-length of an integer";
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

class RCompare: public xmlrpc_c::method {
  public:
    
    RCompare() {
      this->_signature = "i:iss";
      this->_help = "Returns an integer constant encoding the relationship between the two real arguments"
        "-1 meaning the first arg. is < then the second. 0 meaning they are equal. 1 meaning the first in > than the second;";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::R op1( *((mpplas::R*)table.get(clientId, varId1)));
        const mpplas::R op2( *((mpplas::R*)table.get(clientId, varId2)));

        int res;
        if( op1 < op2 ){
          res = -1;
        } 
        else if( op1 == op2 ){
          res = 0;
        }
        else if( op1 > op2 ){
          res = 1;
        }

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
      this->_help = "Returns the result of the modular exponentiation (arg1 ^ arg2) MOD arg3"; 

      mpplas::MethodsFactory::getInstance()->getFunc(pmod);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));
        const std::string varId3(paramList.getString(3));

        paramList.verifyEnd(4);

        const mpplas::Z base( *((mpplas::Z*)table.get(clientId, varId1)));
        const mpplas::Z exp( *((mpplas::Z*)table.get(clientId, varId2)));
        const mpplas::Z mod( *((mpplas::Z*)table.get(clientId, varId3)));

        mpplas::Z_n op(base, mod);

        pmod->exponentiation(&op,exp);
        const std::string varId = table.set(clientId, new mpplas::Z( op ), "Z");
        
        *retvalP = xmlrpc_c::value_string( varId );
      }

  private:
    mpplas::Exponentiation< mpplas::Z_n >* pmod;
};

class ModInverseMethod : public xmlrpc_c::method {
  public:
    
    ModInverseMethod() {
      this->_signature = "s:iss";
      this->_help = "Returns the result of the modular inverse (arg1 ^ -1) MOD arg2"; 

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
          newInst = new mpplas::Z( pmod->inverse(op1,op2) );
        }
        catch(const std::exception& e){
          throw(girerr::error(e.what()));
        }

        const std::string varId = table.set(clientId, newInst , "Z");
        
        *retvalP = xmlrpc_c::value_string( varId );

      }

  private:
    mpplas::Exponentiation< mpplas::Z_n >* pmod;
};

/***********************************************
 ************** POLYNOMIALS ********************
 ***********************************************/



/***********************************************
 ************** FINITE FIELDS ******************
 ***********************************************/

class GFCreate: public xmlrpc_c::method {
  public:
    
    GFCreate() {
      this->_signature = "s:isib";
      this->_help = "Creates a new finite field generator";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));

        const std::string varId1(paramList.getString(1));
        const mpplas::Z p( *((mpplas::Z*)table.get(clientId, varId1)));

        const int n(paramList.getInt(2));
        const bool usePrimitive(paramList.getBoolean(3));

        paramList.verifyEnd(4);

        try{ 
          mpplas::GF* const op( new mpplas::GF(p,n,usePrimitive) ); 
          const std::string varId(table.set(clientId, op, "GF"));

          *retvalP = xmlrpc_c::value_string(varId);


        }
        catch( const std::exception &e ){
          throw girerr::error( e.what() );
        }


    }
};

class GFxCreate: public xmlrpc_c::method {
  public:
    
    GFxCreate() {
      this->_signature = "s:iss";
      this->_help = "Returns an element from the given finite field";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));

        const std::string varId1(paramList.getString(1));
        const mpplas::GF* const gfGen( (mpplas::GF*)table.get(clientId, varId1));

        const std::string poly(paramList.getString(2));

        paramList.verifyEnd(3);

        try{ 
          mpplas::GFx* const op( new mpplas::GFx( gfGen->getElement(poly) )  ); 
          const std::string varId(table.set(clientId, op, "GFx"));

          *retvalP = xmlrpc_c::value_string(varId);


        }
        catch( const std::exception &e ){
          throw girerr::error( e.what() );
        }


    }
};


class GFxAddMethod : public xmlrpc_c::method {
  public:
    
    GFxAddMethod() {
      this->_signature = "s:iss";
      this->_help = "Adds two elements of a finite field together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::GFx op1( *((mpplas::GFx*)table.get(clientId, varId1)));
          const mpplas::GFx op2( *((mpplas::GFx*)table.get(clientId, varId2)));
          
          try{ 
            const std::string varId = table.set(clientId, new mpplas::GFx(op1+op2), "GFx");
            *retvalP = xmlrpc_c::value_string( varId );
          }
          catch(const std::exception& e){
            throw(girerr::error(e.what()));
          }



      }
};
class GFxSubMethod : public xmlrpc_c::method {
  public:
    
    GFxSubMethod() {
      this->_signature = "s:iss";
      this->_help = "Substracts two elements of a finite field";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::GFx op1( *((mpplas::GFx*)table.get(clientId, varId1)));
          const mpplas::GFx op2( *((mpplas::GFx*)table.get(clientId, varId2)));

          try{ 
            const std::string varId = table.set(clientId, new mpplas::GFx(op1-op2), "GFx");
            *retvalP = xmlrpc_c::value_string( varId );
          }
          catch(const std::exception& e){
            throw(girerr::error(e.what()));
          }

      }
};
class GFxMulMethod : public xmlrpc_c::method {
  public:
    
    GFxMulMethod() {
      this->_signature = "s:iss";
      this->_help = "Multiplies two elements of a finite field";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::GFx op1( *((mpplas::GFx*)table.get(clientId, varId1)));
          const mpplas::GFx op2( *((mpplas::GFx*)table.get(clientId, varId2)));

          try{ 
            const std::string varId = table.set(clientId, new mpplas::GFx(op1*op2), "GFx");
            *retvalP = xmlrpc_c::value_string( varId );
          }
          catch(const std::exception& e){
            throw(girerr::error(e.what()));
          }

      }
};
class GFxDivMethod : public xmlrpc_c::method {
  public:
    
    GFxDivMethod() {
      this->_signature = "s:iss";
      this->_help = "Divides two elements of a finite field";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

          const mpplas::GFx op1( *((mpplas::GFx*)table.get(clientId, varId1)));
          const mpplas::GFx op2( *((mpplas::GFx*)table.get(clientId, varId2)));
 
          try{ 
            const std::string varId = table.set(clientId, new mpplas::GFx(op1/op2), "GFx");
            *retvalP = xmlrpc_c::value_string( varId );
          }
          catch(const std::exception& e){
            throw(girerr::error(e.what()));
          }

      }
};
class GFxInvMethod : public xmlrpc_c::method {
  public:
    
    GFxInvMethod() {
      this->_signature = "s:is";
      this->_help = "Returns the inverse of a finite field element";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));

        paramList.verifyEnd(2);

          const mpplas::GFx op1( *((mpplas::GFx*)table.get(clientId, varId1)));
          try{ 
            const std::string varId = table.set(clientId, new mpplas::GFx( op1.getInverse() ), "GFx");
            *retvalP = xmlrpc_c::value_string( varId );
          }
          catch(const std::exception& e){
            throw(girerr::error(e.what()));
          }


      }
};

class GFxGetPBRString: public xmlrpc_c::method {
  public:
    GFxGetPBRString() {
      this->_signature = "s:is";
      this->_help = "Returns an string representing the Polynomial Basis Representation of the finite field element";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        paramList.verifyEnd(2);

        const mpplas::GFx op1( *((mpplas::GFx*)table.get(clientId, varId1)));

        *retvalP = xmlrpc_c::value_string( op1.getPBRString() );
      }
};



class GFGetProperties: public xmlrpc_c::method {
  public:
    
    GFGetProperties() {
      this->_signature = "S:is";
      this->_help = "Returns the properties for the given finite field";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId(paramList.getString(1));
        paramList.verifyEnd(2);

        mpplas::MPPDataType* const mppdata(table.get(clientId, varId));

        const mpplas::GF* gf;
        const mpplas::GFx* gfx;

        if( gfx = dynamic_cast<mpplas::GFx*>(mppdata) ){
          gf = &(gfx->getGenerator());
        }
        else{
          gf = dynamic_cast<mpplas::GF*>(mppdata);
        }


        std::map<std::string, xmlrpc_c::value> structData;
        
        std::pair<std::string, xmlrpc_c::value> characteristic("characteristic", xmlrpc_c::value_string( gf->getCharacteristic().toString() ));
        std::pair<std::string, xmlrpc_c::value> degree("degree", xmlrpc_c::value_int( gf->getDegree() ));
        std::pair<std::string, xmlrpc_c::value> order("order", xmlrpc_c::value_string( gf->getOrder().toString() ));
        std::pair<std::string, xmlrpc_c::value> modulus("modulus", xmlrpc_c::value_string( gf->getMod().toHRString() ));
        std::pair<std::string, xmlrpc_c::value> isModulusPrimitive("isModulusPrimitive", xmlrpc_c::value_boolean( gf->isModPrimitive() ));

        structData.insert(characteristic);
        structData.insert(degree);
        structData.insert(order);
        structData.insert(modulus);
        structData.insert(isModulusPrimitive);

        *retvalP = xmlrpc_c::value_struct( structData );
      }
};

class GFxGetValue: public xmlrpc_c::method {
  public:
    
    GFxGetValue() {
      this->_signature = "s:is";
      this->_help = "Returns the integer equivalent for the given finite field element";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId(paramList.getString(1));
        paramList.verifyEnd(2);

        const mpplas::GFx* const op( (mpplas::GFx*)table.get(clientId, varId));

        *retvalP = xmlrpc_c::value_string( op->getIntegerValue().toString() );
      }
};

class GFxSetValue: public xmlrpc_c::method {
  public:
    
    GFxSetValue() {
      this->_signature = "s:iss";
      this->_help = "Sets the finite field element to the equivalent representation of the given integer";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));
        paramList.verifyEnd(3);

        mpplas::GFx* const op( (mpplas::GFx*)table.get(clientId, varId1));
        const mpplas::Z zOp( *((mpplas::Z*)table.get(clientId, varId2)));
        
        try{
          op->setIntegerValue(zOp);
        }
        catch(const std::exception& e){
          throw(girerr::error(e.what()));
        }


        *retvalP = xmlrpc_c::value_string( varId1 );
      }
};


/***********************************************
 ************** INTEGER MATRICES ****************
 ***********************************************/
class MZCreate: public xmlrpc_c::method {
  public:
    
    MZCreate() {
      this->_signature = "s:is";
      this->_help = "Creates a new integer matrix";
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
      this->_help = "Adds two integer matrices together";
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
class MZSubMethod : public xmlrpc_c::method {
  public:
    
    MZSubMethod() {
      this->_signature = "s:iss";
      this->_help = "Adds two integer matrices together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::MatrixZ op1( *((mpplas::MatrixZ*)table.get(clientId, varId1)));
        const mpplas::MatrixZ op2( *((mpplas::MatrixZ*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::MatrixZ(op1-op2), "MZ");

        *retvalP = xmlrpc_c::value_string( varId );
      }

};

class MZMulMethod : public xmlrpc_c::method {
  public:
    
    MZMulMethod() {
      this->_signature = "s:iss";
      this->_help = "Multiplies two integer matrices";
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
class MZDivMethod : public xmlrpc_c::method {
  public:
    
    MZDivMethod() {
      this->_signature = "s:iss";
      this->_help = "Multiplies two integer matrices";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::MatrixZ op1( *((mpplas::MatrixZ*)table.get(clientId, varId1)));
        const mpplas::MatrixZ op2( *((mpplas::MatrixZ*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::MatrixZ(op1/op2), "MZ");

        *retvalP = xmlrpc_c::value_string( varId );
      }

};




/***********************************************
 **************** REAL MATRICES ****************
 ***********************************************/
class MRCreate: public xmlrpc_c::method {
  public:
    
    MRCreate() {
      this->_signature = "s:is";
      this->_help = "Creates a new integer matrix";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        mpplas::MatrixR* const op( new mpplas::MatrixR(paramList.getString(1)));

        paramList.verifyEnd(2);

        const std::string varId(table.set(clientId, op, "MR"));

        *retvalP = xmlrpc_c::value_string(varId);
      }
};

class MRAddMethod : public xmlrpc_c::method {
  public:
    
    MRAddMethod() {
      this->_signature = "s:iss";
      this->_help = "Adds two integer matrices together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::MatrixR op1( *((mpplas::MatrixR*)table.get(clientId, varId1)));
        const mpplas::MatrixR op2( *((mpplas::MatrixR*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::MatrixR(op1+op2), "MR");

        *retvalP = xmlrpc_c::value_string( varId );
      }

};
class MRSubMethod : public xmlrpc_c::method {
  public:
    
    MRSubMethod() {
      this->_signature = "s:iss";
      this->_help = "Adds two integer matrices together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::MatrixR op1( *((mpplas::MatrixR*)table.get(clientId, varId1)));
        const mpplas::MatrixR op2( *((mpplas::MatrixR*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::MatrixR(op1-op2), "MR");

        *retvalP = xmlrpc_c::value_string( varId );
      }

};

class MRMulMethod : public xmlrpc_c::method {
  public:
    
    MRMulMethod() {
      this->_signature = "s:iss";
      this->_help = "Multiplies two integer matrices";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::MatrixR op1( *((mpplas::MatrixR*)table.get(clientId, varId1)));
        const mpplas::MatrixR op2( *((mpplas::MatrixR*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::MatrixR(op1*op2), "MR");

        *retvalP = xmlrpc_c::value_string( varId );
      }

};
class MRDivMethod : public xmlrpc_c::method {
  public:
    
    MRDivMethod() {
      this->_signature = "s:iss";
      this->_help = "Multiplies two integer matrices";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

        const int clientId(paramList.getInt(0));
        const std::string varId1(paramList.getString(1));
        const std::string varId2(paramList.getString(2));

        paramList.verifyEnd(3);

        const mpplas::MatrixR op1( *((mpplas::MatrixR*)table.get(clientId, varId1)));
        const mpplas::MatrixR op2( *((mpplas::MatrixR*)table.get(clientId, varId2)));

        const std::string varId = table.set(clientId, new mpplas::MatrixR(op1/op2), "MR");

        *retvalP = xmlrpc_c::value_string( varId );
      }

};



/***********************************************
 ************** RANDOM Z ***********************
 ***********************************************/
class RandomZMethod : public xmlrpc_c::method {
  public:
    
    RandomZMethod() {
      this->_signature = "s:ii";
      this->_help = "Returns a random interger of the specified number of bits"; 

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

class SecureRandomZMethod : public xmlrpc_c::method {
  public:
    
    SecureRandomZMethod() {
      this->_signature = "s:ii";
      this->_help = "Returns a truly random interger of the specified number of bits"; 

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
    mpplas::RandomSecure* rnd;
};


class RandomZLessThanMethod : public xmlrpc_c::method {
  public:
    
    RandomZLessThanMethod() {
      this->_signature = "s:is";
      this->_help = "Returns a random interger that is less than the given one"; 

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
      this->_help = "Returns a prime of at least the specified number of bits"; 

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

class GenStrongPrimeMethod : public xmlrpc_c::method {
  public:
    
    GenStrongPrimeMethod() {
      this->_signature = "s:ii";
      this->_help = "Returns a cryptographically prime of at least the specified number of bits"; 

      mpplas::MethodsFactory::getInstance()->getFunc(primes);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {
      const int clientId(paramList.getInt(0));
      const int bits = paramList.getInt(1);
      paramList.verifyEnd(2);

      try{
        mpplas::Z* const op( new mpplas::Z(primes->getPrimeStrong( bits ) ));
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
      this->_help = "Returns true if its argument is prime"; 

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
 ****************    LCM    ********************
 ***********************************************/
class LCMMethod : public xmlrpc_c::method {
  public:

    LCMMethod() {
      this->_signature = "s:iss";
      this->_help = "Returns the least common multiple of both integer arguments"; 

      mpplas::MethodsFactory::getInstance()->getFunc(lcm);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

      const int clientId(paramList.getInt(0));
      const std::string varId1(paramList.getString(1));
      const std::string varId2(paramList.getString(2));
      paramList.verifyEnd(3);

      const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
      const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));
 
      try{
        const std::string varId = table.set(clientId, new mpplas::Z(lcm->lcm(op1,op2)), "Z");
        *retvalP = xmlrpc_c::value_string( varId );
      }
      catch(const std::exception& e){
        throw(girerr::error(e.what()));
      }
    }

  private:
    mpplas::LCM* lcm;
};


/***********************************************
 ****************    GCD    ********************
 ***********************************************/
class GCDMethod : public xmlrpc_c::method {
  public:

    GCDMethod() {
      this->_signature = "s:iss";
      this->_help = "Returns a the greatest common divisor of both integer arguments"; 

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
    mpplas::GCD< mpplas::Z >* gcd;
};

class GCDExtMethod : public xmlrpc_c::method {
  public:

    GCDExtMethod() {
      this->_signature = "A:iss";
      this->_help = "Returns the Bézout coefficients corresponding to the given integer arguments"; 

      mpplas::MethodsFactory::getInstance()->getFunc(gcdext);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

      const int clientId(paramList.getInt(0));
      const std::string varId1(paramList.getString(1));
      const std::string varId2(paramList.getString(2));
      paramList.verifyEnd(3);

      const mpplas::Z op1( *((mpplas::Z*)table.get(clientId, varId1)));
      const mpplas::Z op2( *((mpplas::Z*)table.get(clientId, varId2)));
 
      try{
        mpplas::Z s,t; 
        const mpplas::Z d( gcdext->gcdext(op1, op2, &s, &t) );
        std::vector<xmlrpc_c::value> res;
        res.push_back(xmlrpc_c::value_string( d.toString() ));
        res.push_back(xmlrpc_c::value_string( s.toString() ));
        res.push_back(xmlrpc_c::value_string( t.toString() ));
        *retvalP  = xmlrpc_c::value_array(res);
      }
      catch(const std::exception& e){
        throw(girerr::error(e.what()));
      }
    }

  private:
    mpplas::GCDExt< mpplas::Z >* gcdext;
};


/***********************************************
 ****************    CRT    ********************
 ***********************************************/
class CRTMethod : public xmlrpc_c::method {
  public:

    CRTMethod() {
      this->_signature = "s:iAA";
      this->_help = "Returns the modular eq. system defined by the two arrays of integers given";

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
 ***********  INT. FACTORIZATION ***************
 ***********************************************/
class FactorizationMethod: public xmlrpc_c::method {
  public:

    FactorizationMethod() {
      this->_signature = "A:is";
      this->_help = "Returns an array with the integer factors of the given integer";

      mpplas::MethodsFactory::getInstance()->getFunc(factor);
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP) {

      const int clientId(paramList.getInt(0));
      const std::string varId(paramList.getString(1));
      paramList.verifyEnd(2);

      const mpplas::Z op( *((mpplas::Z*)table.get(clientId, varId)));

      try{
        const mpplas::MiVec<mpplas::Z> factors( factor->factoriza(op) );
        std::vector<xmlrpc_c::value> factorsArray;

        std::string varId;
        for(int i = 0; i < factors.size(); i++){
          factorsArray.push_back(xmlrpc_c::value_string( factors[i].toString() ));
        }
        *retvalP  = xmlrpc_c::value_array(factorsArray);
      }
      catch(const std::exception& e){
        throw(girerr::error(e.what()));
      }

    }

  private:
    mpplas::Factoriza* factor;
};




/***********************************************
 ****************    MISC   ********************
 ***********************************************/
class SysInfoMethod : public xmlrpc_c::method { 
  public:

    SysInfoMethod() {
      this->_signature = "S:i";
      this->_help = "Returns a map with some information about the host system";
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
      this->_help = "Marks the starting point in time for profiling clock";
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
      this->_help = "Returns the time elapsed since the profiling clock was set to run";
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
      this->_help = "Returns an array containing the profiling counters"
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
      this->_help = "Resets the profiling counters";
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


    myRegistry.addMethod("__requestClientId", new RequestClientId);
    myRegistry.addMethod("__discardClientId", new DiscardClientId);


    myRegistry.addMethod("_getData", new GetData);

    myRegistry.addMethod("__runGC", new RunGC);

    myRegistry.addMethod("_zCreate", new ZCreate);
    myRegistry.addMethod("_zAdd", new ZAddMethod);
    myRegistry.addMethod("_zSub", new ZSubMethod);
    myRegistry.addMethod("_zMul", new ZMulMethod);
    myRegistry.addMethod("_zDiv", new ZDivMethod);
    myRegistry.addMethod("_zMod", new ZModMethod);
    myRegistry.addMethod("_zPow", new ZPowMethod);
    myRegistry.addMethod("_zBitLength", new ZBitLength);
    myRegistry.addMethod("_zCompare", new ZCompare);

    myRegistry.addMethod("_znCreate", new Z_nCreate);
    myRegistry.addMethod("_znAdd", new Z_nAddMethod);
    myRegistry.addMethod("_znSub", new Z_nSubMethod);
    myRegistry.addMethod("_znMul", new Z_nMulMethod);
    myRegistry.addMethod("_znDiv", new Z_nDivMethod);
    myRegistry.addMethod("_znInv", new Z_nInvMethod);
    myRegistry.addMethod("_znPow", new Z_nPowMethod);


    myRegistry.addMethod("_rCreate", new RCreate);
    myRegistry.addMethod("_rAdd", new RAddMethod);
    myRegistry.addMethod("_rSub", new RSubMethod);
    myRegistry.addMethod("_rMul", new RMulMethod);
    myRegistry.addMethod("_rDiv", new RDivMethod);
    myRegistry.addMethod("_rPow", new RPowMethod);
    myRegistry.addMethod("_rBitLength", new RBitLength);
    myRegistry.addMethod("_rCompare", new RCompare);
    myRegistry.addMethod("_rInnerPrec", new RSetInternalPrecision);
    myRegistry.addMethod("_rOutputPrec", new RSetOutputPrecision);

    myRegistry.addMethod("_zFactorial", new ZFactorialMethod);

    myRegistry.addMethod("_mzCreate", new MZCreate);
    myRegistry.addMethod("_mzAdd", new MZAddMethod);
    myRegistry.addMethod("_mzSub", new MZSubMethod);
    myRegistry.addMethod("_mzMul", new MZMulMethod);
    myRegistry.addMethod("_mzDiv", new MZDivMethod);

    myRegistry.addMethod("_mrCreate", new MRCreate);
    myRegistry.addMethod("_mrAdd", new MRAddMethod);
    myRegistry.addMethod("_mrSub", new MRSubMethod);
    myRegistry.addMethod("_mrMul", new MRMulMethod);
    myRegistry.addMethod("_mrDiv", new MRDivMethod);

    myRegistry.addMethod("_getHRString", new GetHRStringMethod);

    myRegistry.addMethod("_gfCreate", new GFCreate);
    myRegistry.addMethod("_gfGetProperties", new GFGetProperties);
    myRegistry.addMethod("_gfxGetPBRString", new GFxGetPBRString);

    myRegistry.addMethod("_gfxCreate", new GFxCreate);
    myRegistry.addMethod("_gfxAdd", new GFxAddMethod);
    myRegistry.addMethod("_gfxSub", new GFxSubMethod);
    myRegistry.addMethod("_gfxMul", new GFxMulMethod);
    myRegistry.addMethod("_gfxDiv", new GFxDivMethod);
    myRegistry.addMethod("_gfxInverse", new GFxInvMethod);
    myRegistry.addMethod("_gfxGetValue", new GFxGetValue);
    myRegistry.addMethod("_gfxSetValue", new GFxSetValue);



    myRegistry.addMethod("modExp", new ModExpMethod);
    myRegistry.addMethod("modInverse", new ModInverseMethod);

    myRegistry.addMethod("getRandomZ", new RandomZMethod);
    myRegistry.addMethod("getSecureRandomZ", new SecureRandomZMethod);
    myRegistry.addMethod("getRandomZLessThan", new RandomZLessThanMethod);

    myRegistry.addMethod("getPrime", new GenPrimeMethod);
    myRegistry.addMethod("getStrongPrime", new GenStrongPrimeMethod);
    myRegistry.addMethod("isPrime", new PrimeTestMethod);

    myRegistry.addMethod("lcm", new  LCMMethod);

    myRegistry.addMethod("gcd", new  GCDMethod);
    myRegistry.addMethod("gcdext", new  GCDExtMethod);

    myRegistry.addMethod("crt", new CRTMethod);
    
    myRegistry.addMethod("factorize", new FactorizationMethod);

    myRegistry.addMethod("getSystemInfo", new SysInfoMethod);


    myRegistry.addMethod("startProfClock", new StartProfilingClockMethod);
    myRegistry.addMethod("stopProfClock", new StopProfilingClockMethod);
    myRegistry.addMethod("getProfRes", new GetProfilingResultsMethod);
    myRegistry.addMethod("resetProf", new ResetProfilingCountersMethod);



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
