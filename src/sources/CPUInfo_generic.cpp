#include <cstring>

#include "CPUInfo_generic.h"
#include "Utils.h"

namespace mpplas{

  //static singleton initialization
  template<>
    std::auto_ptr< CPUInfo_generic > 
    SingletonMixIn< CPUInfo_generic >::_singletonInstance(SingletonMixIn< CPUInfo_generic >::_singletonInstance);


  CPUInfo_generic::CPUInfo_generic()
    : SingletonMixIn< CPUInfo_generic >()
  {
    _l1Size = _l2Size = _l3Size = 0;
    _getCacheSizes();
    _getSIMDInfo();
    _getModelName();

  }


  //////////////////////////////////////////////////////////////

  void CPUInfo_generic::_getCacheSizes(){
    //TODO
  }
  
  void CPUInfo_generic::_getSIMDInfo(){
    _simdCap.push_back("generic");
  }

  void CPUInfo_generic::_getModelName(){
    _modelName = "Generic CPU";
  }



} //namespace
