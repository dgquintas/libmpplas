/*
 * $Id$
 */


#ifndef __CONSTANTS_H_
#define __CONSTANTS_H_

#include <limits>
#include <cstdlib>

#include "BasicTypedefs.h"
#include "Utils.h"

namespace mpplas{
  
  /** Constants used throughout the library */
  namespace Constants{
    
#ifdef ARCH_x86
    static const char* const ARCH_STRING = "x86";
  #define ARCH_DEFINED
#endif

#ifdef ARCH_x86_64
    static const char* const ARCH_STRING = "x86_64";
  #define ARCH_DEFINED
#endif

#ifdef ARCH_generic
    static const char* const ARCH_STRING = "generic";
  #define ARCH_DEFINED
#endif

#ifdef ARCH_ppc
    static const char* const ARCH_STRING = "ppc";
  #define ARCH_DEFINED
#endif

#ifndef ARCH_DEFINED
  #warning "ARCH not supported or not defined. Using x86"
    static const char* const ARCH_STRING = "x86";
  #define ARCH_DEFINED
  #define ARCHBITS 32
#endif


    static const short ARCH_BITS = ARCHBITS;

    
    /** Número de operaciones soportadas por vCPUBasica */
    static const int NUM_OPERACIONES = 10;

    /** Log2(10) */
    static const double LOG_2_10 = 3.3219280948873623;

    /** Log10(2)*/
    static const double LOG_10_2 = 0.3010299956639812;


    /** Bits en mantisa de un double */
    static const int BITS_EN_DOUBLE = std::numeric_limits<double>::digits;

    /** Bits en un unsigned long */
    static const int BITS_EN_ULONG = std::numeric_limits<unsigned long>::digits;

    /** Bits en un Digit */
    static const int BITS_EN_CIFRA = std::numeric_limits<Digit>::digits;

    /** Bits in half a Digit */
    static const int BITS_IN_HALFCIFRA = std::numeric_limits<Digit>::digits >> 1;

    /** Bits en un SignedDigit */
    static const int BITS_EN_CIFRASIGNO = std::numeric_limits<SignedDigit>::digits;

    /** Bytes en un Digit */
    static const int BYTES_EN_CIFRA = BITS_EN_CIFRA >> 3;


    /** Maximo valor de una Digit */
    static const Digit CIFRA_MAX = std::numeric_limits<Digit>::max();

    /** Maximum value for half a Digit */
    static const Digit CIFRAHALF_MAX = (((Digit)1) << BITS_IN_HALFCIFRA) - 1;

    /** TODO */
   static const Digit MASK_CIFRALOW = CIFRAHALF_MAX;

    /** TODO  */
   static const Digit MASK_CIFRAHIGH = ~MASK_CIFRALOW;
 
    /** Maximo valor de una SignedDigit */
    static const SignedDigit CIFRASIGNO_MAX = std::numeric_limits<SignedDigit>::max();

    /** Maximo valor de un unsigned long */
    static const unsigned long SYSTEM_ULONG_MAX = std::numeric_limits<unsigned long>::max();

    /** Maximo valor de un long */
    static const long SYSTEM_LONG_INT_MAX = std::numeric_limits<long>::max();

    /* Maximo valor de un size_t */
    static const size_t SYSTEM_SIZE_T_MAX = std::numeric_limits<size_t>::max();

    /** Mayor 'n' tal que \f$10^n \leq 2^{base}\f$.
     * 
    * Es decir, el número de cifras decimales que "caben" en un 'Digit'
    * para \f$ \lfloor\log_{10} 2^{32}\rfloor = 9 \f$ */
    static const int MAX_EXP10_CIFRA = std::numeric_limits<Digit>::digits10;


    static const Digit MAX_BASE10_POWER_DIGIT = Utils::CTPow<10, MAX_EXP10_CIFRA>::result;

 
    /** Mayor 'n' tal que \f$10^n \leq 2^{base}\f$.
     * 
    * Es decir, el número de cifras decimales que "caben" en un 'SignedDigit'
    * para \f$ \lfloor\log_{10} 2^{31}\rfloor = 9 \f$ */
    static const int MAX_EXP10_CIFRASIGNO = std::numeric_limits<SignedDigit>::digits10;

