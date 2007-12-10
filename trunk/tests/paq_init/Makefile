.PHONY: all test clean

LDFLAGS=-lpthread

CXXFLAGS=-ggdb

TARGET=test-pinit

OBJS=main.o \
     ../../server/EstructuralPasillo.o \
     ../../server/EstructuralUnitario.o \
     ../../server/EstructuralCasaFantasma.o \
     ../../server/Posicion.o \
     ../../server/MapImpSet.o \
     ../../server/PaqueteInit.o \
     ../../server/PaqueteTecla.o \
     ../../server/PaqueteStatus.o \
     ../../server/PaqueteMensaje.o \
     ../../server/PaqueteStart.o \
     ../../server/PaqueteStop.o \
     ../../server/PaqueteQuit.o \
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
