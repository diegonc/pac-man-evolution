.PHONY: all test

LDFLAGS=-lpthread

OBJS=../../server/EstructuralPasillo.o \
     ../../server/EstructuralUnitario.o \
     ../../server/Posicion.o \
     ../../server/MapImpSet.o \
     ../../server/PaqueteInit.o \
     ../../server/Paquete.o \
     ../../server/Comestible.o \
     ../../server/OutputBitStream.o \
     ../../server/InputBitStream.o \
     ../../server/Jugador.o \
     ../../server/Personaje.o \
     ../../server/PacMan.o \
     ../../server/Direccion.o \
     ../../server/ComestibleFactory.o \
     ../../server/PowerUp.o \
     ../../common/mutex.o \
     ../../common/bloqueo.o \
     ../../common/observable.o

all: test

test_pinit: $(OBJS) main.o
	g++ -o $@ $(LDFLAGS) $^

test: test_pinit
	./$^

