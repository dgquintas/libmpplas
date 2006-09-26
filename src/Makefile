
PROGRAM = libnumth.so

SHELL = /bin/bash
CC = g++

STDCFLAGS = -ggdb3 -finline-functions -c -O3 -W -Wall -Werror -DARCH=x86 -fPIC
#STDCFLAGS = -ggdb3 -finline-functions -c -O0 -W -DARCH=x86 -fPIC
INCLUDES = -I./nucleo/ -I.
LIBS = 

#${PROGRAM}: Z.o mp.o R.o Z_n.o Random.o	Primos.o test.o Funciones.o GCD.o Potencia.o RedModular.o Hash.o SimbolosLegendre.o CRT.o Semillero.o Factor.o
#	$(CC) -ggdb3 -o ${PROGRAM} Z.o mp.o R.o Z_n.o Random.o	Primos.o test.o Funciones.o GCD.o Potencia.o RedModular.o Hash.o SimbolosLegendre.o CRT.o Semillero.o Factor.o $(LIBS)
${PROGRAM}: Z.o mp.o R.o Z_n.o Random.o	Primos.o Funciones.o GCD.o Potencia.o RedModular.o Hash.o SimbolosLegendre.o CRT.o Semillero.o Factor.o Perfil.o LCM.o Trascendentes.o
	$(CC) -ggdb3 -shared -fPIC -o ${PROGRAM} Z.o mp.o R.o Z_n.o Random.o Primos.o Funciones.o GCD.o Potencia.o RedModular.o Hash.o SimbolosLegendre.o CRT.o Semillero.o Factor.o Perfil.o LCM.o Trascendentes.o $(LIBS)

#test.o: test.cpp
#	$(CC) $(STDCFLAGS) $(INCLUDES) test.cpp

Funciones.o: Funciones.h Funciones.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) Funciones.cpp

Factor.o: Factor.h Factor.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) Factor.cpp

Perfil.o: Perfil.h Perfil.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) Perfil.cpp

Semillero.o: Semillero.h Semillero.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) Semillero.cpp

Random.o: Random.h Random.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) Random.cpp

Primos.o: Primos.h Primos.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) Primos.cpp

GCD.o: GCD.h GCD.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) GCD.cpp

LCM.o: LCM.h LCM.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) LCM.cpp

Potencia.o: Potencia.h Potencia.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) Potencia.cpp

CRT.o: CRT.h CRT.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) CRT.cpp

Trascendentes.o: Trascendentes.h Trascendentes.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) Trascendentes.cpp


RedModular.o: RedModular.h RedModular.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) RedModular.cpp

SimbolosLegendre.o: SimbolosLegendre.h SimbolosLegendre.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) SimbolosLegendre.cpp

Hash.o: Hash.h Hash.cpp
	$(CC) $(STDCFLAGS) $(INCLUDES) Hash.cpp

Z.o: Z.cpp Z.h
	$(CC) $(STDCFLAGS) $(INCLUDES) Z.cpp

Z_n.o: Z_n.cpp Z_n.h
	$(CC) $(STDCFLAGS) $(INCLUDES) Z_n.cpp

R.o: R.cpp R.h
	$(CC) $(STDCFLAGS) $(INCLUDES) R.cpp

mp.o: mp.cpp mp.h 
	$(CC) $(STDCFLAGS) $(INCLUDES) mp.cpp

clean:
	rm -f ${PROGRAM} *.o *~ core
	
