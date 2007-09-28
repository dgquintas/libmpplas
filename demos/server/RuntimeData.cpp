


template<typename T>
RuntimeData<T>::RuntimeData(){
  assert(!pthread_mutex_init(&_mutex, NULL));
}

template<typename T>
  T& RuntimeData<T>::get(const int clientId, const int varId) throw(NoSuchVariable) {
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
      oss << "Variable '" << varId << "' not found";
      throw NoSuchVariable(oss.str());
    }


  }

template<typename T>
  int RuntimeData<T>::set(const int clientId, const T& instance){
    pthread_mutex_lock( &_mutex );
    const int varId( _getAvailableVarId(clientId) );
    _dataTable[clientId][varId] = instance;
    pthread_mutex_unlock( &_mutex );
    return varId;
  }

template<typename T>
void RuntimeData<T>::runGC(const int clientId, const std::vector<int>& usedSlots){
  pthread_mutex_lock( &_mutex );
  ClientVarsType newClientVars;
  ClientVarsType& oldClientVars( _dataTable[clientId] );
  std::vector<int>::const_iterator it;
  for(it = usedSlots.begin(); it != usedSlots.end(); it++){
    newClientVars[*it] = oldClientVars[*it];
  }
  oldClientVars = newClientVars;
  pthread_mutex_unlock( &_mutex );
  return;
}
  


template<typename T>
bool RuntimeData<T>::_contains(const int clientId, const int varId){
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
int RuntimeData<T>::_getAvailableVarId(const int clientId){
  int rnd;
  std::set<int>& usedSet(_usedVarIds[clientId]);
  do{
    rnd = rand();
  } while( usedSet.find(rnd) != usedSet.end() );
  usedSet.insert(rnd);
  return rnd;
}
  



