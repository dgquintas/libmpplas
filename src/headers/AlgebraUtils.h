#ifndef __ALGEBRAUTILS_H
#define __ALGEBRAUTILS_H

#include <string>

namespace mpplas{

  class Dimensions {
    public:
      Dimensions();
      Dimensions(size_t n, size_t m);
      Dimensions(const Dimensions&);

      size_t getRows() const;
      size_t getColumns() const;
      size_t getProduct() const;

      void setRows(size_t n);
      void setColumns(size_t m);
      void setBoth(size_t n, size_t m);

      bool operator==(const Dimensions& rhs) const;
      bool operator!=(const Dimensions& rhs) const;

      std::string toString() const;

    protected:
      size_t _n;
      size_t _m;

  };
}

#endif
