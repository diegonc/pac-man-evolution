.PHONY: all test clean

LDFLAGS=-lpthread

CXXFLAGS=-ggdb -I../..

TARGET=test-pstart

OBJS=main.o test_pstart.o \
     ../../server/EstructuralPasillo.o \
     ../../server/EstructuralUnitario.o \
     ../../server/EstructuralCasaFantasma.o \
     ../../server/Posicion.o \
     ../../server/MapImpSet.o \
     ../../server/PaqueteInit.o \
     ../../server/PaqueteTecla.o \
     ../../server/PaqueteMensaje.o \
     ../../server/PaqueteStart.o \
     ../../server/Paquete.o \
     ../../server/Comestible.o \
     ../../server/KeyOp.o \
     ../../server/OutputBitStream.o \
     ../../server/ModeloServidor.o \
     ../../server/InputBitStream.o \
     ../../server/Jugador.o \
     ../../server/Fantasma.o \
     ../../server/reloj.o \
     ../../server/Personaje.o \
     ../../server/PacMan.o \
     ../../server/Direccion.o \
     ../../server/ComestibleFactory.o \
     ../../server/PowerUp.o \
     ../../common/mutex.o \
     ../../common/bloqueo.o \
     ../../common/observable.o \
     ../../common/thread.o

all: test

$(TARGET): $(OBJS)
	g++ -o $@ $(CXXFLAGS) $(LDFLAGS) $^

test: $(TARGET)
	@./$^

clean:
	@rm -vf $(OBJS) $(TARGET)
