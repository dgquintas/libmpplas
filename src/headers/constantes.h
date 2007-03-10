/*
 * $Id$
 */


#ifndef __CONSTANTES_H_
#define __CONSTANTES_H_

#include <limits>
#include <stdint.h> //C99
#include <cstdlib>

#ifndef ARCHBITS
  #warning "Architecture bits not defined. Using 32"
  #define ARCHBITS 32
#endif

namespace numth{
  /** Tipo de dato básico. 
   *
   * Representa la base en la cual se trabaja en Z y será el tipo
   * utilizado en todo lugar que haga falta un entero positivo.
   */
#if ARCHBITS == 64
  typedef uint64_t Cifra;
#elif ARCHBITS == 32
  typedef uint32_t Cifra;
#else 
  #error Unsupported number of bits ARCHBITS
#endif

  /** Tipo de dato básico auxiliar con signo.
   *
   * Representa la versión con signo de Cifra, siendo utilizado en 
   * aquellos lugares en los que tenga sentido trabajar con enteros de
   * precisión simple negativos.
   */
#if ARCHBITS == 64
  typedef int64_t CifraSigno;
#elif ARCHBITS == 32
  typedef int32_t CifraSigno;
#else 
  #error Unsupported number of bits ARCHBITS
#endif

//  /** Las arquitecturas soportadas */
//  struct Arch {
//    enum {
//      x86,
//      x86Prof,
//      x86_64,
//      x86_64Prof,
//      generic,
//      ppc
//    };
//  };
//
//  /** Las operaciones de la vCPUBasica */
//  struct Operaciones {
//    enum {
//      Add, Addx, Sub, Subx, Addmul, Mul, Div, Shiftl, Shiftlr, Bfffo
//    };
//  };


  
  /** Espacio de nombres contenedor de las constantes utilizadas a lo
   * largo de la librería. */
  namespace Constantes{
    /** Número de operaciones soportadas por vCPUBasica */
    static const size_t NUM_OPERACIONES = 10;

    /** Log en base 2 de 10*/
    static const double LOG_2_10 = 3.3219280948873623;

    /** Log en base 10 de 2*/
    static const double LOG_10_2 = 0.3010299956639812;


    /** Bits en mantisa de un double */
    static const int BITS_EN_DOUBLE = std::numeric_limits<double>::digits;

    /** Bits en un unsigned long */
    static const int BITS_EN_ULONG = std::numeric_limits<unsigned long>::digits;

    /** Bits en un Cifra */
    static const int BITS_EN_CIFRA = std::numeric_limits<Cifra>::digits;

    /** Bits in half a Cifra */
    static const int BITS_IN_HALFCIFRA = std::numeric_limits<Cifra>::digits >> 1;

    /** Bits en un CifraSigno */
    static const int BITS_EN_CIFRASIGNO = std::numeric_limits<CifraSigno>::digits;

    /** Bytes en un Cifra */
    static const int BYTES_EN_CIFRA = BITS_EN_CIFRA >> 3;


    /** Maximo valor de una Cifra */
    static const Cifra CIFRA_MAX = std::numeric_limits<Cifra>::max();

    /** Maximum value for half a Cifra */
    static const Cifra CIFRAHALF_MAX = (((Cifra)1) << BITS_IN_HALFCIFRA) - 1;

    /** TODO */
   static const Cifra MASK_CIFRALOW = CIFRAHALF_MAX;

    /** TODO  */
   static const Cifra MASK_CIFRAHIGH = ~MASK_CIFRALOW;
 
    /** Maximo valor de una CifraSigno */
    static const CifraSigno CIFRASIGNO_MAX = std::numeric_limits<CifraSigno>::max();

#ifdef ULONG_MAX
#undef ULONG_MAX
#endif
    /** Maximo valor de un unsigned long */
    static const unsigned long ULONG_MAX = std::numeric_limits<unsigned long>::max();

#ifdef LONG_MAX
#undef LONG_MAX
#endif
    /** Maximo valor de un long */
    static const long LONG_MAX = std::numeric_limits<long>::max();

#ifdef SIZE_T_MAX
#undef SIZE_T_MAX
#endif
    /* Maximo valor de un size_t */
    static const size_t SIZE_T_MAX = std::numeric_limits<size_t>::max();

    /** Mayor 'n' tal que \f$10^n \leq 2^{base}\f$.
     * 
    * Es decir, el número de cifras decimales que "caben" en un 'Cifra'
    * para \f$ \lfloor\log_{10} 2^{32}\rfloor = 9 \f$ */
    static const int MAX_EXP10_CIFRA = std::numeric_limits<Cifra>::digits10;
 
    /** Mayor 'n' tal que \f$10^n \leq 2^{base}\f$.
     * 
    * Es decir, el número de cifras decimales que "caben" en un 'CifraSigno'
    * para \f$ \lfloor\log_{10} 2^{31}\rfloor = 9 \f$ */
    static const int MAX_EXP10_CIFRASIGNO = std::numeric_limits<CifraSigno>::digits10;

    /** Mayor 'n' tal que \f$10^n \leq 2^{base}\f$.
     * 
    * Es decir, el número de cifras decimales que "caben" en un 'Cifra'
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

    /** Número de cifras en base \f$2^{BITS_EN_CIFRA}\f$ a partir del cual se usa
    * la multiplicacion de Karatsuba */
    static const size_t UMBRAL_KARATSUBA = 64; 

    /** Número de cifras en base \f$2^{BITS_EN_CIFRA}\f$ a partir del cual se usa
    * karatsuba para el calculo del cuadrado. */
    static const size_t UMBRAL_CUAD_KARATSUBA = 72;

    /** Número de bytes tras los cuales el generador de semillas (el no
    * seguro) se renueva con datos random reales. */
    static const size_t UMBRAL_SEMILLA = 10; 

    /** Iteraciones que se considerarán en la factorización trial */
    static const size_t COTA_FACTORIZACION_TRIAL = 303; // pi(2000) 

    /** Iteraciones que se considerarán en la factorización por el metodo 
    * \f$\rho\f$ de Pollard */
    static const size_t COTA_FACTORIZACION_RHO = 50000; 

    /** Iteraciones que se considerarán en la factorización por el metodo 
    * SQUFOR */
    static const size_t COTA_FACTORIZACION_SQUFOF = 500; 

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

      /** Tabla de los primos hasta 2000. */
    static const Cifra TABLA_PRIMOS_2000[] = {
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
    }; // 303 elementos = Pi(2000) 

  }
}
#endif
