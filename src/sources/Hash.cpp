/* 
 * $Id$
 */

#include "Hash.h"
#include <cassert>
#include <sstream>
#include <cstring> //para memset

namespace mpplas{


  MD5::MD5(void)
    : finalizado_(false)
  {
    inicializar();

    return;
  }
  
  Z MD5::obtenerEnteroResumen(void)
  {
    if( !finalizado_)
      finalizar();

    //para que todo sea DE VERDAD independiente de todo, no nos fiamos
    //ni de que Digit vaya a ser siempre de 32 bits... echamos mano de
    //las rutinas de conversion desde cadenas.
    std::ostringstream cadStream;
    cadStream << resumen_[0] << resumen_[1] << resumen_[2] << resumen_[3];
    std::string cadena = cadStream.str();
    Z temp(cadena.c_str());

    return temp;
  }

  MiVec<uint32_t> MD5::obtenerVectorResumen(void)
  {
    if( !finalizado_)
      finalizar();

    MiVec<uint32_t> temp(4);

    temp[0] = resumen_[0]; 
    temp[1] = resumen_[1]; 
    temp[2] = resumen_[2]; 
    temp[3] = resumen_[3]; 

    return temp;
  }


  void MD5::inicializar(void)
  {
    tam_[0] = 0;
    tam_[1] = 0;

    //magia potagia
    resumen_[0] = 0x67452301;
    resumen_[1] = 0xefcdab89;
    resumen_[2] = 0x98badcfe;
    resumen_[3] = 0x10325476;

    return;
  }

  //esta función actualiza el resumen 
  void MD5::actualizar(const MiVec<uint8_t>& datos)
  {
    int i, ii;
    int longDatos = datos.size();

    //calcular el numero de bytes mod 64
    int mdi = ((tam_[0] >> 3) & 0x3F);

    //acualizar el numero de bits
    if( (tam_[0] + (longDatos << 3)) < tam_[0]) //overflow
      tam_[1]++;
    tam_[0] += ((uint32_t)longDatos << 3); //se cuentan bits, NO bytes (* 2^3)
    tam_[1] += ((uint32_t)longDatos >> 29); // (8k)/2^{32} = k/2^{29}

    int pos = 0;
    while (longDatos--) {
      //añadir los nuevos caracteres al buffer
      buffer8_[mdi++] = datos[pos++];

      //realizar transformación si es necesario
      if (mdi == 64) {
        for (i = 0, ii = 0; i < 16; i++, ii += 4)
          buffer32_[i] = (((uint32_t)buffer8_[ii+3]) << 24) |
            (((uint32_t)buffer8_[ii+2]) << 16) |
            (((uint32_t)buffer8_[ii+1]) << 8) |
            ((uint32_t)buffer8_[ii]);
        procesar();
        mdi = 0;
      }
    }
  }

  //esta rutina concluye el calculo del hash y deja almacenado el
  //resumen en resumen[]
  void MD5::finalizar(void)
  {
    int i, ii;
    
    //guardar el numero de bits
    buffer32_[14] = tam_[0];
    buffer32_[15] = tam_[1];

    //calcular el numero de bytes mod 64
    const int mdi = ((tam_[0] >> 3) & 0x3F);

    //desplazar hasta 56 mod 64
    const int padLen = (mdi < 56) ? (56 - mdi) : (120 - mdi);
    MiVec<uint8_t> PADDING(padLen, 0x00);
    PADDING[0] = 0x80;
    actualizar(PADDING);

    //añadir la longitud en bits y transformar
    for (i = 0, ii = 0; i < 14; i++, ii += 4)
      buffer32_[i] = (((uint32_t)buffer8_[ii+3]) << 24) |
        (((uint32_t)buffer8_[ii+2]) << 16) |
        (((uint32_t)buffer8_[ii+1]) << 8) |
        ((uint32_t)buffer8_[ii]);
    procesar();

    for(i = 0; i < 4; i++)
      resumen_[i] = 
        ( (resumen_[i] & 0xff000000) >> 24) | 
        ( (resumen_[i] & 0x00ff0000) >> 8)  |  
        ( (resumen_[i] & 0x0000ff00) << 8)  | 
        ( (resumen_[i] & 0x000000ff) << 24);

 
    // limpiar datos sensibles 
    memset(buffer8_, 0, sizeof(buffer8_));
    memset(buffer32_, 0, sizeof(buffer32_));
    memset(tam_, 0, sizeof(tam_));

    finalizado_ = true;
    
    return;
  }

