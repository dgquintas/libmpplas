#ifndef __RANGE_H
#define __RANGE_H

#include "Errors.h"

namespace mpplas{

  class Range {
    public:
      Range(int start=0, int step=1, int stop=-1);
      Range(const Range& src);

      Range& operator=(const Range& src);

      inline int getStart() const;
      inline int getStop() const;
      inline int getStep() const;

      inline void reset();

      inline bool hasNext() const;
      int getNext();

      inline bool hasPrevious() const;
      int getPrevious();

    private:
      int _start;
      int _stop;
      int _step;

      int _curr;
  };


  //////////////////////////////////////////////////////////


  inline int Range::getStart() const{
    return _start;
  }
  inline int Range::getStop() const{
    return _stop;
  }
  inline int Range::getStep() const{
    return _step;
  }

  inline void Range::reset(){
    _curr = _start;
    return;
  }

  inline bool Range::hasNext() const{
    return _stop < 0 ? true : ((_curr+_step) <= _stop);
  }

  inline bool Range::hasPrevious() const{
    return (_curr-_step >= _start);
  }


}

#endif
