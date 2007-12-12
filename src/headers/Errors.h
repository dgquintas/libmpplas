/*
 * $Id$ 
 */

#ifndef __ERRORS_H
#define __ERRORS_H

#include <string>
#include <stdexcept>
#include <exception>
#include <sstream>

#include "Dimensions.h"

#define GEN_TRACE_INFO_OSS(oss) \
  oss << '(' << __FILE__ << ':' << __LINE__ << ')'

namespace mpplas{
  /** Library errors namespace. */
  namespace Errors{
    /** Base class of the library's exceptions hierarchy. */
    class Exception: public std::exception {
      public:
        /** Textual (human readable) description of exception. 
         *
         * This follows std::exception conventions. 
         *
         * @return a textual (human readable) description of the exception. */
        virtual const char* what(void) const throw() {
          return _msg.c_str();
        }
        virtual ~Exception() throw() {}
      protected:
        Exception(){};
        std::string _msg;
    };

    /** Invalid arguments errors
     *
     * For instance, division by zero, non-invertible element, etc.
     * 
     * */
    class InvalidArgument: public Exception {
      public:
        InvalidArgument( std::string msg = "<empty>" ){
          _msg += "Invalid Argument error: ";
          _msg += msg;
        }
        virtual ~InvalidArgument() throw() {}
    };

    /** Sintactic errors.
     *
     * Such as invalid parsing of textual description of a user-given number.  */
    class Sintactic : public Exception {
      public:
        Sintactic( std::string msg = "<empty>" ){
          _msg += "Sintactic error: ";
          _msg += msg;
        }
        virtual ~Sintactic() throw() {}
    };

    /** Internal errors.
     *
     * Such as invalid pointers, situations which in theory 
     * should never happen, etc. */
    class Internal : public Exception  {
      public:
      Internal( std::string msg = "<empty>" ) {
        _msg += "Internal error: ";
        _msg += msg;
      }

      virtual ~Internal() throw() {}
    };


    /** Division by zero attempt. */
    class DivisionByZero : public InvalidArgument {
      public:
        DivisionByZero(const std::string details = "")
          : InvalidArgument("Division by zero; ") {
            _msg += details;
          }
    };

    /** Negative result in unsigned substraction. */
    class NegativeSubstraction : public InvalidArgument  {
      public:
        NegativeSubstraction(const std::string details = "")
          : InvalidArgument("Subtrahend is greater than the minuend at unsigned subtraction; "){
            _msg += details;
          }
    };

    /** Inversion of non-invertible element attempt. */
    class NonInvertibleElement : public InvalidArgument  {
      public:
        NonInvertibleElement(const std::string details = "")
          : InvalidArgument("Tried to invert an non-invertible element; "){
            _msg += details;
          }
    };

    /** Negative exponentiation on a non-invertible element attempt */
    class NegativeExponent : public InvalidArgument  {
      public:
        NegativeExponent(const std::string details = "")
          : InvalidArgument("Negative exponent on a non-invertible element; ") {
            _msg += details;
          }
    };

    /** Even Jacobi Symbol second argument. */
    class EvenInJacobiSymbol : public InvalidArgument {
      public:
        EvenInJacobiSymbol(const std::string details = "")
          : InvalidArgument("Even element as second argument of a Jacoby Symbol; "){
            _msg += details;
          }
    };

    /** Even modulus on a Montgomery reduction */
    class MontgomeryEvenMod : public InvalidArgument  {
      public:
        MontgomeryEvenMod(const std::string details = "") 
          : InvalidArgument("Even modulus on Montgomery reduction/exponentiation; "){
            _msg += details;
          }
    };

    /** Log(0) calculation attempt */
    class LogZero: public InvalidArgument  {
      public:
        LogZero(const std::string details = "") 
          : InvalidArgument("Calculation of the logarithm of zero; "){
            _msg += details;
          }
    };

    /** Prime number required */
    class PrimeRequired : public InvalidArgument{
      public:
        PrimeRequired( std::string details = "" )
          : InvalidArgument("Prime number required") {
            _msg += details;
          }
    };


