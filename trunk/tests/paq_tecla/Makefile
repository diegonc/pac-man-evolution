.PHONY: all test clean

LDFLAGS=-lpthread

CXXFLAGS=-ggdb

TARGET=test-ptecla

OBJS=main.o \
     ../../server/EstructuralPasillo.o \
     ../../server/EstructuralUnitario.o \
     ../../server/Posicion.o \
     ../../server/MapImpSet.o \
     ../../server/ModeloServidor.o \
     ../../server/PaqueteTecla.o \
     ../../server/Paquete.o \
     ../../server/Comestible.o \
     ../../server/OutputBitStream.o \
     ../../server/InputBitStream.o \
     ../../server/Jugador.o \
     ../../server/Personaje.o \
     ../../server/PacMan.o \
     ../../server/Fantasma.o \
     ../../server/reloj.o \
     ../../server/Direccion.o \
     ../../server/ComestibleFactory.o \
     ../../server/PowerUp.o \
     ../../server/KeyOp.o \
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
