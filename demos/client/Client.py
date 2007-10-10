# encoding: utf-8

#
# $Id$
#

from RPCServer import RPCServer
from Configuration import Configuration
from xmlrpclib import Fault,MultiCall
import threading
import thread
import Queue
import wx
import wx.lib.delayedresult as delayedresult

global filteredMethods
global global_config
global clientId

class Variable(object):
  def __init__(self, varId):
    self.__varId = varId;
  def getId(self):
    return self.__varId;
  def setId(self, newId):
    self.__varId = newId;
    

def __elemsToStr(ls):
  newl = []
  for elem in ls:
    newl.append(str(elem))
  return newl



def beginBatch():
  RPCServer.getInstance().setBatch(True)

def runBatch(reset = True):
  res = RPCServer.getInstance().getBatchServer()()
  if reset:
    RPCServer.getInstance().resetBatch()
  return [x for x in res]

def endBatch():
  RPCServer.getInstance().setBatch(False)

def toInt(arg):
  res = 0;
  if isinstance(arg, Z):
  # recover the data and cast it to an XMLRPC integer (32 bits) 
    res = int(zGet(arg.getId()))
  else:
    res = int(arg)

  return res


def initializeClient(configFileName = 'config.cfg'):
  global global_config
  global clientId
  global_config = Configuration(configFileName)
  rpcServer = RPCServer.getInstance( global_config.RPCServerURL )
  clientId = rpcServer.getServer()._requestClientId()

  global filteredMethods
  filteredMethods = filter(lambda mName: mName[:7] != 'system.' and mName[0] != '_', 
                            rpcServer.getInteractiveServer().system.listMethods())

  proxyFuncsSrc = """def %(methodName)s(*args):
    \"\"\"%(methodHelp)s\"\"\"
    methodName = '%(methodName)s'[:2]
    newArgs = [clientId]
    rpcServer = RPCServer.getInstance()
    for arg in args:
      if type(arg) in ( type(()), type([]) ):
        newArgs.append( __elemsToStr(arg) )
      elif isinstance(arg, Z):
        newArgs.append(arg.getId())
      else:
        newArgs.append(arg)
    try:
      result = rpcServer.getServer().%(methodName)s(*newArgs)
    except:
      raise

    if isinstance(result, dict):
      tpe = result['type']
      varId = result['varId']
      if tpe == "Z":
        result = Z(id=varId)

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



###################################################################

class ThreadRunner(threading.Thread):
  queue = Queue.Queue()
  stopThreads = False
  stopLock = threading.Lock()

  def __init__(self):
    threading.Thread.__init__(self)
    ThreadRunner.results = Queue.Queue()

  def stop(cls, status = True):
    cls.stopLock.acquire()
    cls.stopThreads = status
    cls.stopLock.release()
  stop = classmethod(stop)

  def isStopped(cls):
    cls.stopLock.acquire()
    status = cls.stopThreads
    cls.stopLock.release()
    return status
  isStopped = classmethod(isStopped)


  def run(self):
    while True and ( not ThreadRunner.isStopped() ):
      try:
        taskWithIndex = ThreadRunner.queue.get_nowait()
        self.id, task = taskWithIndex
      except Queue.Empty:
        break
      try:
        exec task in globals(), locals()
        self.appendResult(locals()['result'])
      except Exception, e:
        self.appendResult("ERROR: " + str(e))
      ThreadRunner.queue.task_done()
    
    if ThreadRunner.isStopped():
      #discard the rest of the tasks
      ThreadRunner.stop(False)
      while True:
        try:
          ThreadRunner.queue.get_nowait()
          ThreadRunner.queue.task_done()
        except (ValueError, Queue.Empty):
          break
 


  def appendResult(self, result):
    ThreadRunner.results.put( (self.id, result) )

  def getResults(cls):
    return cls.results
  getResults = classmethod(getResults)


def runInParallel( listOfSnippets, numberOfThreads ):
  runInParallel.res = None
  progress = wx.ProgressDialog("Tasks completion progress",
                               "",
                               maximum = len(listOfSnippets),
                               parent=None,
                               style = wx.PD_CAN_ABORT
                                | wx.PD_APP_MODAL
                                | wx.PD_ELAPSED_TIME
                                | wx.PD_REMAINING_TIME
                                | wx.PD_SMOOTH
                                )

  def doRun():
    for i in xrange( min(numberOfThreads, len(listOfSnippets)) ):
      t = ThreadRunner()
      t.start()
    ThreadRunner.queue.join()
    return ThreadRunner.getResults()

  def consumer(delayedResult):
    resQueue = delayedResult.get()
    runInParallel.res = [None]*resQueue.qsize()
    while not resQueue.empty():
      elem = resQueue.get()
      runInParallel.res[elem[0]] = elem[1]


  for taskN, snippet in enumerate(listOfSnippets):
    ThreadRunner.queue.put((taskN, snippet))

  delayedresult.startWorker(consumer, doRun)
  while (threading.activeCount() > 1) or (not ThreadRunner.queue.empty()):
    wx.MilliSleep(250)
    i = (len(listOfSnippets) - ThreadRunner.queue.qsize())-(threading.activeCount()-1)
    keepgoing = progress.Update( i )[0]
    if not keepgoing: 
      ThreadRunner.stop()
      break
  progress.Destroy()

  return runInParallel.res

######################################################################################

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

class Z(Variable):
  def __init__(self, zStr="0", id=None):
    if id:
      varId = id
    else:
      #create the instance on the server -> we get the varId
      varId = zCreate(zStr)
    #invoke Variable's constructor with the varId
    Variable.__init__(self, varId)

  def __add__(self, anotherZ): 
    if not isinstance(anotherZ,type(self)):
      anotherZ = Z(str(anotherZ))
    return Z(id=zAdd(self, anotherZ ))
  def __iadd__(self, anotherZ): 
    self.setId( self.__add__(anotherZ).getId() )
    return self

  def __sub__(self, anotherZ): 
    if not isinstance(anotherZ,type(self)):
      anotherZ = Z(str(anotherZ))
    return Z(id=zSub(self, anotherZ ))
  def __isub__(self, anotherZ): 
    self.setId( self.__sub__(anotherZ).getId() )
    return self

  def __mul__(self, anotherZ): 
    if not isinstance(anotherZ,type(self)):
      anotherZ = Z(str(anotherZ))
    return Z(id=zMul(self, anotherZ ))
  def __imul__(self, anotherZ): 
    self.setId( self.__mul__(anotherZ).getId() )
    return self


  def __div__(self, anotherZ): 
    if not isinstance(anotherZ,type(self)):
      anotherZ = Z(str(anotherZ))
    return Z(id=zDiv(self, anotherZ ))
  def __idiv__(self, anotherZ): 
    self.setId( self.__div__(anotherZ).getId() )
    return self


  def __mod__(self, anotherZ): 
    if not isinstance(anotherZ,type(self)):
      anotherZ = Z(str(anotherZ))
    return Z(id=zMod(self, anotherZ ))
  def __imod__(self, anotherZ): 
    self.setId( self.__mod__(anotherZ).getId() )
    return self


  def __lt__(self, anotherZ):
    return long(self.__str__()) < long(anotherZ.__str__())
  def __le__(self, anotherZ):
    return long(self.__str__()) <= long(anotherZ.__str__())
  def __eq__(self, anotherZ):
    return long(self.__str__()) == long(anotherZ.__str__())
  def __ne__(self, anotherZ):
    return long(self.__str__()) != long(anotherZ.__str__())
  def __gt__(self, anotherZ):
    return long(self.__str__()) > long(anotherZ.__str__())
  def __ge__(self, anotherZ):
    return long(self.__str__()) >= long(anotherZ.__str__())


  def __len__(self):
    return len(self.__str__());

  def __repr__(self):
    return "%s with id %d" % (type(self),self.getId())
#    return self.__str__()

  def __str__(self):
    res = zGet(self.getId())
    return res


#######################################################################

class R(Variable):

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

class MZ(Variable): #matrix Z

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
    return RPCServer.getInstance().getInteractiveServer()._mzPPrint(self.__matrixZStr)

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

#########################################################



import sys
if __name__ == '__main__':
  sys.exit("Not meant to be used standalone")
  
  