    /** Dimensions of the operands are not conformant */
    class NonConformantDimensions: public InvalidArgument  {
      public:
        NonConformantDimensions(const Dimensions& dimsLeft, const Dimensions& dimsRight, std::string str = "")
          : InvalidArgument("Non conformant dimensions; ") {
          std::string tmpStr = dimsLeft.toString() + " and " + dimsRight.toString() + " " + str;
          _msg += tmpStr;
        }
    };
 
    /** Square matrix required */
    class SquareMatrixRequired: public InvalidArgument  {
      public:
        SquareMatrixRequired( const std::string details = "" )
          : InvalidArgument("Square matrix required; "){
            _msg += details;
          }
    };


    /** Invalid range */
    class InvalidRange : public InvalidArgument {
      public:
        InvalidRange(const std::string details = "")
        : InvalidArgument("Invalid range; ") {
          _msg += details;
        }
    };

    /** Field type required */
    class FieldRequired: public InvalidArgument {
      public:
        FieldRequired(const std::string details = "")
        : InvalidArgument("Field required; ") {
          _msg += details;
        }
    };

    /** Inconsistent finite field generator for operators */ 
    class InconsistentGFGenerator: public InvalidArgument {
      public:
        InconsistentGFGenerator(const std::string details = "")
        : InvalidArgument("GF elements do not belong to the same field; ") {
          _msg += details;
        }
    };

    /** Inconsistent modulus for operators */ 
    class InconsistentModulus: public InvalidArgument {
      public:
        InconsistentModulus(const std::string details = "")
        : InvalidArgument("Operands do not share the same modulus; ") {
          _msg += details;
        }
    };


    /** Irreducible polynomial expected */
    class IrreduciblePolyExpected: public InvalidArgument {
      public:
        IrreduciblePolyExpected(const std::string details = "")
        : InvalidArgument("Expected an irreducible polynomial; ") {
          _msg += details;
        }
    };

    /** No such element found in a sequence */
    class NoSuchElement: public InvalidArgument {
      public:
        NoSuchElement(const std::string details = "")
        : InvalidArgument("No such element in the sequence; ") {
          _msg += details;
        }
    };



    ////////////////////////////////////////////
    // SINTACTIC ERRORS
    ////////////////////////////////////////////

    /** Invalid symbol while parsing */
    class InvalidSymbol: public Sintactic
    {
      public:
        InvalidSymbol(const std::string str = "")
          : Sintactic("Invalid symbol; ") {
          _msg += str;
        }
    };

    ////////////////////////////////////////////
    // INTERNAL ERRORS
    ////////////////////////////////////////////

    /** Invalid sign */
    class InvalidSign : public Internal
    {
      public: 
        InvalidSign(const std::string details = "")
          : Internal("Incorrect sign; "){
            _msg += details;
          }
    };

    /** Number too big to be used in a given context */
    class TooBig: public Internal  {
      public:
        TooBig(const std::string details = "")
          : Internal("Number too big; "){
            _msg += details;
          }
    };

    /** Current architecture does not support profiling */
    class ArchNoProfiling : public Internal  {
      public:
        ArchNoProfiling(const std::string details = "")
          : Internal("The current architecture does not support profiling; "){
            _msg += details;
          }
    };


    /** Error while profiling */
    class ProfilingError : public Internal  {
      public: 
        ProfilingError(const std::string details = "")
          : Internal("Profiling error; "){
            _msg += details;
          }
    };


    /** Error while accessing the entropy source */
    class InvalidEntropySource : public Internal
    {
      public:
        InvalidEntropySource(const std::string details = "")
          : Internal("Error while accessing the entropy source; "){
            _msg += details;
          }
    };


    /** Null pointer dereference attempt */
    class NullPointer : public Internal {
      public:
        NullPointer(const std::string details = "")
          : Internal("Null pointer; "){
            _msg += details;
          }
    };

    /** @a R exponent overflow*/
    class RealsExpOverflow : public Internal {
      public: 
        RealsExpOverflow(const std::string details = "")
          : Internal("The exponent for floating-point exp. overflowed; "){
            _msg += details;
          }
    };

    /** Feature not implemented */
    class NotImplemented : public Internal
    {
      public:
        NotImplemented(const std::string details = "")
          : Internal("Feature not implemented; "){
            _msg += details;
          }
    };


  }//namespace Errors
}//namespace 

   
#endif
