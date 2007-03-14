from Client import *
p = getPrime(10)
q = getPrime(10)
n = p*q
phi = (p-1)*(q-1)
while True:
	e = randomZLessThan(n)
	if gcd(e,phi) == 1:
		break

d = modInverse(e,phi)
m = 123
c = modExp(m,e,n)
print modExp(c,d,n)
