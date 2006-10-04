/*
 * $Id$ 
 */

#ifndef __ERR_H
#define __ERR_H

#include <iostream>
#include <string>
#include <stdexcept>

namespace numth{
  /** Espacio de nombres contenedor del mecanismo de errores. */
  namespace Errores{
    // Tipos b�sicos
    /** Clase base de todas las excepciones (errores) que comprende
     * la librer�a. */
    class Excepcion
    {
      public:
        /** Informaci�n sobre el error.
         * 
         * @return Un vector de caracteres con un mensaje explicativo
         * del error en cuesti�n.
         */
        virtual const char* info(void) const = 0;
        virtual ~Excepcion(){};
    };
      
    /** Clase base para errores de tipo aritm�tico.
     *
     * Ejemplo cl�sico: la divisi�n por cero.
     * 
     * */
    class Aritmetico : public Excepcion
    {
      public:
      virtual const char* info(void) const 
      {
        return "Error aritm�tico indeterminado";
      }
    };

    /** Clase base para errores de tipo sint�ctico.
     *
     * Se utiliza por ejemplo en la lectura de n�meros con el operador
     * de entrada ">>".
     * 
     */
    class Sintactico : public Excepcion
    {
      public:
      virtual const char* info(void) const 
      {
        return "Error sint�ctico indeterminado";
      }
    };

    /** Clase base para errores internos.
     *
     * Por ejemplo al detectar un puntero inv�lido, intento de acceso
     * a una posici�n de memoria no reservada, etc.
     * */
    class Interno : public Excepcion
    {
      public:
        virtual const char* info(void) const
        {
          return "Error interno indeterminado";
        }
    };


    // Tipos derivados
    /** Error de divisi�n por cero */
    class DivisionPorCero : public Aritmetico
    {
      public:
      virtual const char* info(void) const 
      { 
        return "Se ha producido una divisi�n por cero";
      }
    };

    /** Resultado negativo en resta sin signo */
    class RestaNegativa : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
        return "Sustraendo mayor que minuendo en resta sin signo a nivel MP";
      }
    };

    /** Elemento no invertible en un grupo finito */
    class ElementoNoInvertible : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
         return "Intento de inversi�n inv�lido";
      }
    };

    /** Intento de potenciaci�n de un elemento no inverbiel en un no-cuerpo */
    class ExponenteNegativo : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
         return "Exponente negativo en elemento no invertible";
      }
    };

    /** Segundo argumento de un s�mbolo de Jacobi es par */
    class ParEnSimboloJacobi : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
         return "Segundo argumento del Simbolo de Jacobi par";
      }
    };

    /** Modulo par en la exponenciaci�n por Montgomery */
    class ModuloParEnMontgomery : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
         return "Modulo par en exponenciaci�n de Montgomery";
      }
    };

    /** Logaritmo de cero */
    class LogaritmoDeCero : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
         return "Intento de c�lculo del logaritmo de cero";
      }
    };




    /** Detectado s�mbolo inv�lido en la lectura de un n�mero */
    class SimboloInvalido : public Sintactico
    {
      char simbolo_;
      
      public:
        SimboloInvalido(char c) : simbolo_(c){}
        virtual const char* info(void) const 
        { 
          std::string msg("Simbolo inv�lido: ");
          msg += simbolo_;
          return msg.c_str();
        }
    };

    /** N�mero sin longitud alguna (al menos tendria que ser 1, para
     * el cero)*/
    class NumeroVacio : public Interno
    {
      virtual const char* info(void) const
      {
         return "Polinomio representante del n�mero de longitud 0";
      }
    };

    /** Signo inv�lido */
    class SignoInvalido : public Interno
    {
      virtual const char* info(void) const
      {
         return "Signo incorrecto";
      }

    };

    /** Uso de un n�mero demasiado grande para el contexto */
    class DemasiadoGrande : public Interno
    {
      virtual const char* info(void) const
      {
         return "N�mero demasiado grande";
      }
    };

    /** Intento de uso de perfilado en arquitectura que no lo soporta
     * */
    class ArchNoProfiling : public Interno
    {
      virtual const char* info(void) const
      {
         return "Arquitectura actual no soporta operaciones de perfilado";
      }
    };


    /** Error en el proceso de perfilado */
    class ErrorPerfilado : public Interno
    {
      virtual const char* info(void) const
      {
         return "Error de perfilado";
      }
    };


    /** Error al acceder a la fuente de entrop�a */
    class FuenteEntropiaInvalida : public Interno
    {
      virtual const char* info(void) const
      {
         return "Error al acceder a la fuente de entrop�a";
      }
    };

    
    /** Intento de desreferenciar un puntero nulo */
    class PunteroNulo : public Interno
    {
      virtual const char* info(void) const
      {
         return "Se ha proporcionado un puntero nulo donde no se admite";
      }
    };

    /** Exponente de reales desbordado */
    class OverflowExpReales : public Interno
    {
      virtual const char* info(void) const
      {
         return "El exponente de la representaci�n de reales se ha desbordado";
      }
    };
 
    /** Funci�n no implementada */
    class NoImplementado : public Interno
    {
      virtual const char* info(void) const
      {
         return "Funci�n a�n no implementada";
      }
    };

  
  }//namespace Errores
}//namespace numth

   
#endif
