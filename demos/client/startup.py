# encoding: utf-8

#
# $Id$
#


import Client
from sys import argv
from pprint import pprint

if len(argv) > 1:
  globals().update( Client.initializeClient(argv[1]) )
else:
  globals().update( Client.initializeClient() )
if Client.checkForUpdates():
  #updated version available
  globals()['updated'] = True
else:
  globals()['updated'] = False 
 
#the "grace" is a single varId that is
#to be kept from the gc.
#the reason why is because the GC is performed just after a 
#create operation. If such creation hasn't been asigned to any
#variable, it'd be gc'd, but then the interpreter wouldn't 
#be able to show it's value, raising an exception
def _runGC(grace):
  global clientId

  usedSlots = [grace]
  for inst in globals().values():
    if isinstance(inst, Variable) and inst.getId() not in usedSlots:
      usedSlots.append(inst.getId())

  RPCServer.getInstance().getServer().__runGC(clientId, usedSlots)

Client.runGC = _runGC

def runFile(fileName):
  f = open(fileName, 'r')
  exec f in globals() 

import matplotlib
matplotlib.interactive(True)
matplotlib.use('WXAgg') 
from matplotlib.pylab import *
