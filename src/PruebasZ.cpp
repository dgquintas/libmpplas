/* 
 * $Id$
 */

#include <cassert>
#include "mp.h"

namespace numth
{

      // constructores
      Z() /**< constructor por defecto */;
      Z( const Z& otro); /**< Constructor de copia.
                           @param otro Entero a copiar. */

      
      static Z convertir(const Cifra numSimple);

      static Z convertir(const long numSimple);


      static Z convertir(const char* cadena) throw(Errores::Sintactico);


      static Z convertir(const double numFlotante);

      Z& operator=(const Z& origen);


      Z& operator=(const Cifra origenSimple);

     Z& operator+=(const Z& sumandoDerecha);

      Z& operator-=(const Z& sustraendo);

      Z& operator*=(const Z& factorDer);

      Z& operator/=(const Z& divisor);
 
      Z& operator%=(const Z& divisor);


      Z& cuadrado(void);

      Z& operator+=(const long); 
      Z& operator-=(const long); 
      Z& operator*=(const long); 
      Z& operator/=(const long); 
      Z& operator%=(const long); 


      Z& operator+=(const unsigned long); 
      Z& operator-=(const unsigned long); 
      Z& operator*=(const unsigned long); 
      Z& operator/=(const unsigned long); 
      Z& operator%=(const unsigned long); 

      Z& operator^=(const Z& exp); 
      Z& operator^=(unsigned long exp); 
      Z& operator^=(long exp); 

      // OPERADORES DE COMPARACION
      bool operator>(const Z& der) const;
      bool operator<(const Z& der) const;
      bool operator==(const Z& der) const;
      bool operator!=(const Z& der) const;
      bool operator>=(const Z& der) const;
      bool operator<=(const Z& der) const;

      bool operator>(const long der) const;
      bool operator<(const long der) const;
      bool operator==(const long der) const;
      bool operator!=(const long der) const;
      bool operator>=(const long der) const;
      bool operator<=(const long der) const;

      bool operator>(const unsigned long der) const;
      bool operator<(const unsigned long der) const;
      bool operator==(const unsigned long der) const;
      bool operator!=(const unsigned long der) const;
      bool operator>=(const unsigned long der) const;
      bool operator<=(const unsigned long der) const;


      //OPERADORES DE DESPLAZAMIENTO (funciones miembro)
      Z& operator>>=(const unsigned long);
      Z& operator<<=(const unsigned long);

      //OPERADORES "REDUCIDOS"
      Z& operator++(void); //prefijo
      Z& operator++(int); //sufijo
      Z& operator--(void); //prefijo
      Z& operator--(int); //sufijo

      //conteo de bits
      unsigned long numBits(void) const;
      //redondeo
      long redondear(unsigned long exceso) const;

      //funciones utiles
      void hacerCero(void);
      void hacerUno(void);
      inline void hacerPositivo(void) { signo_ = 1; } 
      inline void hacerNegativo(void) { signo_ = -1; }
      inline void cambiarSigno(void) { signo_ *= -1; }
      bool esCero(void) const;  
      bool esUno(void) const;  
      inline bool esPositivo(void) const { return signo_ > 0; }
      inline bool esNegativo(void) const { return signo_ < 0; }
      void limpiarCeros(void);
      inline bool esPar(void) const { return (!(coefPoliB_[0] & 0x1)); }
      inline bool esImpar(void) const { return ((coefPoliB_[0] & 0x1)); }



      //funcciones de informacion
      inline
        unsigned long longitud(void) const  {   return coefPoliB_.size();  }

      inline
        Cifra operator[](unsigned long i) const { return coefPoliB_[i]; }

      inline 
        long signo(void) const { return signo_; }


      //relativas a precision de salida
      inline 
        static unsigned long precisionSalida(void) { return precisionSalida_; }

      inline 
        static void precisionSalida(unsigned long nueva) 
        { precisionSalida_ = nueva; return;}


    protected:
      Z( const long ); 
      Z( const Cifra ); 
      Z( const double ); 
      Z( const char* ); 


      /** Operador de salida del número */
      friend std::ostream& operator<<(std::ostream&, Z);
      /** Operador obtencion del número */
      friend std::istream& operator>>(std::istream&, Z&) throw (Errores::Sintactico);

      friend void divMod(const Z& dividendo, const Z& divisor, Z& cociente, Z& resto) 
        throw (Errores::DivisionPorCero);
      friend void divMod(const Z& dividendo, const long divisor, Z& cociente, Z& resto) 
        throw (Errores::DivisionPorCero);
      friend void divMod(const Z& dividendo, const Cifra divisor, Z& cociente, Z& resto) 
        throw (Errores::DivisionPorCero);



  bool operator<(const long, const Z&);
  bool operator>(const long, const Z&);
  bool operator<=(const long, const Z&);
  bool operator>=(const long, const Z&);
  bool operator==(const long, const Z&);
  bool operator!=(const long, const Z&);

  bool operator<(const unsigned long, const Z&);
  bool operator>(const unsigned long, const Z&);
  bool operator<=(const unsigned long, const Z&);
  bool operator>=(const unsigned long, const Z&);
  bool operator==(const unsigned long, const Z&);
  bool operator!=(const unsigned long, const Z&);

  Z operator+(Z, const Z&);
  Z operator-(Z, const Z&);
  Z operator*(Z, const Z&);
  Z operator/(Z, const Z&);
  Z operator%(Z, const Z&);

  Z operator+(const long, Z);
  Z operator-(const long, Z);
  Z operator*(const long, Z);
  Z operator/(const long, const Z&);
  Z operator%(const long, const Z&);

  Z operator+(Z, const long);
  Z operator-(Z, const long);
  Z operator*(Z, const long);
  Z operator/(Z, const long);
  Z operator%(Z, const long);

  Z operator+(const unsigned long, Z);
  Z operator-(const unsigned long, Z);
  Z operator*(const unsigned long, Z);
  Z operator/(const unsigned long, const Z&);
  Z operator%(const unsigned long, const Z&);

  Z operator+(Z, const unsigned long);
  Z operator-(Z, const unsigned long);
  Z operator*(Z, const unsigned long);
  Z operator/(Z, const unsigned long);
  Z operator%(Z, const unsigned long);

  Z operator-(Z); 
  Z operator^(Z base, const Z& exp); 
  Z operator^(Z base, const unsigned long exp); 
  Z operator^(Z base, const long exp); 

  Z cuadrado(Z x);


  //OPERADORES DE DESPLAZAMIENTO 
  Z operator>>(Z, const unsigned long);
  Z operator<<(Z, const unsigned long);

