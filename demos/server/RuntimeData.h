
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
    RuntimeData(const std::string& containedDataName );

    typedef std::string varId_t;
    typedef int clientId_t;

    typedef std::map<varId_t    /* varId */, T > ClientVarsType;
    typedef std::map<clientId_t /* clientId */,  ClientVarsType > TableType;
    
    T& get(const clientId_t clientId, const varId_t varId) throw(NoSuchVariable) ;
    varId_t set(const clientId_t clientId, const T& instance);

    void runGC(const clientId_t clientId, const std::vector<varId_t>& usedSlots);


  private:
    TableType _dataTable;
    pthread_mutex_t _mutex;
    std::map<clientId_t, std::set<int> > _usedVarIds;
    const std::string _containedDataName;
    
    bool _contains(const clientId_t clientId, const varId_t varId);
    varId_t _getAvailableVarId(const clientId_t clientId);

};

#include "RuntimeData.cpp"

