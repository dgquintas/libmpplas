
#include <map>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <pthread.h>


class NoSuchVariable : public std::invalid_argument
{
  public:
    explicit NoSuchVariable(const std::string& what_arg)
      : std::invalid_argument(what_arg)
    {}
};

template<typename T>
class RuntimeData {

  public:
    RuntimeData();

    typedef std::map<int, T > ClientVarsType;
    typedef std::map<int, ClientVarsType > TableType;
    
    T& get(const int clientId, const int varId) throw(NoSuchVariable) ;
    int set(const int clientId, const T& instance);

    void runGC(const int clientId, const std::vector<int>& usedSlots);


  private:
    TableType _dataTable;
    pthread_mutex_t _mutex;
    std::map<int, std::set<int> > _usedVarIds;
    std::map<int, std::vector<int> > _clientUsedSlots;
    
    bool _contains(const int clientId, const int varId);
    int _getAvailableVarId(const int clientId);

};

#include "RuntimeData.cpp"

