
#include <cstring>

#include "CPUInfo_x86_64.h"
#include "Utils.h"
#include "BasicTypedefs.h"
#include "CompilationConfig.h"

namespace mpplas{

  //static singleton initialization
  template<>
    const std::auto_ptr< CPUInfo_x86_64 > 
    SingletonMixIn< CPUInfo_x86_64 >::singletonInstance( new CPUInfo_x86_64() );


  CPUInfo_x86_64::CPUInfo_x86_64()
    : SingletonMixIn< CPUInfo_x86_64 >()
  {
    _l1Size = _l2Size = _l3Size = 0;
    _getCacheSizes();
    _getSIMDInfo();
    _getModelName();

  }


  int CPUInfo_x86_64::getCacheL1Size() const {
    return _l1Size;
  }
  int CPUInfo_x86_64::getCacheL2Size() const {
    return _l2Size;
  }
  int CPUInfo_x86_64::getCacheL3Size() const {
    return _l3Size;
  }

  std::string CPUInfo_x86_64::getModelName() const {
    return _modelName;
  }


  std::string CPUInfo_x86_64::getArchName() const {
    return std::string(CompilationConfig::TARGET_ARCH);
  }

  std::vector<std::string> CPUInfo_x86_64::getSIMDCapabilities() const {
    return _simdCap;
  }

  int CPUInfo_x86_64::getDigitBitWidth() const {
    return sizeof(Digit)*8;
  }
  

  //////////////////////////////////////////////////////////////

  inline void CPUInfo_x86_64::_invokeCPUID(uint32_t eax){
    asm volatile(
        "cpuid            \n\t"
        : "=a"(*_regs), "=b"(_regs[1]), "=c"(_regs[2]), "=d"(_regs[3])
        : "a"(eax)
        : "cc");
  }
  

  void CPUInfo_x86_64::_getSIMDInfo(){
    _invokeCPUID(1);

      if( _regs[EDX] & (1L << 23) ){ _simdCap.push_back("MMX") ; }
      if( _regs[EDX] & (1L << 25) ){ _simdCap.push_back("SSE") ; }
      if( _regs[EDX] & (1L << 26) ){ _simdCap.push_back("SSE2") ; }
      if( _regs[ECX] & (1L) )      { _simdCap.push_back("SSE3") ; }
      if( _regs[ECX] & (1L << 9) ) { _simdCap.push_back("SSSE3") ; }
  }

  void CPUInfo_x86_64::_getModelName(){
    static char* BRAND_TABLE[24] = {
      /* 00H */ "This processor does not support the brand identification feature",
      /* 01H */ "Intel(R) Celeron(R) processor",
      /* 02H */ "Intel(R) Pentium(R) III processor",
      /* 03H */ "Intel(R) Pentium(R) III Xeon(R) processor / Intel(R) Celeron(R) processor",
      /* 04H */ "Intel(R) Pentium(R) III processor",
      /* 05H */ "",
      /* 06H */ "Mobile Intel(R) Pentium(R) III processor-M",
      /* 07H */ "Mobile Intel(R) Celeron(R) processor1",
      /* 08H */ "Intel(R) Pentium(R) 4 processor",
      /* 09H */ "Intel(R) Pentium(R) 4 processor",
      /* 0AH */ "Intel(R) Celeron(R) processor1",
      /* 0BH */ "Intel(R) Xeon(R) processor / Intel(R) Xeon(R) processor MP",
      /* 0CH */ "Intel(R) Xeon(R) processor MP",
      /* 0DH */ "",
      /* 0EH */ "Mobile Intel(R) Pentium(R) 4 processor-M / Intel(R) Xeon(R) processor",
      /* 0FH */ "Mobile Intel(R) Celeron(R) processor",
      /* 10H */ "",
      /* 11H */ "Mobile Genuine Intel(R) processor",
      /* 12H */ "Intel(R) Celeron(R) M processor",
      /* 13H */ "Mobile Intel(R) Celeron(R) processor",
      /* 14H */ "Intel(R) Celeron(R) processor",
      /* 15H */ "Mobile Genuine Intel(R) processor",
      /* 16H */ "Intel(R) Pentium(R) M processor",
      /* 17H */ "Mobile Intel(R) Celeron(R) processor"
    };

    _invokeCPUID(0x80000000);
    if( _regs[EAX] & 0x80000000 ){

      char brand[48];

      _invokeCPUID( 0x80000002 );
      memcpy(&brand[0], _regs, sizeof(uint32_t)*4);

      _invokeCPUID( 0x80000003 );
      memcpy(&brand[16], _regs, sizeof(uint32_t)*4);

      _invokeCPUID( 0x80000004 );
      memcpy(&brand[32], _regs, sizeof(uint32_t)*4);

      _modelName = std::string(brand);
    }
    else{
      _invokeCPUID(1);

      const short idx = _regs[EBX] & 0xff;
      _modelName = std::string(BRAND_TABLE[ idx ]);
    }


    _modelName = Utils::strip(_modelName);

    return;
  }

  void CPUInfo_x86_64::_getCacheSizes(){
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

