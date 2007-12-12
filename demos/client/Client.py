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
global createCount

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
    endBatch()
  resultsList = []
  for r in res:
    if isinstance(r, str):
      tpe = r.split("-",1)[0]
      resInstance = eval( "%s(id='%s')" % (tpe, r) )
      resultsList.append(resInstance)
    else:
      resultsList.append(r)

  return resultsList

def endBatch():
  RPCServer.getInstance().setBatch(False)

def toInt(arg):
  res = 0;
  if isinstance(arg, Z):
  # recover the data and cast it to an XMLRPC integer (32 bits) 
    res = int(_getData(arg.getId()))
  else:
    res = int(arg)

  return res

def helpFuncs():
  from pprint import pprint
  rpcServer = RPCServer.getInstance()
  methods = listFuncs()
  for mName in listFuncs():
    rpcServer.getBatchServer().system.methodHelp(mName)
  
  methodsHelp = zip(methods, rpcServer.getBatchServer()())
  RPCServer.getInstance().resetBatch()
  pprint(dict(methodsHelp))


def initializeClient(configFileName = 'config.cfg'):
  global global_config
  global clientId
  global createCount
  global gcThreshold
  createCount = 0
  global_config = Configuration(configFileName)
  rpcServer = RPCServer.getInstance( global_config.RPCServerURL )
  clientId = rpcServer.getServer().__requestClientId()
  gcThreshold = global_config.GCThreshold
  global filteredMethods
  filteredMethods = filter(lambda mName: mName[:7] != 'system.' and mName[0:2] != '__', 
                            rpcServer.getInteractiveServer().system.listMethods())

  proxyFuncsSrc = """def %(methodName)s(*args):
    \"\"\"%(methodHelp)s\"\"\"
    global createCount
    global gcThreshold 
    mName = '%(methodName)s'
    newArgs = [clientId]
    rpcServer = RPCServer.getInstance()


    for arg in args:
      if type(arg) in ( type(()), type([]) ):
        newArgs.append( __elemsToStr(arg) )
      elif isinstance(arg, Variable):
        newArgs.append(arg.getId())
      else:
        newArgs.append(arg)
    try:
      result = rpcServer.getServer().%(methodName)s(*newArgs)
    except:
      raise


    #result's first chars before the "-" indicate the type of the result
    #UNLESS the result is an string repr of the number, in which case
    #it is not processed
    if isinstance(result, str):
      tpe = result.split("-",1)[0]
      if tpe.isalpha():
        strToEval = "%%s(id='%%s')" %% (tpe, result)
        result = eval(strToEval)

    if mName.endswith("Create"):
      createCount += 1
      if createCount > gcThreshold:
        runGC(result.getId())
        createCount = 0


    return result
"""
  for mName in filteredMethods:
    rpcServer.getBatchServer().system.methodHelp(mName)
  
  methodsHelp = zip(filteredMethods, rpcServer.getBatchServer()())
  RPCServer.getInstance().resetBatch()

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


