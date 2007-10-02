/*
 * $Id$
 */

#include <cstring>
#include <cassert>
#include <iomanip>

#include "ProfResult.h"


namespace mpplas {

  ProfResult::ProfResult() {
    this->reset();
  }

  ProfResult& ProfResult::operator+=(const ProfResult& rhs){
    for( int i = 0; i < BasicCPU::__OpsEnum_SIZE; i++){
      (*this)[i] += rhs[i];
    }
    return *this;
  }
  ProfResult& ProfResult::operator-=(const ProfResult& rhs){
    for( int i = 0; i < BasicCPU::__OpsEnum_SIZE; i++){
      (*this)[i] -= rhs[i];
    }
    return *this;
  }

  OpsCount& ProfResult::operator[](const int i) {
    assert( i < BasicCPU::__OpsEnum_SIZE );
    return _opsCount[i];
  }
  const OpsCount& ProfResult::operator[](const int i) const {
    assert( i < BasicCPU::__OpsEnum_SIZE );
    return _opsCount[i];
  }


  OpsCount ProfResult::getTotalOps() const{
    OpsCount total = 0;
    for( int i = 0; i < BasicCPU::__OpsEnum_SIZE; i++){
      total += _opsCount[i];
    }
    return total;
  }

  void ProfResult::reset(){
    for( int i = 0; i < BasicCPU::__OpsEnum_SIZE; i++){
      _opsCount[i] = 0;
    }
  }

  /////////////////////////////////////////
 
  ProfResult operator+(ProfResult lhs, const ProfResult& rhs){
    lhs += rhs;
    return lhs;
  }
  ProfResult operator-(ProfResult lhs, const ProfResult& rhs){
    lhs -= rhs;
    return lhs;
  }

  /////////////////////////////////////////
  std::ostream& operator<<(std::ostream& out, const ProfResult& prof){
    const double totalOps = prof.getTotalOps();
    for( int i = 0; i < BasicCPU::__OpsEnum_SIZE; i++){
      double percentage = prof[i] / totalOps;
      out << std::setw(10) << std::left << prof[i] ;
      out << "(" << std::setw(4)  << std::left << std::fixed << std::setprecision(2) << percentage << ") ";
      out << BasicCPU::OpsNames[i] << std::endl; 
    }
    out << "------------" << std::endl;
    out << "Total = " << (long)totalOps << std::endl;

    return out;
  }

}
