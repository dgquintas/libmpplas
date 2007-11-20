/*
 * $Id$ 
 */

#ifndef __ERRORS_H
#define __ERRORS_H

#include <string>
#include <stdexcept>
#include <exception>

#include "AlgebraUtils.h"


namespace mpplas{
  /** Espacio de nombres contenedor del mecanismo de errores. */
  namespace Errors{
    // Tipos báicos
    /** Clase base de todas las excepciones (errores) que comprende
     * la librería. */
    class Exception: public std::exception {
      public:
        virtual const char* what(void) const throw() {
          return _msg.c_str();
        }
        virtual ~Exception() throw() {}
      protected:
        Exception(){};
        std::string _msg;
    };

    /** Base class for invalid arguments errors
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

    /** Clase base para errores de tipo sintáctico.
     *
     * Se utiliza por ejemplo en la lectura de números con el operador
     * de entrada ">>".
     * 
     */
    class Sintactic : public Exception {
      public:
        Sintactic( std::string msg = "<empty>" ){
          _msg += "Sintactic error: ";
          _msg += msg;
        }
        virtual ~Sintactic() throw() {}
    };

    /** Clase base para errores internos.
     *
     * Por ejemplo al detectar un puntero inválido, intento de acceso
     * a una posición de memoria no reservada, etc.
     * */
    class Interno : public Exception  {
      public:
      Interno( std::string msg = "<empty>" ) {
        _msg += "Internal error: ";
        _msg += msg;
      }

      virtual ~Interno() throw() {}
    };


    ////////////////////////////////////////////
    // ARGUMENT ERRORS
    ////////////////////////////////////////////


    // Tipos derivados
    /** Error de división por cero */
    class DivisionPorCero : public InvalidArgument {
      public:
        DivisionPorCero(const std::string details = "")
          : InvalidArgument("Division by zero; ") {
            _msg += details;
          }
    };

    /** Resultado negativo en resta sin signo */
    class RestaNegativa : public InvalidArgument  {
      public:
        RestaNegativa(const std::string details = "")
          : InvalidArgument("Subtrahend is greater than the minuend at unsigned subtraction; "){
            _msg += details;
          }
    };

    /** Elemento no invertible en un grupo finito */
    class NonInvertibleElement : public InvalidArgument  {
      public:
        NonInvertibleElement(const std::string details = "")
          : InvalidArgument("Tried to invert an non-invertible element; "){
            _msg += details;
          }
    };

    /** Intento de potenciación de un elemento no invertible en un no-cuerpo */
    class ExponenteNegativo : public InvalidArgument  {
      public:
        ExponenteNegativo(const std::string details = "")
          : InvalidArgument("Negative exponent on a non-invertible element; ") {
            _msg += details;
          }
    };

    /** Segundo argumento de un símbolo de Jacobi es par */
    class ParEnSimboloJacobi : public InvalidArgument {
      public:
        ParEnSimboloJacobi(const std::string details = "")
          : InvalidArgument("Even element as second argument of a Jacoby Symbol; "){
            _msg += details;
          }
    };

    /** Even modulus on a Montgomery reduction */
    class ModuloParEnMontgomery : public InvalidArgument  {
      public:
        ModuloParEnMontgomery(const std::string details = "") 
          : InvalidArgument("Even modulus on Montgomery reduction/exponentiation; "){
            _msg += details;
          }
    };

    /** Logaritmo de cero */
    class LogaritmoDeCero : public InvalidArgument  {
      public:
        LogaritmoDeCero(const std::string details = "") 
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


    class NonConformantDimensions: public InvalidArgument  {
      public:
        NonConformantDimensions(const Dimensions& dimsLeft, const Dimensions& dimsRight, std::string str = "")
          : InvalidArgument("Non conformant dimensions; ") {
          std::string tmpStr = dimsLeft.toString() + " and " + dimsRight.toString() + " " + str;
          _msg += tmpStr;
        }
    };
 
    class SquareMatrixRequired: public InvalidArgument  {
      public:
        SquareMatrixRequired( const std::string details = "" )
          : InvalidArgument("Square matrix required; "){
            _msg += details;
          }
    };


    class InvalidRange : public InvalidArgument {
      public:
        InvalidRange(const std::string details = "")
        : InvalidArgument("Invalid range; ") {
          _msg += details;
        }
    };

    class FieldRequired: public InvalidArgument {
      public:
        FieldRequired(const std::string details = "")
        : InvalidArgument("Field required; ") {
          _msg += details;
        }
    };

    class InconsistentGFGenerator: public InvalidArgument {
      public:
        InconsistentGFGenerator(const std::string details = "")
        : InvalidArgument("GF elements do not belong to the same field; ") {
          _msg += details;
        }
    };
    class IrreduciblePolyExpected: public InvalidArgument {
      public:
        IrreduciblePolyExpected(const std::string details = "")
        : InvalidArgument("Expected an irreducible polynomial; ") {
          _msg += details;
        }
    };




    ////////////////////////////////////////////
    // SINTACTIC ERRORS
    ////////////////////////////////////////////

    /** Detectado símbolo inválido en la lectura de un nmero */
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

    /** Signo inválido */
    class SignoInvalido : public Interno
    {
      public: 
        SignoInvalido(const std::string details = "")
          : Interno("Incorrect sign; "){
            _msg += details;
          }
    };

    /** Number too big to be used in a given context */
    class TooBig: public Interno  {
      public:
        TooBig(const std::string details = "")
          : Interno("Number too big; "){
            _msg += details;
          }
    };

    /** Intento de uso de perfilado en arquitectura que no lo soporta
     * */
    class ArchNoProfiling : public Interno  {
      public:
        ArchNoProfiling(const std::string details = "")
          : Interno("The current architecture does not support profiling; "){
            _msg += details;
          }
    };


    /** Error en el proceso de perfilado */
    class ErrorPerfilado : public Interno  {
      public: 
        ErrorPerfilado(const std::string details = "")
          : Interno("Profiling error; "){
            _msg += details;
          }
    };


    /** Error al acceder a la fuente de entropía */
    class FuenteEntropiaInvalida : public Interno
    {
      public:
        FuenteEntropiaInvalida(const std::string details = "")
          : Interno("Error while accessing the entropy source; "){
            _msg += details;
          }
    };


    /** Intento de desreferenciar un puntero nulo */
    class PunteroNulo : public Interno {
      public:
        PunteroNulo(const std::string details = "")
          : Interno("Null pointer; "){
            _msg += details;
          }
    };

    /** Exponente de reales desbordado */
    class OverflowExpReales : public Interno {
      public: 
        OverflowExpReales(const std::string details = "")
          : Interno("The exponent for floating-point exp. overflowed; "){
            _msg += details;
          }
    };

    /** Función no implementada */
    class NoImplementado : public Interno
    {
      public:
        NoImplementado(const std::string details = "")
          : Interno("Feature not implemented; "){
            _msg += details;
          }
    };


  }//namespace Errors
}//namespace 

   
#endif
