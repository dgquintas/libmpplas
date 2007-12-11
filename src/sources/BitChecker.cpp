#include "BitChecker.h"


namespace mpplas{
  namespace Utils{
    BitChecker::BitChecker(const Z& integer, const bool rightToLeft)
      : _integer(integer), _bitLength(integer.getBitLength()), _rightToLeft(rightToLeft)
    {
        _bitPos = rightToLeft ? 0 : _integer.getBitLength()-1;
        _init(_bitPos, _rightToLeft);
    }

    void BitChecker::_init(const int bitPos, const bool rightToLeft){
      _inDigitPosMask = 1;
      if( rightToLeft ){
        _digitPos = 0;
      }
      else{
        _digitPos = bitPos >> Constants::LOG_2_BITS_EN_CIFRA;

        // bitPos % BITS_IN_DIGIT
        _inDigitPosMask <<= ( bitPos & Constants::DIGIT_MOD_MASK );
      }
    }


    int BitChecker::getPosition() const {
      return _bitPos-1;
    }

    void BitChecker::setPosition(int bitPos){
      // 0 <= bitPos <= _bitLength
      if( bitPos < 0 || bitPos > _bitLength ){
        std::ostringstream oss;
        oss << "Invalid bit position " << bitPos << " for a " << _bitLength << " sequence. ";
        GEN_TRACE_INFO_OSS(oss);
        throw Errors::InvalidArgument(oss.str());
      }
      _bitPos = bitPos;
      _init(_bitPos, _rightToLeft);
      return;
    }

    bool BitChecker::hasNext() const {
      return _bitPos < _bitLength;
    }

    bool BitChecker::checkNext(){
      if( !hasNext() ){
        std::ostringstream oss;
        oss << "No next element when calling \"BitChecker::checkNext\". ";
        GEN_TRACE_INFO_OSS(oss);
        throw Errors::NoSuchElement(oss.str());
      }

      static const Digit BASEMASK = (Digit)1;
      static const Digit IN_DIGIT_POS_MAX = 
        ((Digit)1) << (Constants::BITS_EN_CIFRA -1);

      bool result;

      if( ( _integer[_digitPos] & _inDigitPosMask ) ){ 
        result = true;
      }
      else{
        result = false;
      }

      if( _inDigitPosMask == IN_DIGIT_POS_MAX ){
        _digitPos++;
        _inDigitPosMask = BASEMASK;
      } 
      else{
        _inDigitPosMask <<= 1;
      }


      _bitPos++;
      return result;
    }
  
    bool BitChecker::hasPrevious() const {
      return _bitPos >= 0;
    }

    bool BitChecker::checkPrevious(){
      if( !hasPrevious() ){
        std::ostringstream oss;
        oss << "No previous element when calling \"BitChecker::checkPrevious\". ";
        GEN_TRACE_INFO_OSS(oss);
        throw Errors::NoSuchElement(oss.str());
      }
      static const Digit BASEMASK = 
        ((Digit)1) << (Constants::BITS_EN_CIFRA -1);

      if( !_inDigitPosMask ){
        _digitPos--;
        _inDigitPosMask = BASEMASK;
      }
      bool result;

      if( ( _integer[_digitPos] & _inDigitPosMask ) ){ 
        result = true;
      }
      else{
        result = false;
      }

      _bitPos--;
      _inDigitPosMask >>= 1;
      return result;
    } 
  
  } // namespace Utils
} //namespace mpplas
