.PHONY: all test clean

LDFLAGS=-lpthread

CXXFLAGS=-ggdb -I../..

TARGET=test-client

SERVER_DIR=../../server
#SERVER_O=$(wildcard $(SERVER_DIR)/*.o)
SERVER_O=Paquete.o \
	 SocketReader.o \
	 InputBitStream.o \
	 OutputBitStream.o \
	 PaqueteInit.o \
	 PaqueteStart.o \
	 PaqueteStatus.o \
	 PaqueteQuit.o \
	 PaqueteTecla.o \
	 PaqueteMensaje.o \
	 KeyOp.o \
	 Jugador.o \
	 ModeloServidor.o \
	 MapImpSet.o \
	 Direccion.o \
	 Posicion.o \
	 reloj.o \
	 EstructuralUnitario.o \
	 EstructuralPasillo.o \
	 EstructuralCasaFantasma.o \
	 Fantasma.o \
	 Personaje.o \
	 PacMan.o \
	 Comestible.o \
	 ComestibleFactory.o \
	 PowerUp.o


COMMON_DIR=../../common
COMMON_O=thread.o \
	 mutex.o \
	 socket.o \
	 client_socket.o \
	 bloqueo.o \
	 observable.o

TESTCLIENT_O=main.o Cliente.o

OBJS=$(TESTCLIENT_O)
OBJS+=$(patsubst %, $(SERVER_DIR)/%,$(SERVER_O))
OBJS+=$(patsubst %, $(COMMON_DIR)/%,$(COMMON_O))


     #../../server/EstructuralPasillo.o \
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