  void MD5::procesar ()
  {
    uint32_t a,b,c,d;
    a = resumen_[0]; b = resumen_[1]; c = resumen_[2]; d = resumen_[3];

    /* Round 1 */
    FF ( a, b, c, d, buffer32_[ 0], (uint32_t)7, (uint32_t)3614090360UL); /* 1 */
    FF ( d, a, b, c, buffer32_[ 1], (uint32_t)12, (uint32_t)3905402710UL); /* 2 */
    FF ( c, d, a, b, buffer32_[ 2], (uint32_t)17, (uint32_t) 606105819UL); /* 3 */
    FF ( b, c, d, a, buffer32_[ 3], (uint32_t)22, (uint32_t)3250441966UL); /* 4 */
    FF ( a, b, c, d, buffer32_[ 4], (uint32_t)7, (uint32_t)4118548399UL); /* 5 */
    FF ( d, a, b, c, buffer32_[ 5], (uint32_t)12, (uint32_t)1200080426UL); /* 6 */
    FF ( c, d, a, b, buffer32_[ 6], (uint32_t)17, (uint32_t)2821735955UL); /* 7 */
    FF ( b, c, d, a, buffer32_[ 7], (uint32_t)22, (uint32_t)4249261313UL); /* 8 */
    FF ( a, b, c, d, buffer32_[ 8], (uint32_t)7, (uint32_t)1770035416UL); /* 9 */
    FF ( d, a, b, c, buffer32_[ 9], (uint32_t)12, (uint32_t)2336552879UL); /* 10 */
    FF ( c, d, a, b, buffer32_[10], (uint32_t)17, (uint32_t)4294925233UL); /* 11 */
    FF ( b, c, d, a, buffer32_[11], (uint32_t)22, (uint32_t)2304563134UL); /* 12 */
    FF ( a, b, c, d, buffer32_[12], (uint32_t)7, (uint32_t)1804603682UL); /* 13 */
    FF ( d, a, b, c, buffer32_[13], (uint32_t)12, (uint32_t)4254626195UL); /* 14 */
    FF ( c, d, a, b, buffer32_[14], (uint32_t)17, (uint32_t)2792965006UL); /* 15 */
    FF ( b, c, d, a, buffer32_[15], (uint32_t)22, (uint32_t)1236535329UL); /* 16 */

    /* Round 2 */
    GG ( a, b, c, d, buffer32_[ 1], (uint32_t)5, (uint32_t)4129170786UL); /* 17 */
    GG ( d, a, b, c, buffer32_[ 6], (uint32_t)9, (uint32_t)3225465664UL); /* 18 */
    GG ( c, d, a, b, buffer32_[11], (uint32_t)14, (uint32_t) 643717713UL); /* 19 */
    GG ( b, c, d, a, buffer32_[ 0], (uint32_t)20, (uint32_t)3921069994UL); /* 20 */
    GG ( a, b, c, d, buffer32_[ 5], (uint32_t)5, (uint32_t)3593408605UL); /* 21 */
    GG ( d, a, b, c, buffer32_[10], (uint32_t)9, (uint32_t)  38016083UL); /* 22 */
    GG ( c, d, a, b, buffer32_[15], (uint32_t)14, (uint32_t)3634488961UL); /* 23 */
    GG ( b, c, d, a, buffer32_[ 4], (uint32_t)20, (uint32_t)3889429448UL); /* 24 */
    GG ( a, b, c, d, buffer32_[ 9], (uint32_t)5, (uint32_t) 568446438UL); /* 25 */
    GG ( d, a, b, c, buffer32_[14], (uint32_t)9, (uint32_t)3275163606UL); /* 26 */
    GG ( c, d, a, b, buffer32_[ 3], (uint32_t)14, (uint32_t)4107603335UL); /* 27 */
    GG ( b, c, d, a, buffer32_[ 8], (uint32_t)20, (uint32_t)1163531501UL); /* 28 */
    GG ( a, b, c, d, buffer32_[13], (uint32_t)5, (uint32_t)2850285829UL); /* 29 */
    GG ( d, a, b, c, buffer32_[ 2], (uint32_t)9, (uint32_t)4243563512UL); /* 30 */
    GG ( c, d, a, b, buffer32_[ 7], (uint32_t)14, (uint32_t)1735328473UL); /* 31 */
    GG ( b, c, d, a, buffer32_[12], (uint32_t)20, (uint32_t)2368359562UL); /* 32 */

    /* Round 3 */
    HH ( a, b, c, d, buffer32_[ 5], (uint32_t)4, (uint32_t)4294588738UL); /* 33 */
    HH ( d, a, b, c, buffer32_[ 8], (uint32_t)11, (uint32_t)2272392833UL); /* 34 */
    HH ( c, d, a, b, buffer32_[11], (uint32_t)16, (uint32_t)1839030562UL); /* 35 */
    HH ( b, c, d, a, buffer32_[14], (uint32_t)23, (uint32_t)4259657740UL); /* 36 */
    HH ( a, b, c, d, buffer32_[ 1], (uint32_t)4, (uint32_t)2763975236UL); /* 37 */
    HH ( d, a, b, c, buffer32_[ 4], (uint32_t)11, (uint32_t)1272893353UL); /* 38 */
    HH ( c, d, a, b, buffer32_[ 7], (uint32_t)16, (uint32_t)4139469664UL); /* 39 */
    HH ( b, c, d, a, buffer32_[10], (uint32_t)23, (uint32_t)3200236656UL); /* 40 */
    HH ( a, b, c, d, buffer32_[13], (uint32_t)4, (uint32_t) 681279174UL); /* 41 */
    HH ( d, a, b, c, buffer32_[ 0], (uint32_t)11, (uint32_t)3936430074UL); /* 42 */
    HH ( c, d, a, b, buffer32_[ 3], (uint32_t)16, (uint32_t)3572445317UL); /* 43 */
    HH ( b, c, d, a, buffer32_[ 6], (uint32_t)23, (uint32_t)  76029189UL); /* 44 */
    HH ( a, b, c, d, buffer32_[ 9], (uint32_t)4, (uint32_t)3654602809UL); /* 45 */
    HH ( d, a, b, c, buffer32_[12], (uint32_t)11, (uint32_t)3873151461UL); /* 46 */
    HH ( c, d, a, b, buffer32_[15], (uint32_t)16, (uint32_t) 530742520UL); /* 47 */
    HH ( b, c, d, a, buffer32_[ 2], (uint32_t)23, (uint32_t)3299628645UL); /* 48 */

    /* Round 4 */
#define S41 6
#define S42 10
#define S43 15
#define S44 21
    II ( a, b, c, d, buffer32_[ 0], (uint32_t)6, (uint32_t)4096336452UL); /* 49 */
    II ( d, a, b, c, buffer32_[ 7], (uint32_t)10, (uint32_t)1126891415UL); /* 50 */
    II ( c, d, a, b, buffer32_[14], (uint32_t)15, (uint32_t)2878612391UL); /* 51 */
    II ( b, c, d, a, buffer32_[ 5], (uint32_t)21, (uint32_t)4237533241UL); /* 52 */
    II ( a, b, c, d, buffer32_[12], (uint32_t)6, (uint32_t)1700485571UL); /* 53 */
    II ( d, a, b, c, buffer32_[ 3], (uint32_t)10, (uint32_t)2399980690UL); /* 54 */
    II ( c, d, a, b, buffer32_[10], (uint32_t)15, (uint32_t)4293915773UL); /* 55 */
    II ( b, c, d, a, buffer32_[ 1], (uint32_t)21, (uint32_t)2240044497UL); /* 56 */
    II ( a, b, c, d, buffer32_[ 8], (uint32_t)6, (uint32_t)1873313359UL); /* 57 */
    II ( d, a, b, c, buffer32_[15], (uint32_t)10, (uint32_t)4264355552UL); /* 58 */
    II ( c, d, a, b, buffer32_[ 6], (uint32_t)15, (uint32_t)2734768916UL); /* 59 */
    II ( b, c, d, a, buffer32_[13], (uint32_t)21, (uint32_t)1309151649UL); /* 60 */
    II ( a, b, c, d, buffer32_[ 4], (uint32_t)6, (uint32_t)4149444226UL); /* 61 */
    II ( d, a, b, c, buffer32_[11], (uint32_t)10, (uint32_t)3174756917UL); /* 62 */
    II ( c, d, a, b, buffer32_[ 2], (uint32_t)15, (uint32_t) 718787259UL); /* 63 */
    II ( b, c, d, a, buffer32_[ 9], (uint32_t)21, (uint32_t)3951481745UL); /* 64 */

    resumen_[0] += a;
    resumen_[1] += b;
    resumen_[2] += c;
    resumen_[3] += d;
  }



}
