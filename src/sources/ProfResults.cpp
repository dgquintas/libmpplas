/*
 * $Id$
 */

#include <cstring>
#include <cassert>


#include "ProfResults.h"
#include "omp_mock.h"
#include "SystemInfo.h"



namespace mpplas {

  ProfResults::ProfResults() 
  : _perThreadResults ( SystemInfo::getMaxNumberOfThreads() ) { 
    this->reset();
  }

  ProfResults& ProfResults::operator+=(const ProfResults& rhs){
    for( std::vector<int>::size_type i = 0; i < _perThreadResults.size(); i++){
      (*this)[i] += rhs[i];
    }
    return *this;
  }
  ProfResults& ProfResults::operator-=(const ProfResults& rhs){
    for( std::vector<int>::size_type i = 0; i < _perThreadResults.size(); i++){
      (*this)[i] -= rhs[i];
    }
    return *this;
  }

  ProfResult& ProfResults::operator[](const int i) {
    return _perThreadResults.at(i);
  }
  const ProfResult& ProfResults::operator[](const int i) const {
    return _perThreadResults.at(i);
  }


  OpsCount ProfResults::getTotalOps() const{
    OpsCount total = 0;
    for( std::vector<int>::size_type i = 0; i < _perThreadResults.size(); i++){
      total += _perThreadResults[i].getTotalOps();
    }
    return total;
  }

  void ProfResults::reset(){
    for( std::vector<int>::size_type i = 0; i < _perThreadResults.size(); i++){
      _perThreadResults[i].reset();
    }
  }

  int ProfResults::size() const {
    return _perThreadResults.size();
  }

  /////////////////////////////////////////
 
  ProfResults operator+(ProfResults lhs, const ProfResults& rhs){
    lhs += rhs;
    return lhs;
  }
  ProfResults operator-(ProfResults lhs, const ProfResults& rhs){
    lhs -= rhs;
    return lhs;
  }

  /////////////////////////////////////////
  std::ostream& operator<<(std::ostream& out, const ProfResults& prof){
    for(std::vector<int>::size_type i = 0; i < prof._perThreadResults.size(); i++){
      out << "Thread " << i << ":\n";
      out << "---------\n";
      out << prof._perThreadResults[i] << std::endl;
    }

    return out;


  }
}
