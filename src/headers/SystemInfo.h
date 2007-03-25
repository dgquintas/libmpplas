/*
 * $Id$
 */

#ifndef __SYSTEMINFO_H
#define __SYSTEMINFO_H


#include <string>
#include "AbstractMethod.h"
#include "constantes.h"

namespace mpplas{

  class SystemInfo : public AbstractMethod {
    public:
      std::string getArchitecture() const;
      size_t getBasicTypeBitLength() const;

      typedef SystemInfo DFL;
  };

}

#endif
