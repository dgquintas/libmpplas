# encoding: utf-8

#
# $Id$
#


import Client
from sys import argv

if len(argv) > 1:
  globals().update( Client.initializeClient(argv[1]) )
else:
  globals().update( Client.initializeClient() )
if Client.checkForUpdates():
  #updated version available
  globals()['updated'] = True
else:
  globals()['updated'] = False 
  
def runGC():
  global clientId

  usedSlots = []
  for inst in globals().values():
    if isinstance(inst, Variable):
      usedSlots.append(inst.getId())

  print usedSlots
  RPCServer.getInstance().getServer()._runGC(clientId, usedSlots)


import matplotlib
matplotlib.interactive(True)
matplotlib.use('WXAgg') 
from matplotlib.pylab import *
