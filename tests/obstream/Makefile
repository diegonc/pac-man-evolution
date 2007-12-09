.PHONY: all test clean

LDFLAGS=-lpthread

CXXFLAGS=-ggdb

TARGET=test-obs

OBJS=main.o \
     ../../server/EstructuralPasillo.o \
     ../../server/EstructuralUnitario.o \
     ../../server/EstructuralCasaFantasma.o \
     ../../server/Posicion.o \
     ../../server/MapImpSet.o \
     ../../server/PaqueteInit.o \
     ../../server/PaqueteTecla.o \
     ../../server/Paquete.o \
     ../../server/KeyOp.o \
     ../../server/ModeloServidor.o \
     ../../server/Comestible.o \
     ../../server/OutputBitStream.o \
     ../../server/InputBitStream.o \
     ../../server/Jugador.o \
     ../../server/Personaje.o \
     ../../server/PacMan.o \
     ../../server/Fantasma.o \
     ../../server/Direccion.o \
     ../../server/ComestibleFactory.o \
     ../../server/PowerUp.o \
     ../../server/reloj.o \
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
	rm -vf $(OBJS) $(TARGET)
