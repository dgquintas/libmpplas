# encoding: utf-8

#
# $Id$
#


import Client
globals().update( Client.initializeClient() )
if Client.checkForUpdates():
  #updated version available
  globals()['updated'] = True
else:
  globals()['updated'] = False 
  
  

import matplotlib
matplotlib.interactive(True)
matplotlib.use('WXAgg') 
from matplotlib.pylab import *
