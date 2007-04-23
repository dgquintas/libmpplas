/* 
 * $Id$
 */

#ifndef __PERFIL_H
#define __PERFIL_H

#include "MiVec.h"
#include "Z.h"
#include "R.h"

namespace mpplas{

  /** Clase para el manejo del mecanismo de perfilado. */
  class Perfil
  {
    public:
      Perfil(void);

    /** Comenzar a tomar datos de perfilado */
      void iniciar(void);
    /** Finalizar la toma de datos de perfilado. */
      void finalizar(void);
    /** Acumular en los contadores internos de la clase.
     *
     * Los valores presentes de perfilado de la CPU Básica
     * (vCPUBasica) se acumulan en los contadores internos de la
     * clase, para evitar posibles desbordamientos de los contadores
     * de la CPU Básica si el intervalo de perfilado es muy grande. 
     * Los contadores de la CPU Básica se reinician.
     */
      void acumular(void);
      
      /** Leer segundos.
       *
       * @return Flotante de C++ representando el número de
       * segundos y centésimas de segundo representadas en los
       * acumuladores internos de la clase.
       */
      float leerSegundos(void);

      /** Leer número operaciones.
       *
       * @return Vector de enteros con el número de cada tipo de
       * operación efectuada en el intervalo de perfilado acumulado.
       *
       * */
      MiVec<Z> leerVectorOperaciones(void);
       /** Leer porcentaje de operaciones.
       *
       * @return Vector de enteros con el porcentaje de cada tipo de
       * operación efectuada en el intervalo de perfilado acumulado.
       *
       * */
      MiVec<R> leerVectorPorcentajes(void);

    private:
      MiVec<Z> n_operaciones_;
      clock_t ciclos_;
  };

}

#endif

  
