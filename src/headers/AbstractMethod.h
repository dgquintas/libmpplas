#ifndef __ABSTRACTMETHOD_H
#define __ABSTRACTMETHOD_H

namespace mpplas{
  class AbstractMethod{
    public:
      virtual ~AbstractMethod(){}// = 0; //force the class to be abstract
  };
}

//AbstractMethod::~AbstractMethod(){}

#endif
