gf = GF(2,4)
m = MGFx("[12 34; 67 98]",gf=gf)
result = m.getInverse()
print result
