from Client import *
def getKeyPair(keySize):
  " Returns the pair (public, private) keys"
  (p,q) = runInParallel(["result=getPrime(%d)" % keySize ]*2,2, "Generating prime pair (p,q)")
  n = p*q
  phi = (p-1)*(q-1)
  while True:
    e = getRandomZLessThan(n)
    if str(gcd(e,phi)) == '1':
      break
  d = modInverse(e,phi)
  return ((e,n) , (d,n))

def cypher(key, msg):
  e = key[0]
  n = key[1]
  return modExp(msg,e,n)

def decypher(key, cyphertext):
  d = key[0]
  n = key[1]
  return modExp(cyphertext,d,n)
