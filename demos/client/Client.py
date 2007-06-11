# encoding: utf-8

#
# $Id$
#

from RPCServer import RPCServer
from Configuration import Configuration
from xmlrpclib import Fault,MultiCall

def __elemsToStr(ls):
  newl = []
  for elem in ls:
    newl.append(str(elem))
  return newl

global filteredMethods
global global_config

def beginBatch():
  RPCServer.getInstance().setBatch(True)

def runBatch(reset = True):
  res = RPCServer.getInstance().getBatchServer()()
  if reset:
    RPCServer.getInstance().resetBatch()
  return [x for x in res]

def endBatch():
  RPCServer.getInstance().setBatch(False)

def initializeClient(configFileName = 'config.cfg'):
  global global_config
  global_config = Configuration(configFileName)
  rpcServer = RPCServer.getInstance( global_config.RPCServerURL )

  global filteredMethods
  filteredMethods = filter(lambda mName: mName[:7] != 'system.' and mName[0] != '_', 
                            rpcServer.getInteractiveServer().system.listMethods())

  proxyFuncsSrc = """def %(methodName)s(*args):
    \"\"\"%(methodHelp)s\"\"\"
    methodName = '%(methodName)s'[:2]
    newArgs = []
    rpcServer = RPCServer.getInstance()
    for arg in args:
      if type(arg) in ( type(()), type([]) ):
        newArgs.append( __elemsToStr(arg) )
      else:
        newArgs.append(str(arg))
    try:
      result = rpcServer.getServer().%(methodName)s(*newArgs)
    except Fault, e:
      raise "Exception from the server: " + e.faultString   
    except:
      raise
    
    if type(result) == type(""):
      if methodName[0] == 'z':
        result = Z(result)
      elif methodName[0] == 'r':
        result = R(result)
      elif methodName[:2] == 'mz':
        result = MZ(result)
    # else, do not chage its type   
    
    return result
"""
  for mName in filteredMethods:
    rpcServer.getBatchServer().system.methodHelp(mName)
  
  methodsHelp = zip(filteredMethods, rpcServer.getBatchServer()())
  for methodAndHelpPair in methodsHelp:
    exec proxyFuncsSrc % \
    {'methodName': methodAndHelpPair[0], 
     'methodHelp': methodAndHelpPair[1]
    } in globals()

  return globals()

def listFuncs():
  return filteredMethods

def checkForUpdates():
  import md5
  updated = False
  if global_config.checkForUpdates:
    latestOne = global_config.clientLatestUpdate
    localOneHandler = open(global_config.clientFilename, 'r') 
    localOne = md5.new( localOneHandler.read() ).hexdigest()
    localOneHandler.close()

    if latestOne != localOne:
      updated = True
    else:
      updated = False

    return updated

def performUpdate():
  import shutil
  backupFname = global_config.clientFilename + '.bak'
  shutil.copy(global_config.clientFilename, backupFname)
  localOneHandler = open(global_config.clientFilename, 'w') 
  localOneHandler.write( global_config.remoteFileContents )
  localOneHandler.close()
  localOneHandler.close()

  return backupFname

def hasBeenUpdated(self):
  return self.hasBeenUpdated


######################################################
#
#  Client implementation begins here
#
######################################################

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


#######################################################################

class R(object):

  def __init__(self, rStr=""):
    self.__realStr = str(rStr)

  def __add__(self, anotherR): 
    return rAdd(self, anotherR )
  def __iadd__(self, anotherR): 
    self.__realStr = str(rAdd(self, anotherR))
    return self

  def __sub__(self, anotherR): 
    return rSub(self, anotherR )
  def __isub__(self, anotherR): 
    self.__realStr = str(rSub(self, anotherR))
    return self

  def __mul__(self, anotherR): 
    return rMul(self, anotherR )
  def __imul__(self, anotherR): 
    self.__realStr = str(rMul(self, anotherR))
    return self

  def __div__(self, anotherR): 
    return rDiv(self, anotherR )
  def __idiv__(self, anotherR): 
    self.__realStr = str(rDiv(self, anotherR))
    return self


  def __lt__(self, anotherR):
    return long(str(self)) < long(str(anotherR))
  def __le__(self, anotherR):
    return long(str(self)) <= long(str(anotherR))
  def __eq__(self, anotherR):
    return long(str(self)) == long(str(anotherR))
  def __ne__(self, anotherR):
    return long(str(self)) != long(str(anotherR))
  def __gt__(self, anotherR):
    return long(str(self)) > long(str(anotherR))
  def __ge__(self, anotherR):
    return long(str(self)) >= long(str(anotherR))


  def __len__(self):
    return len(self.__realStr);

  def __getitem__(self, key):
    return self.__realStr[key]

  def __repr__(self):
    return 'R("' + self.__realStr + '")'

  def __str__(self):
    return self.__realStr


###############################################################################

class MZ(object): #matrix Z

  def __init__(self, mzStr=""):
    self.__matrixZStr = str(mzStr)

  def __add__(self, anotherMZ): 
    return mzAdd(self.__matrixZStr, anotherMZ.__matrixZStr )
  def __iadd__(self, anotherMZ): 
    self.__matrixZStr = str( mzAdd( self.__matrixZStr, anotherMZ.__matrixZStr ) )
    return self
 
  def __mul__(self, anotherMZ): 
    return mzMul(self.__matrixZStr, anotherMZ.__matrixZStr )
  def __imul__(self, anotherMZ): 
    self.__matrixZStr = str( mzMul( self.__matrixZStr, anotherMZ.__matrixZStr ) )
    return self


  def __getitem__(self, row):
    pyRep = self.__strToPyRep( self.__matrixZStr )
    return pyRep[row]

  def __repr__(self):
    return 'MZ("' + self.__matrixZStr + '")'

  def __str__(self):
    return rpcServer.getInteractiveServer()._mzPPrint(self.__matrixZStr)

  def __strToPyRep(self, str):
    res = []
    str = str.strip()
    str = str[1:-1].strip() #remove the external [ ]
    rows = str.split(';')
    for i in rows:
      res.append( i.split() )

    return res

  def __PyRepToStr(self, pyRep):
    strRows = []
    map( lambda row: strRows.append(" ".join(row)), py)
    str = " ; ".join(strRows)
    str = "[ " + str +" ]"

    return str


import sys
if __name__ == '__main__':
  sys.exit("Not meant to be used standalone")
  
  


