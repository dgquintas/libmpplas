/*
 * $Id$
 */

#include <cstring>
#include <cassert>

#include "ProfResult.h"


namespace mpplas {

  ProfResult::ProfResult() {
    this->reset();
  }

  ProfResult& ProfResult::operator+=(const ProfResult& rhs){
    for( int i = 0; i < __OpsEnum_SIZE; i++){
      (*this)[i] += rhs[i];
    }
    return *this;
  }
  ProfResult& ProfResult::operator-=(const ProfResult& rhs){
    for( int i = 0; i < __OpsEnum_SIZE; i++){
      (*this)[i] -= rhs[i];
    }
    return *this;
  }

  OpsCount& ProfResult::operator[](const size_t i) {
    assert( i < ProfResult::__OpsEnum_SIZE );
    return _opsCount[i];
  }
  const OpsCount& ProfResult::operator[](const size_t i) const {
    assert( i < ProfResult::__OpsEnum_SIZE );
    return _opsCount[i];
  }


  OpsCount ProfResult::getTotalOps() const{
    OpsCount total = 0;
    for( int i = 0; i < __OpsEnum_SIZE; i++){
      total += _opsCount[i];
    }
    return total;
  }

  void ProfResult::reset(){
    for( int i = 0; i < __OpsEnum_SIZE; i++){
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
    out << prof[ProfResult::ADD] << "\tadds" << std::endl; 
    out << prof[ProfResult::ADDX] << "\taddxs" << std::endl; 
    out << prof[ProfResult::SUB] << "\tsubs" << std::endl; 
    out << prof[ProfResult::SUBX] << "\tsubxs" << std::endl; 
    out << prof[ProfResult::ADDMUL] << "\taddmuls" << std::endl; 
    out << prof[ProfResult::MUL] << "\tmuls" << std::endl; 
    out << prof[ProfResult::DIV] << "\tdivs" << std::endl; 
    out << prof[ProfResult::SHIFTL] << "\tshiftls" << std::endl; 
    out << prof[ProfResult::SHIFTLR] << "\tshiftlrs" << std::endl; 
    out << prof[ProfResult::MNOB] << "\tmnobs" << std::endl; 
    out << "------------" << std::endl;
    out << "Total = " << prof.getTotalOps() << std::endl;

    return out;
  }

}
