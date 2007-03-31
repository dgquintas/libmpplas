from RPCServer import RPCServer
from Configuration import Configuration
from xmlrpclib import Fault

def __elemsToStr(ls):
  newl = []
  for elem in ls:
    newl.append(str(elem))
  return newl

global filteredMethods
global global_rpcServer

def initializeClient():
  global_config = Configuration()
  global global_rpcServer
  global_rpcServer = RPCServer.getInstance( global_config.url )

  global filteredMethods
  filteredMethods = filter(lambda mName: mName[:7] != 'system.', 
                            global_rpcServer.system.listMethods())

  proxyFuncsSrc = """def %s(*args):
    \"\"\"%s\"\"\"
    newArgs = []
    for arg in args:
      if type(arg) in ( type(()), type([]) ):
        newArgs.append( __elemsToStr(arg) )
      else:
        newArgs.append(str(arg))
    try:
      result = global_rpcServer.%s(*newArgs)
    except Fault, e:
      raise "Exception from the server: " + e.faultString   
    except:
      raise
    
    if type(result) == type(""):
      result = Z(result)
    # else, do not chage its type   
    
    return result
"""

  for mName in filteredMethods:
    exec proxyFuncsSrc % (mName, global_rpcServer.system.methodHelp(mName), mName) in globals()

  return globals()



def listFuncs():
  return filteredMethods

class Z(object):

  def __init__(self, zStr=""):
    self.__integerStr = str(zStr)

  def __add__(self, anotherZ): 
    return zAdd(self, anotherZ )
  def __iadd__(self, anotherZ): 
    self.__integerStr = str(zAdd(self, anotherZ))
    return self

  def __sub__(self, anotherZ): 
    return zSub(self, anotherZ )
  def __isub__(self, anotherZ): 
    self.__integerStr = str(zSub(self, anotherZ))
    return self

  def __mul__(self, anotherZ): 
    return zMul(self, anotherZ )
  def __imul__(self, anotherZ): 
    self.__integerStr = str(zMul(self, anotherZ))
    return self

  def __div__(self, anotherZ): 
    return zDiv(self, anotherZ )
  def __idiv__(self, anotherZ): 
    self.__integerStr = str(zDiv(self, anotherZ))
    return self

  def __mod__(self, anotherZ): 
    return zMod(self, anotherZ )
  def __mod__(self, anotherZ): 
    self.__integerStr = str(zMod(self, anotherZ))
    return self
 

  def __lt__(self, anotherZ):
    return long(str(self)) < long(str(anotherZ))
  def __le__(self, anotherZ):
    return long(str(self)) <= long(str(anotherZ))
  def __eq__(self, anotherZ):
    return long(str(self)) == long(str(anotherZ))
  def __ne__(self, anotherZ):
    return long(str(self)) != long(str(anotherZ))
  def __gt__(self, anotherZ):
    return long(str(self)) > long(str(anotherZ))
  def __ge__(self, anotherZ):
    return long(str(self)) >= long(str(anotherZ))







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


