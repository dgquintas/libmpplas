from matplotlib.pylab import *
from Client import *

def piEuler(x):
	numPrimes = 0
	for i in xrange(x):
		if isPrime(i):
			numPrimes += 1
	return numPrimes

t1 = arange(2,1000,50)
xlabel(r"$n$")
ylabel(r"$\pi(n)$")
plot(t1, map(lambda x: piEuler(x), t1), 'ro-', t1, t1/log(t1), 'bx-')

