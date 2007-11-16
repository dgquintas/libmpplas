from matplotlib.pylab import *
from Client import *

def piEuler(last, first=3, initialCount=1):
  assert(last >= first)
  numPrimes = initialCount
  if not (first & 0x1): #even
    first += 1
  for i in xrange(first,last,2):
    if isPrime(Z(i)):
      numPrimes += 1

  return numPrimes

t1 = arange(100,1001,100)
piEulerResList = []
piEulerResList.append( piEuler(t1[0]) )
for i in xrange(1,len(t1)):
  piEulerResList.append( piEuler(first = t1[i-1]+1, last = t1[i], initialCount = piEulerResList[-1]) )


xlabel(r"$n$")
ylabel(r"$\pi(n)$")
plot(t1, piEulerResList, 'ro-', label=r"True pi(n)")
plot(t1, t1/log(t1), 'bx-', label=r"n/log(n) approx.")
legend()



