#include "Perfil.h"
#include "nucleo.h"

namespace numth{

  Perfil::Perfil(void)
    : n_operaciones_(Constantes::NUM_OPERACIONES)
  {}

  void Perfil::iniciar(void)
  {
    vCPUBasica<Arch::ARCH> cpu_;
    for(size_t i=0; i < Constantes::NUM_OPERACIONES; i++)
      n_operaciones_[i].hacerCero();
    
    cpu_.reiniciarContadores();
    cpu_.inicioProf();

    return;
  }
  void Perfil::finalizar(void)
  {
    vCPUBasica<Arch::ARCH> cpu_;
    cpu_.finProf();
    ResultadosProf resultTemp;
    resultTemp = cpu_.obtenerPerfil();
    for(size_t i=0; i < Constantes::NUM_OPERACIONES; i++)
      n_operaciones_[i] += resultTemp.n_operaciones[i];

    ciclos_ = resultTemp.ciclos;

    return;
  }
  void Perfil::acumular(void)
  {
    vCPUBasica<Arch::ARCH> cpu_;
    ResultadosProf resultTemp;
    resultTemp = cpu_.obtenerPerfil();

    for(size_t i=0; i < Constantes::NUM_OPERACIONES; i++)
      //FIXME: esto usa el += de Z, con lo cual las medidas
      //se distorsionan
      n_operaciones_[i] += resultTemp.n_operaciones[i];
  
    cpu_.reiniciarContadores();
    return;
  }
    

  float Perfil::leerSegundos(void)
  {
    return ((float)ciclos_ / (float)CLOCKS_PER_SEC );
  }

  MiVec<Z> Perfil::leerVectorOperaciones(void)
  {
    return n_operaciones_;
  }

  MiVec<R> Perfil::leerVectorPorcentajes(void)
  {
    Z sum; sum.hacerCero();
    MiVec<R> porcentajes(Constantes::NUM_OPERACIONES);
    
    for(size_t i=0; i < Constantes::NUM_OPERACIONES; i++){
      porcentajes[i].hacerCero();
      sum += n_operaciones_[i];
    }

    R sumReal = R::convertir(sum);
    R cien = R::convertir((Cifra)100);
    for(size_t i=0; i < Constantes::NUM_OPERACIONES; i++)
      porcentajes[i] = (R::convertir(n_operaciones_[i]) / sumReal) * cien;

    return porcentajes;
  }
      
}   
      

