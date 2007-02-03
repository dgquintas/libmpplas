LIBNUMTH_LIB = ../../../lib 
LIBNUMTH_HEADERS = ../../headers
SOURCES = main.cpp calculadora.cc mlex.cc gram_loader.cc gram_lex.cc \
          panelFunciones.cpp interfazImpl.cpp interfaz.cpp 
HEADERS = calculadora.h  gram_loader.h  interfazImpl.h  mlex.h \
          parser.h gram_lex.h interfaz.h lex.h panelFunciones.h 
INCLUDEPATH += $${LIBNUMTH_HEADERS}
unix:LIBS += -lnumth -L$${LIBNUMTH_LIB}
CONFIG = qt warn_on debug numth
TARGET = Calculadora

