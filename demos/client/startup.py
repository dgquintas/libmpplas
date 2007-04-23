from Client import *
globals().update( initializeClient() )

import matplotlib
matplotlib.interactive(True)
matplotlib.use('WXAgg') 
from matplotlib.pylab import *
