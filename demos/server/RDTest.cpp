#include "RuntimeData.h"

int main(){

  RuntimeData<int> data;

  int ids[5];
   ids[0] = data.set(123,1488);
   ids[1] = data.set(123,148);
   ids[2] = data.set(123,14);
   ids[3] = data.set(123,1);
   ids[4] = data.set(123,2);

   for(int i =0 ; i < 5; i++){
    try{
      std::cout << data.get(123,ids[i]) << std::endl;
    }
    catch( const std::exception& e ){
      std::cout << e.what() << std::endl;
    }
  }
 
   std::cout << "Lets GC" << std::endl;
  std::vector<int> used(2);
  used.push_back(ids[1]);
  used.push_back(ids[4]);
  data.runGC(123, used);
  for(int i =0 ; i < 5; i++){
    try{
      std::cout << data.get(123,ids[i]) << std::endl;
    }
    catch( const std::exception& e ){
      std::cout << e.what() << std::endl;
    }
  }


  return 0;

}
