


template<typename T>
RuntimeData<T>::RuntimeData()
 {
  assert(!pthread_mutex_init(&_mutex, NULL));
}

template<typename T>
  T& RuntimeData<T>::get(const clientId_t clientId, const varId_t varId) throw(NoSuchVariable) {
    pthread_mutex_lock( &_mutex );
    
    T* instance;
    if( this->_contains(clientId, varId) ){
      instance = &(_dataTable[clientId][varId]);
      pthread_mutex_unlock( &_mutex );
      return *instance;
    }
    else{
      pthread_mutex_unlock( &_mutex );
      std::ostringstream oss;
      oss << "Variable '" << varId << "' not found" ;
      throw NoSuchVariable(oss.str());
    }
  }

template<typename T>
  varId_t RuntimeData<T>::set(const clientId_t clientId, const T& instance, const std::string typeStr){
    pthread_mutex_lock( &_mutex );
    const varId_t varId( _getAvailableVarId(clientId, typeStr) );
    _dataTable[clientId][varId] = instance;
    pthread_mutex_unlock( &_mutex );
    return varId;
  }

template<typename T>
void RuntimeData<T>::eraseClient(const clientId_t clientId){

  pthread_mutex_lock( &_mutex );
  ClientVarsType& varIds( _dataTable[clientId] );
  typename ClientVarsType::iterator toDeleteIt;
  for(toDeleteIt = varIds.begin(); toDeleteIt != varIds.end(); toDeleteIt++){
    delete (*toDeleteIt).second;
    std::cout << "cleared " << (*toDeleteIt).first << std::endl;
  }

  _dataTable.erase(clientId);
  pthread_mutex_unlock( &_mutex );

  std::cout << "clientId " << clientId << " deleted\n" 
    << "table size now: " << _dataTable.size() << std::endl;

}

template<typename T>
void RuntimeData<T>::runGC(const clientId_t clientId, const std::vector<varId_t>& usedSlots){
  pthread_mutex_lock( &_mutex );
  ClientVarsType newClientVars;
  ClientVarsType& oldClientVars( _dataTable[clientId] );
  std::vector<varId_t>::const_iterator it;
  for(it = usedSlots.begin(); it != usedSlots.end(); it++){
    newClientVars[*it] = oldClientVars[*it];
    oldClientVars.erase(*it); //the ones to keep are removed
  }
  typename ClientVarsType::iterator toDeleteIt;
  // the ones remeining in the old map are to be freed
  for(toDeleteIt = oldClientVars.begin(); toDeleteIt != oldClientVars.end(); toDeleteIt++){
    delete (*toDeleteIt).second;
  }
  oldClientVars.clear(); //maybe it's redundant...
  oldClientVars = newClientVars;
  pthread_mutex_unlock( &_mutex );
  return;
}
  


template<typename T>
bool RuntimeData<T>::_contains(const clientId_t clientId, const varId_t varId){
  ClientVarsType clientVars = _dataTable[clientId];
  const typename ClientVarsType::iterator it = clientVars.find(varId);
  if( it == clientVars.end() ){
    return false;
  }
  else{
    return true;
  }
}

template<typename T>
varId_t RuntimeData<T>::_getAvailableVarId(const clientId_t clientId, const std::string typeStr){
  int rnd;
  std::set<int>& usedSet(_usedVarIds[clientId]);
  do{
    rnd = rand(); 
  } while( usedSet.find(rnd) != usedSet.end() );
  usedSet.insert(rnd);
  
  std::ostringstream oss;
  oss << typeStr << "-" << rnd;
  return oss.str();
}
  