def runInParallel( listOfSnippets, numberOfThreads, caption=""):
  runInParallel.res = None
  for i in listOfSnippets:
    if isinstance(i,file):
      i.seek(0)
  progress = wx.ProgressDialog("Tasks completion progress",
                               caption,
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
    wx.MilliSleep(500)
    i = (len(listOfSnippets) - ThreadRunner.queue.qsize())-(threading.activeCount()-1)
    keepgoing = progress.Update( i )[0]
    if not keepgoing: 
      ThreadRunner.stop()
      break
  progress.Destroy()

  return runInParallel.res

######################################################################################

def listFuncs():
  return [ name for name in filteredMethods if name[0] != '_' ]

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

def matrixToPyRep(str):
  res = []
  str = str.strip()
  str = str[1:-1].strip() #remove the external [ ]
  rows = str.split(';')
  for i in rows:
    res.append( i.split() )

  return res
######################################################
#
#  Client implementation begins here
#
######################################################

class Z(Variable):
  def __init__(self, zStr="0", id=None):
    if id:
      Variable.__init__(self, id)
    else:
      Variable.__init__(self, _zCreate(str(zStr)).getId())

  def __add__(self, anotherZ): 
    if not isinstance(anotherZ,type(self)):
      anotherZ = Z(str(anotherZ))
    return _zAdd(self, anotherZ )
  def __iadd__(self, anotherZ): 
    self.setId( self.__add__(anotherZ).getId() )
    return self

  def __sub__(self, anotherZ): 
    if not isinstance(anotherZ,type(self)):
      anotherZ = Z(str(anotherZ))
    return _zSub(self, anotherZ)
  def __isub__(self, anotherZ): 
    self.setId( self.__sub__(anotherZ).getId() )
    return self

  def __mul__(self, anotherZ): 
    if not isinstance(anotherZ,type(self)):
      anotherZ = Z(str(anotherZ))
    return _zMul(self, anotherZ)
  def __imul__(self, anotherZ): 
    self.setId( self.__mul__(anotherZ).getId() )
    return self


  def __div__(self, anotherZ): 
    if not isinstance(anotherZ,type(self)):
      anotherZ = Z(str(anotherZ))
    return _zDiv(self, anotherZ)
  def __idiv__(self, anotherZ): 
    self.setId( self.__div__(anotherZ).getId() )
    return self


  def __mod__(self, anotherZ): 
    if not isinstance(anotherZ,type(self)):
      anotherZ = Z(str(anotherZ))
    return _zMod(self, anotherZ)
  def __imod__(self, anotherZ): 
    self.setId( self.__mod__(anotherZ).getId() )
    return self

  def __lt__(self, anotherZ):
    return (_zCompare(self, anotherZ) < 0 )
  def __le__(self, anotherZ):
    return (_zCompare(self, anotherZ) <= 0)
  def __eq__(self, anotherZ):
    return (_zCompare(self, anotherZ) == 0)
  def __ne__(self, anotherZ):
    return (_zCompare(self, anotherZ) != 0)
  def __gt__(self, anotherZ):
    return (_zCompare(self, anotherZ) > 0)
  def __ge__(self, anotherZ):
    return (_zCompare(self, anotherZ) >= 0)


  def __pow__(self, exp, mod=None):
    if not isinstance(exp,type(self)):
      exp = Z(str(exp))
    if mod:
      return modExp(self,exp,mod)
    else:
      return _zPow(self, exp)
  def __ipow__(self, exp, mod=None): 
    self.setId( self.__pow__(exp,mod).getId() )



  def __len__(self):
    return _zBitLength(self.getId())

  def __repr__(self):
#    return "%s with id %s" % (type(self),self.getId())
    return self.__str__()

  def __str__(self):
    res = _getData(self.getId())
    return res


#######################################################################


class Zn(Variable):
  def __init__(self, zIniStr="0", zMod=None, id=None):
    if id:
      Variable.__init__(self, id)
    else:
      Variable.__init__(self, _znCreate(str(zIniStr), zMod).getId())

  def __add__(self, anotherZn): 
    if not isinstance(anotherZn,type(self)):
      anotherZn = Zn(str(anotherZn))
    return _znAdd(self, anotherZn )
  def __iadd__(self, anotherZn): 
    self.setId( self.__add__(anotherZn).getId() )
    return self

  def __sub__(self, anotherZn): 
    if not isinstance(anotherZn,type(self)):
      anotherZn = Zn(str(anotherZn))
    return _znSub(self, anotherZn)
  def __isub__(self, anotherZn): 
    self.setId( self.__sub__(anotherZn).getId() )
    return self

  def __mul__(self, anotherZn): 
    if not isinstance(anotherZn,type(self)):
      anotherZn = Zn(str(anotherZn))
    return _znMul(self, anotherZn)
  def __imul__(self, anotherZn): 
    self.setId( self.__mul__(anotherZn).getId() )
    return self


  def __div__(self, anotherZn): 
    if not isinstance(anotherZn,type(self)):
      anotherZn = Zn(str(anotherZn))
    return _znDiv(self, anotherZn)
  def __idiv__(self, anotherZn): 
    self.setId( self.__div__(anotherZn).getId() )
    return self


  def __lt__(self, anotherZn):
    return (_zCompare(self, anotherZn) < 0 )
  def __le__(self, anotherZn):
    return (_zCompare(self, anotherZn) <= 0)
  def __eq__(self, anotherZn):
    return (_zCompare(self, anotherZn) == 0)
  def __ne__(self, anotherZn):
    return (_zCompare(self, anotherZn) != 0)
  def __gt__(self, anotherZn):
    return (_zCompare(self, anotherZn) > 0)
  def __ge__(self, anotherZn):
    return (_zCompare(self, anotherZn) >= 0)


  def __pow__(self, exp, mod=None):
    if not isinstance(exp,type(self)):
      exp = Zn(str(exp))
    if mod:
      return modExp(self,exp,mod)
    else:
      return _znPow(self, exp)
  def __ipow__(self, exp, mod=None): 
    self.setId( self.__pow__(exp,mod).getId() )


  def getInverse(self):
    return _znInv(self)

  def __len__(self):
    return _zBitLength(self.getId())

  def __repr__(self):
#    return "%s with id %s" % (type(self),self.getId())
    return self.__str__()

  def __str__(self):
    res = _getData(self.getId())
    return res


#######################################################################




class R(Variable):
  def __init__(self, rStr="0", id=None):
    if id:
      Variable.__init__(self, id)
    else:
      #create the instance on the server 
      Variable.__init__(self, _rCreate(str(rStr)).getId())

  def __add__(self, anotherR): 
    if not isinstance(anotherR,type(self)):
      anotherR = R(str(anotherR))
    return _rAdd(self, anotherR )
  def __iadd__(self, anotherR): 
    self.setId( self.__add__(anotherR).getId() )
    return self

  def __sub__(self, anotherR): 
    if not isinstance(anotherR,type(self)):
      anotherR = R(str(anotherR))
    return _rSub(self, anotherR)
  def __isub__(self, anotherR): 
    self.setId( self.__sub__(anotherR).getId() )
    return self

  def __mul__(self, anotherR): 
    if not isinstance(anotherR,type(self)):
      anotherR = R(str(anotherR))
    return _rMul(self, anotherR)
  def __imul__(self, anotherR): 
    self.setId( self.__mul__(anotherR).getId() )
    return self


  def __div__(self, anotherR): 
    if not isinstance(anotherR,type(self)):
      anotherR = R(str(anotherR))
    return _rDiv(self, anotherR)
  def __idiv__(self, anotherR): 
    self.setId( self.__div__(anotherR).getId() )
    return self


  def __mod__(self, anotherR): 
    if not isinstance(anotherR,type(self)):
      anotherR = R(str(anotherR))
    return _rMod(self, anotherR)
  def __imod__(self, anotherR): 
    self.setId( self.__mod__(anotherR).getId() )
    return self
 
  def __lt__(self, anotherR):
    return (_rCompare(self, anotherR) < 0 )
  def __le__(self, anotherR):
    return (_rCompare(self, anotherR) <= 0)
  def __eq__(self, anotherR):
    return (_rCompare(self, anotherR) == 0)
  def __ne__(self, anotherR):
    return (_rCompare(self, anotherR) != 0)
  def __gt__(self, anotherR):
    return (_rCompare(self, anotherR) > 0)
  def __ge__(self, anotherR):
    return (_rCompare(self, anotherR) >= 0)

  def __len__(self):
    return _rBitLength(self.getId())

  def __repr__(self):
#    return "%s with id %s" % (type(self),self.getId())
    return self.__str__()

  def __str__(self):
    res = _getData(self.getId())
    return res

  def setInnerPrecision(cls, newPrec):
    _rInnerPrec(newPrec)
  setInnerPrecision = classmethod(setInnerPrecision)

  def setOutputPrecision(cls, newPrec):
    _rOutputPrec(newPrec)
  setOutputPrecision = classmethod(setOutputPrecision)



###############################################################################


class GF(Variable):
  def __init__(self, p=2, n=1, usePrimitive=False, id=None):
    if id:
      Variable.__init__(self, id)
    else:
      if not isinstance(p,Variable):
        p = Z(str(p))
      Variable.__init__(self, _gfCreate(p,n,usePrimitive).getId())

  def getElement(self, poly="[(0,0)]"):
    if isinstance(poly, str):
      return _gfxCreate(self.getId(), poly)
    else:
      elemId = _gfxCreate(self.getId(), "[(0,0)]")
      if not isinstance(poly,Variable):
        poly = Z(str(poly))
      return _gfxSetValue(elemId, poly)


  def getProperties(self):
    return _gfGetProperties(self)




class GFx(Variable):
  def __init__(self, id):
    Variable.__init__(self, id)

  def __add__(self, anotherGF): 
    return _gfxAdd(self, anotherGF )
  def __iadd__(self, anotherGF): 
    self.setId( self.__add__(anotherGF).getId() )
    return self

  def __sub__(self, anotherGF): 
    return _gfxSub(self, anotherGF )
  def __isub__(self, anotherGF): 
    self.setId( self.__sub__(anotherGF).getId() )
    return self


  def __mul__(self, anotherGF): 
    return _gfxMul(self, anotherGF )
  def __imul__(self, anotherGF): 
    self.setId( self.__mul__(anotherGF).getId() )
    return self

  def __div__(self, anotherGF): 
    return _gfxDiv(self, anotherGF )
  def __idiv__(self, anotherGF): 
    self.setId( self.__div__(anotherGF).getId() )
    return self

  def getInverse(self):
    return _gfxInverse(self)

  def __repr__(self):
#    return "%s with id %s" % (type(self),self.getId())
    res = _getData(self)
    return res

  def __str__(self):
    return _getHRString(self)
    return res
  
  def getProperties(self):
    return _gfGetProperties(self)

  def getPBRString(self):
    return _gfxGetPBRString(self)

  def getValue(self):
    return _gfxGetValue(self)

  def setValue(self, anInteger):
    if not isinstance(anInteger,Variable):
      anInteger = Z(str(anInteger))
    return _gfxSetValue(self, anInteger)




###############################################################################

class MZ(Variable): #matrix Z

  def __init__(self, mzStr="[]", n=0, m=0, id=None):
    if id:
      Variable.__init__(self, id)

    else:
      if isinstance(mzStr, Variable):
        Variable.__init__(self,_mzCreate(repr(mzStr)).getId())
      elif n > 0 and m > 0:
        Variable.__init__(self,_mzCreateDims(n,m).getId())
      else:
        Variable.__init__(self,_mzCreate(str(mzStr)).getId())


  def __add__(self, anotherMZ): 
    return _mzAdd(self, anotherMZ )
  def __iadd__(self, anotherMZ): 
    self.setId( self.__add__(anotherMZ).getId() )
    return self

  def __sub__(self, anotherMZ): 
    return _mzSub(self, anotherMZ )
  def __isub__(self, anotherMZ): 
    self.setId( self.__sub__(anotherMZ).getId() )
    return self

  def __mul__(self, anotherMZ): 
    return _mzMul(self, anotherMZ )
  def __imul__(self, anotherMZ): 
    self.setId( self.__mul__(anotherMZ).getId() )
    return self
 
  def __div__(self, anotherMZ): 
    return _mzDiv(self, anotherMZ )
  def __idiv__(self, anotherMZ): 
    self.setId( self.__div__(anotherMZ).getId() )
    return self


  def __getitem__(self, coords):
    return _mzGetElement(self,coords[0],coords[1])
  def __setitem__(self, coords, newVal):
    return _mzSetElement(self,coords[0],coords[1], newVal)


  def __repr__(self):
    #return "%s with id %s" % (type(self),self.getId())
    res = _getData(self.getId())
    return res

  def __str__(self):
    return _getHRString(self.getId())
 
  def getTranspose(self):
    return _mzTranspose(self)

  def getDimensions(self):
    return _mzDims(self)

  def getSubMatrix(self, rangeRows=(0,1,), rangeCols=(0,1,)):
    if isinstance(rangeRows, int):
      rows = [rangeRows,1,-1]
    else:
      rows = [0,1,-1]
      for (index,e) in enumerate(rangeRows): rows[index] = e

    if isinstance(rangeCols, int):
      cols = [rangeCols, 1,-1]
    else:
      cols = [0,1,-1]
      for (index,e) in enumerate(rangeCols): cols[index] = e

    return _mzSlice(self, rows[0], rows[1], rows[2], cols[0], cols[1], cols[2] )

  def appendByRows(self, anotherMZ):
    return _mzAppendByRows(self, anotherMZ)

  def appendByColumns(self, anotherMZ):
    return _mzAppendByColumns(self, anotherMZ)



#########################################################



class MR(Variable): #matrix R

  def __init__(self, mrStr="[]", n=0, m=0, id=None):
    if id:
      Variable.__init__(self, id)
    else:
      #create the instance on the server 
      if isinstance(mrStr, Variable):
        Variable.__init__(self,_mrCreate(repr(mrStr)).getId())
      elif n > 0 and m > 0:
        Variable.__init__(self,_mrCreateDims(n,m).getId())
      else:
        Variable.__init__(self,_mrCreate(str(mrStr)).getId())


  def __add__(self, anotherMR): 
    return _mrAdd(self, anotherMR )
  def __iadd__(self, anotherMR): 
    self.setId( self.__add__(anotherMR).getId() )
    return self

  def __sub__(self, anotherMR): 
    return _mrSub(self, anotherMR )
  def __isub__(self, anotherMR): 
    self.setId( self.__sub__(anotherMR).getId() )
    return self

  def __mul__(self, anotherMR): 
    return _mrMul(self, anotherMR )
  def __imul__(self, anotherMR): 
    self.setId( self.__mul__(anotherMR).getId() )
    return self
 
  def __div__(self, anotherMR): 
    return _mrDiv(self, anotherMR )
  def __idiv__(self, anotherMR): 
    self.setId( self.__div__(anotherMR).getId() )
    return self


  def __getitem__(self, coords):
    return _mrGetElement(self,coords[0],coords[1])
  def __setitem__(self, coords, newVal):
    return _mrSetElement(self,coords[0],coords[1], newVal)


  def __repr__(self):
    #return "%s with id %s" % (type(self),self.getId())
    res = _getData(self.getId())
    return res

  def __str__(self):
    return _getHRString(self.getId())

  def getTranspose(self):
    return _mrTranspose(self)

  def getInverse(self):
    return _mrInv(self)

  def solveFor(self, b):
    return _mrSolve(self, b)

  def getDimensions(self):
    return _mrDims(self)
 
  def getSubMatrix(self, rangeRows=(0,1,), rangeCols=(0,1,)):
    if isinstance(rangeRows, int):
      rows = [rangeRows,1,-1]
    else:
      rows = [0,1,-1]
      for (index,e) in enumerate(rangeRows): rows[index] = e

    if isinstance(rangeCols, int):
      cols = [rangeCols, 1,-1]
    else:
      cols = [0,1,-1]
      for (index,e) in enumerate(rangeCols): cols[index] = e

    return _mrSlice(self, rows[0], rows[1], rows[2], cols[0], cols[1], cols[2] )

  def appendByRows(self, anotherMR):
    return _mrAppendByRows(self, anotherMR)

  def appendByColumns(self, anotherMR):
    return _mrAppendByColumns(self, anotherMR)


class MGFx(Variable): #matrix GFx

  def __init__(self, mgfxStr="[]", n=0, m=0, gf=None, id=None):
    if id:
      Variable.__init__(self, id)
    else:
      if isinstance(mgfxStr, Variable):
        Variable.__init__(self,_mgfxCreate(repr(mgfxStr), gf).getId())
      elif n > 0 and m > 0:
        Variable.__init__(self,_mgfxCreateDims(n,m,gf).getId())
      else:
        Variable.__init__(self,_mgfxCreate(str(mgfxStr),gf).getId())

  def __add__(self, anotherMGFx): 
    return _mgfxAdd(self, anotherMGFx )
  def __iadd__(self, anotherMGFx): 
    self.setId( self.__add__(anotherMGFx).getId() )
    return self

  def __sub__(self, anotherMGFx): 
    return _mgfxSub(self, anotherMGFx )
  def __isub__(self, anotherMGFx): 
    self.setId( self.__sub__(anotherMGFx).getId() )
    return self

  def __mul__(self, anotherMGFx): 
    return _mgfxMul(self, anotherMGFx )
  def __imul__(self, anotherMGFx): 
    self.setId( self.__mul__(anotherMGFx).getId() )
    return self
 
  def __div__(self, anotherMGFx): 
    return _mgfxDiv(self, anotherMGFx )
  def __idiv__(self, anotherMGFx): 
    self.setId( self.__div__(anotherMGFx).getId() )
    return self


  def __getitem__(self, coords):
    return _mgfxGetElement(self,coords[0],coords[1])
  def __setitem__(self, coords, newVal):
    return _mgfxSetElement(self,coords[0],coords[1], newVal)


  def __repr__(self):
    #return "%s with id %s" % (type(self),self.getId())
    res = _getData(self.getId())
    return res

  def __str__(self):
    return _getHRString(self.getId())

  def getTranspose(self):
    return _mgfxTranspose(self)

  def getInverse(self):
    return _mgfxInv(self)

  def solveFor(self, b):
    return _mgfxSolve(self, b)

  def getDimensions(self):
    return _mgfxDims(self)
 
  def getSubMatrix(self, rangeRows=(0,1,), rangeCols=(0,1,)):
    if isinstance(rangeRows, int):
      rows = [rangeRows,1,-1]
    else:
      rows = [0,1,-1]
      for (index,e) in enumerate(rangeRows): rows[index] = e

    if isinstance(rangeCols, int):
      cols = [rangeCols, 1,-1]
    else:
      cols = [0,1,-1]
      for (index,e) in enumerate(rangeCols): cols[index] = e

    return _mgfxSlice(self, rows[0], rows[1], rows[2], cols[0], cols[1], cols[2] )

  def appendByRows(self, anotherMGFx):
    return _mgfxAppendByRows(self, anotherMGFx)

  def appendByColumns(self, anotherMGFx):
    return _mgfxAppendByColumns(self, anotherMGFx)







class MZn(Variable): #matrix Zn

  def __init__(self, mz_nStr="[]", n=0, m=0, mod=None, id=None):
    if id:
      Variable.__init__(self, id)
    else:
      if isinstance(mz_nStr, Variable):
        Variable.__init__(self,_mz_nCreate(repr(mz_nStr), mod).getId())
      elif n > 0 and m > 0:
        Variable.__init__(self,_mz_nCreateDims(n,m,mod).getId())
      else:
        Variable.__init__(self,_mz_nCreate(str(mz_nStr),mod).getId())


  def __add__(self, anotherMZn): 
    return _mz_nAdd(self, anotherMZn )
  def __iadd__(self, anotherMZn): 
    self.setId( self.__add__(anotherMZn).getId() )
    return self

  def __sub__(self, anotherMZn): 
    return _mz_nSub(self, anotherMZn )
  def __isub__(self, anotherMZn): 
    self.setId( self.__sub__(anotherMZn).getId() )
    return self

  def __mul__(self, anotherMZn): 
    return _mz_nMul(self, anotherMZn )
  def __imul__(self, anotherMZn): 
    self.setId( self.__mul__(anotherMZn).getId() )
    return self
 
  def __div__(self, anotherMZn): 
    return _mz_nDiv(self, anotherMZn )
  def __idiv__(self, anotherMZn): 
    self.setId( self.__div__(anotherMZn).getId() )
    return self


  def __getitem__(self, coords):
    return _mz_nGetElement(self,coords[0],coords[1])
  def __setitem__(self, coords, newVal):
    return _mz_nSetElement(self,coords[0],coords[1], newVal)


  def __repr__(self):
    #return "%s with id %s" % (type(self),self.getId())
    res = _getData(self.getId())
    return res

  def __str__(self):
    return _getHRString(self.getId())

  def getTranspose(self):
    return _mz_nTranspose(self)

  def getInverse(self):
    return _mz_nInv(self)

  def solveFor(self, b):
    return _mz_nSolve(self, b)

  def getDimensions(self):
    return _mz_nDims(self)
 
  def getSubMatrix(self, rangeRows=(0,1,), rangeCols=(0,1,)):
    if isinstance(rangeRows, int):
      rows = [rangeRows,1,-1]
    else:
      rows = [0,1,-1]
      for (index,e) in enumerate(rangeRows): rows[index] = e

    if isinstance(rangeCols, int):
      cols = [rangeCols, 1,-1]
    else:
      cols = [0,1,-1]
      for (index,e) in enumerate(rangeCols): cols[index] = e

    return _mz_nSlice(self, rows[0], rows[1], rows[2], cols[0], cols[1], cols[2] )

  def appendByRows(self, anotherMZn):
    return _mz_nAppendByRows(self, anotherMZn)

  def appendByColumns(self, anotherMZn):
    return _mz_nAppendByColumns(self, anotherMZn)





#########################################################




import sys
if __name__ == '__main__':
  sys.exit("Not meant to be used standalone")
  
  


