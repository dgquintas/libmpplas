from RPCServer import RPCServer
from Configuration import Configuration

global_config = Configuration()
global_rpcServer = RPCServer.getInstance( global_config.url )



filteredMethods = filter(lambda mName: mName[:7] != 'system.', 
                          global_rpcServer.system.listMethods())

proxyFuncsSrc = """def %s(*args): 
  for i in xrange(len(args)):
    args[i] = str(args[i])
  return global_rpcServer.%s(*args)
"""

for mName in filteredMethods:
  exec( proxyFuncsSrc % (mName,mName), globals(), locals() )


class Z(object):

  def __init__(self, zStr=""):
    self.__integerStr = str(zStr)

  def __add__(self, anotherZ): 
    return global_rpcServer.zAdd(self.__integerStr, anotherZ.__integerStr)
  def __iadd__(self, anotherZ): 
    self.__integerStr = global_rpcServer.zAdd(self.__integerStr, anotherZ.__integerStr)

  def __sub__(self, anotherZ): 
    return global_rpcServer.zSub(self.__integerStr, anotherZ.__integerStr)
  def __isub__(self, anotherZ): 
    self.__integerStr = global_rpcServer.zSub(self.__integerStr, anotherZ.__integerStr)
    

  def __mul__(self, anotherZ): 
    return global_rpcServer.zMul(self.__integerStr, anotherZ.__integerStr)
  def __imul__(self, anotherZ):
    self.__integerStr = global_rpcServer.zMul(self.__integerStr, anotherZ.__integerStr)


  def __div__(self, anotherZ): 
    return global_rpcServer.zDiv(self.__integerStr, anotherZ.__integerStr)
  def __idiv__(self, anotherZ):
    self.__integerStr = global_rpcServer.zDiv(self.__integerStr, anotherZ.__integerStr)


  def __len__(self):
    return len(self.__integerStr);

  def __getitem__(self, key):
    return self.__integerStr[key]

  def __repr__(self):
    return 'Z("' + self.__integerStr + '")'

  def __str__(self):
    return self.__integerStr


import sys
if __name__ == '__main__':
  sys.exit("Not meant to be used standalone")


