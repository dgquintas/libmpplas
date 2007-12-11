#include "Range.h"

namespace mpplas{

  Range::Range(int start, int step, int stop)
    : _start(start), _stop(stop), _step(step), _curr(start)
  {}

  Range::Range(const Range& src)
    : _start(src._start), _stop(src._stop), _step(src._step), _curr(src._curr)
  {}

  Range& Range::operator=(const Range& src){
    _start = src._start;
    _stop  = src._stop;
    _step = src._step;
    _curr = src._curr;

    return *this;
  }

  int Range::getNext(){
    if( ! this->hasNext() ){
      std::ostringstream oss;
      oss << "No next element when calling \"Range::getNext\". ";
      GEN_TRACE_INFO_OSS(oss);
      throw Errors::NoSuchElement(oss.str());
    }

    _curr += _step;
    return _curr;
  }

  int Range::getPrevious(){
    if( ! this->hasNext() ){
      std::ostringstream oss;
      oss << "No previous element when calling \"Range::getPrevious\". ";
      GEN_TRACE_INFO_OSS(oss);
      throw Errors::NoSuchElement(oss.str());
    }

    _curr -= _step;
    return _curr;

  }

}
