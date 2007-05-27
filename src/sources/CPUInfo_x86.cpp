#include <cstring>

#include "CPUInfo_x86.h"

namespace mpplas{

  //static singleton initialization
  template<>
    const std::auto_ptr< CPUInfo_x86 > 
    SingletonMixIn< CPUInfo_x86 >::singletonInstance( new CPUInfo_x86() );


  CPUInfo_x86::CPUInfo_x86()
    : SingletonMixIn< CPUInfo_x86 >()
  {
    _l1Size = _l2Size = _l3Size = 0;
    _getCacheSizes();
    _getSIMDInfo();

  }


  int CPUInfo_x86::getCacheL1Size() const {
    return _l1Size;
  }
  int CPUInfo_x86::getCacheL2Size() const {
    return _l2Size;
  }
  int CPUInfo_x86::getCacheL3Size() const {
    return _l3Size;
  }

  std::string CPUInfo_x86::getModelName() const {
    return std::string("");
  }


  std::string CPUInfo_x86::getArchName() const {
    return std::string("x86");
  }

  std::vector<std::string> CPUInfo_x86::getSIMDCapabilities() const {
    return _simdCap;
  }

  int CPUInfo_x86::getDigitBitWidth() const {
    return 32;
  }
  

  //////////////////////////////////////////////////////////////

  inline void CPUInfo_x86::_invokeCPUID(uint32_t eax){
    asm volatile(
        "pushl %%ebx      \n\t" /* save %ebx */
        "cpuid            \n\t"
        "movl %%ebx, %1   \n\t" /* save what cpuid just put in %ebx */
        "popl %%ebx       \n\t" /* restore the old %ebx */
        : "=a"(*_regs), "=r"(_regs[1]), "=c"(_regs[2]), "=d"(_regs[3])
        : "a"(eax)
        : "cc");
  }
  

  void CPUInfo_x86::_getSIMDInfo(){
    _invokeCPUID(1);

      if( _regs[EDX] & (1L << 23) ){ _simdCap.push_back("MMX") ; }
      if( _regs[EDX] & (1L << 25) ){ _simdCap.push_back("SSE") ; }
      if( _regs[EDX] & (1L << 26) ){ _simdCap.push_back("SSE2") ; }
      if( _regs[ECX] & (1L) )      { _simdCap.push_back("SSE3") ; }
      if( _regs[ECX] & (1L << 9) ) { _simdCap.push_back("SSSE3") ; }
  }

  void CPUInfo_x86::_getCacheSizes(){
    _invokeCPUID(2);
    const int reqdTimes = (_regs[EAX] & 0xff); //how many times cpuid must be invoked 
    if( reqdTimes > 1 ){
      //TODO
    }
    for( int i = 0; i < 4 ; i++){
      if( !(_regs[i] & 0x80000000) ){ // registers with its 31st bit set mustn't be considered 
        while( _regs[i] ){
          switch( _regs[i] & 0xff ){ // byte indexed table
            case 0xa: 
              _l1Size = 8 * 1024;
              break;
            case 0xc: 
              _l1Size = 16 * 1024;
              break;
            case 0x22:
              _l3Size = 512 * 1024;
              break;
            case 0x23:
              _l3Size = 1 * 1024 * 1024;
              break;
            case 0x25:
              _l3Size = 2 * 1024 * 1024;
              break;
            case 0x29:
              _l3Size = 4 * 1024 * 1024;
              break;
            case 0x2c:
              _l1Size = 32 * 1024;
              break;
            case 0x41:
              _l2Size = 128 * 1024;
              break;
            case 0x42:
              _l2Size = 256 * 1024;
              break;
            case 0x43:
              _l2Size = 512 * 1024;
              break;
            case 0x44:
              _l2Size = 1 * 1024 * 1024;
              break;
            case 0x45:
              _l2Size = 2 * 1024 * 1024;
              break;
            case 0x46:
              _l3Size = 4 * 1024 * 1024;
              break;
            case 0x47:
              _l3Size = 8 * 1024 * 1024;
              break;
            case 0x49:
              _l2Size = 4 * 1024 * 1024;
              break;
            case 0x60:
              _l1Size = 16 * 1024;
              break;
            case 0x66:
              _l1Size = 8 * 1024;
              break;
            case 0x67:
              _l1Size = 16 * 1024;
              break;
            case 0x68:
              _l1Size = 32 * 1024;
              break;
            case 0x78:
              _l2Size = 1 * 1024 * 1024;
              break;
            case 0x79:
              _l2Size = 128 * 1024;
              break;
            case 0x7a:
              _l2Size = 256 * 1024;
              break;
            case 0x7b:
              _l2Size = 512 * 1024;
              break;
            case 0x7c:
              _l2Size = 1* 1024 * 1024;
              break;
            case 0x7d:
              _l2Size = 2 * 1024 * 1024;
              break;
            case 0x7f:
              _l2Size = 512 * 1024;
              break;
            case 0x82:
              _l2Size = 256 * 1024;
              break;
            case 0x83:
              _l2Size = 512 * 1024;
              break;
            case 0x84:
              _l2Size = 1* 1024 * 1024;
              break;
            case 0x85:
              _l2Size = 2 * 1024 * 1024;
              break;
            case 0x86:
              _l2Size = 512 * 1024;
              break;
            case 0x87:
              _l2Size = 1* 1024 * 1024;
              break;

          }
          _regs[i] >>= 8; // next byte 
        }
      }

    }

  }

} //namespace
