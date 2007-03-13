from singletonmixin import Singleton
from xmlrpclib import ServerProxy

class RPCServer(Singleton, ServerProxy):

  def __init__(self, serverURL, **rpcServerExtra):
    ServerProxy.__init__(self, serverURL, **rpcServerExtra) 


  
