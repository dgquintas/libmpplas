from singletonmixin import Singleton
from xmlrpclib import ServerProxy,MultiCall


class RPCServer(Singleton):

  def __init__(self, serverURL, **rpcServerExtra):
    self.__interactiveRPC = self._RPCServerProxy(serverURL, **rpcServerExtra)
    self.__batchRPC = self._RPCMultiCall(self.__interactiveRPC);

    self.__useBatch = False

  def getServer(self):
    if self.isBatch():
      return self.getBatchServer();
    else:
      return self.getInteractiveServer()

  def getInteractiveServer(self):
    return self.__interactiveRPC;

  def getBatchServer(self):
    return self.__batchRPC;

  def setBatch(self, useBatch):
    if useBatch:
      self.__batchRPC = self._RPCMultiCall(self.__interactiveRPC);
    self.__useBatch = useBatch;

  def isBatch(self):
    return self.__useBatch

  def resetBatch(self):
    self.__batchRPC = self._RPCMultiCall(self.__interactiveRPC)


  #############################################
  # Private inner classes
  ##############################
  class _RPCServerProxy(ServerProxy):
    def __init__(self, serverURL, **rpcServerExtra):
      ServerProxy.__init__(self, serverURL, **rpcServerExtra) 

  class _RPCMultiCall(MultiCall):
    def __init__(self, serverProxy):
      MultiCall.__init__(self, serverProxy)


  