    /** Mayor 'n' tal que \f$10^n \leq 2^{base}\f$.
     * 
    * Es decir, el número de cifras decimales que "caben" en un 'Digit'
    * para \f$ \lfloor\log_{10} 2^{32}\rfloor = 9 \f$ */
    static const int MAX_EXP10_ULONG = std::numeric_limits<unsigned long>::digits10;


    /** Máximo numero de digitos en base 10 representables por un double.
     *
     * Máximo numero de digitos en base 10 representables por un double.
    * (se añade un uno ya que hay cierto "margen" para una cifra más;
    * Esto es, el \f$\log_{10}(bits_mantisa)\f$ normalmente tiene cierta parte
    * fraccionaria. */
    static const int MAX_EXP10_DOUBLE = std::numeric_limits<double>::digits10;

#if ARCHBITS == 64
    static const int LOG_2_BITS_EN_CIFRA = 6;
#elif ARCHBITS == 32
    static const int LOG_2_BITS_EN_CIFRA = 5;
#endif

    static const size_t DIGIT_MOD_MASK = (1<<Constants::LOG_2_BITS_EN_CIFRA)-1;

    /** Número de cifras en base \f$2^{BITS_EN_CIFRA}\f$ a partir del cual se usa
    * la multiplicacion de Karatsuba */
    static const int UMBRAL_KARATSUBA = 160; 

    /** Número de cifras en base \f$2^{BITS_EN_CIFRA}\f$ a partir del cual se usa
    * karatsuba para el calculo del cuadrado. */
    static const int UMBRAL_CUAD_KARATSUBA = 72;

    /** Número de bytes tras los cuales el generador de semillas (el no
    * seguro) se renueva con datos random reales. */
    static const int UMBRAL_SEMILLA = 10; 

    /** Iteraciones que se considerarán en la factorización trial */
    static const int COTA_FACTORIZACION_TRIAL = 303; // pi(2000) 

    /** Iteraciones que se considerarán en la factorización por el metodo 
    * \f$\rho\f$ de Pollard */
    static const int COTA_FACTORIZACION_RHO = 50000; 

    /** Iteraciones que se considerarán en la factorización por el metodo 
    * SQUFOR */
    static const int COTA_FACTORIZACION_SQUFOF = 500; 

    /** Tabla para el uso por la función de detección de cuadrado de
    * enteros */
    static const bool Q11[11] = {true, true, false, true, true, true, false, false, 
      false, true, false};
     /** Tabla para el uso por la función de detección de cuadrado de
    * enteros */
   static const bool Q63[63] = {true, true, false, false, true, false, false, true, 
      false, true, false, false, false, false, false, false, true, false, true,
      false, false, false, true, false, false,  true, false, false, true, false,
      false, false, false, false,  false, false, true, true, false, false, false,
      false, false,  true, false, false, true, false, false, true, false, false, 
      false, false, false, false, false, false, true, false, false, false, false};
      /** Tabla para el uso por la función de detección de cuadrado de
    * enteros */
  static const bool Q64[64] = {true, true, false, false, true, false, false, false, false,
      true, false, false, false, false, false, false, true, true, false, false, false,
      false, false, false, false, true, false, false, false, false, false, false, false,
      true, false, false, true, false, false, false, false, true, false, false, false,
      false, false, false, false, true, false, false, false, false, false, false, false,
      true, false, false, false, false, false, false};
       /** Tabla para el uso por la función de detección de cuadrado de
    * enteros */
 static const bool Q65[65] = {true, true, false, false, true, false, false, false, false,
      true, true, false, false, false, true, false, true, false, false, false, false,
      false, false, false, false, true, true, false, false, true, true, false, false,
      false, false, true, true, false, false, true, true, false, false, false, false,
      false, false, false, false, true, false, true, false, false, false, true, true,
      false, false, false, false, true, false, false, true};

      /** Primes up to 2000. */
    static const Digit TABLA_PRIMOS_2000[] = {
      2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 
      73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
      157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
      239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
      331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419,
      421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
      509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607,
      613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 
      709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811,
      821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
      919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019,
      1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097,
      1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201,
      1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 
      1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409,
      1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487,
      1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579,
      1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667,
      1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777,
      1783, 1787, 1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877,
      1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 
      1997, 1999
    }; // 303 elements = Pi(2000) 

  }
}
#endif
