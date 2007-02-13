/*
 * $Id$ 
 */

#ifndef __ERR_H
#define __ERR_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>

//FIXME
#define _(STRING) STRING

namespace numth{
  /** Espacio de nombres contenedor del mecanismo de errores. */
  namespace Errores{
    // Tipos báicos
    /** Clase base de todas las excepciones (errores) que comprende
     * la librería. */
    class NumthExcepcion: public std::exception 
    {};
      
    /** Clase base para errores de tipo aritméico.
     *
     * Ejemplo clásico: la división por cero.
     * 
     * */
    class Aritmetico : public NumthException
    {
      public:
      virtual const char* what(void) const 
      {
        return _("Undefined arithmetic error");
      }
    };

    /** Clase base para errores de tipo sintáctico.
     *
     * Se utiliza por ejemplo en la lectura de números con el operador
     * de entrada ">>".
     * 
     */
    class Sintactico : public NumthException
    {
      public:
      virtual const char* what(void) const 
      {
        return _("Undefined sintactic error");
      }
    };

    /** Clase base para errores internos.
     *
     * Por ejemplo al detectar un puntero inválido, intento de acceso
     * a una posición de memoria no reservada, etc.
     * */
    class Interno : public NumthException
    {
      public:
        virtual const char* what(void) const
        {
          return _("Undefined internal error");
        }
    };


    ////////////////////////////////////////////////////////////////////////////////////

    // Tipos derivados
    /** Error de división por cero */
    class DivisionPorCero : public Aritmetico
    {
      public:
      virtual const char* what(void) const 
      { 
        return _("Division by zero");
      }
    };

    /** Resultado negativo en resta sin signo */
    class RestaNegativa : public Aritmetico
    {
      public:
      virtual const char* what(void) const
      {
        return _("Subtrahend is greater than the minuend at unsigned subtraction");
      }
    };

    /** Elemento no invertible en un grupo finito */
    class ElementoNoInvertible : public Aritmetico
    {
      public:
      virtual const char* what(void) const
      {
         return "Intento de inversión inválido";
      }
    };

    /** Intento de potenciación de un elemento no inverbiel en un no-cuerpo */
    class ExponenteNegativo : public Aritmetico
    {
      public:
      virtual const char* what(void) const
      {
         return "Exponente negativo en elemento no invertible";
      }
    };

    /** Segundo argumento de un símbolo de Jacobi es par */
    class ParEnSimboloJacobi : public Aritmetico
    {
      public:
      virtual const char* what(void) const
      {
         return "Segundo argumento del Simbolo de Jacobi par";
      }
    };

    /** Modulo par en la exponenciación por Montgomery */
    class ModuloParEnMontgomery : public Aritmetico
    {
      public:
      virtual const char* what(void) const
      {
         return "Modulo par en exponenciación de Montgomery";
      }
    };

    /** Logaritmo de cero */
    class LogaritmoDeCero : public Aritmetico
    {
      public:
      virtual const char* what(void) const
      {
         return "Intento de cálculo del logaritmo de cero";
      }
    };




    /** Detectado símbolo inválido en la lectura de un nmero */
    class SimboloInvalido : public Sintactico
    {
      char simbolo_;
      
      public:
        SimboloInvalido(char c) : simbolo_(c){}
        virtual const char* what(void) const 
        { 
          std::string msg("Simbolo inválido: ");
          msg += simbolo_;
          return msg.c_str();
        }
    };

    /** Nmero sin longitud alguna (al menos tendria que ser 1, para
     * el cero)*/
    class NumeroVacio : public Interno
    {
      virtual const char* what(void) const
      {
         return "Polinomio representante del nmero de longitud 0";
      }
    };

    /** Signo inválido */
    class SignoInvalido : public Interno
    {
      virtual const char* what(void) const
      {
         return "Signo incorrecto";
      }

    };

    /** Uso de un nmero demasiado grande para el contexto */
    class DemasiadoGrande : public Interno
    {
      virtual const char* what(void) const
      {
         return "Nmero demasiado grande";
      }
    };

    /** Intento de uso de perfilado en arquitectura que no lo soporta
     * */
    class ArchNoProfiling : public Interno
    {
      virtual const char* what(void) const
      {
         return "Arquitectura actual no soporta operaciones de perfilado";
      }
    };


    /** Error en el proceso de perfilado */
    class ErrorPerfilado : public Interno
    {
      virtual const char* what(void) const
      {
         return "Error de perfilado";
      }
    };


    /** Error al acceder a la fuente de entropía */
    class FuenteEntropiaInvalida : public Interno
    {
      virtual const char* what(void) const
      {
         return "Error al acceder a la fuente de entropía";
      }
    };

    
    /** Intento de desreferenciar un puntero nulo */
    class PunteroNulo : public Interno
    {
      virtual const char* what(void) const
      {
         return "Se ha proporcionado un puntero nulo donde no se admite";
      }
    };

    /** Exponente de reales desbordado */
    class OverflowExpReales : public Interno
    {
      virtual const char* what(void) const
      {
         return "El exponente de la representación de reales se ha desbordado";
      }
    };
 
    /** Función no implementada */
    class NoImplementado : public Interno
    {
      virtual const char* what(void) const
      {
         return "Función an no implementada";
      }
    };

  
  }//namespace Errores
}//namespace numth

   
#endif
