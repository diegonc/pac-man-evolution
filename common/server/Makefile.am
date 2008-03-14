
## Makefile.am -- Process this file with automake to produce Makefile.in

##  robado del autobook - seccion 5.1

noinst_LIBRARIES = libpme-server.a

libpme_server_a_SOURCES = \
	BufferReader.h \
	Cliente.cpp \
	Cliente.h \
	Comestible.cpp \
	Comestible.h \
	ComestibleFactory.cpp \
	ComestibleFactory.h \
	ComparadorPosicion.h \
	Direccion.cpp \
	Direccion.h \
	EscritorCliente.cpp \
	EscritorCliente.h \
	EscuchadorCliente.cpp \
	EscuchadorCliente.h \
	EstructuralCasaFantasma.cpp \
	EstructuralCasaFantasma.h \
	EstructuralPasillo.cpp \
	EstructuralPasillo.h \
	EstructuralUnitario.cpp \
	EstructuralUnitario.h \
	EstructuralUnitarioFactory.cpp \
	EstructuralUnitarioFactory.h \
	Fantasma.cpp \
	Fantasma.h \
	Frutita.h \
	InputBitStream.cpp \
	InputBitStream.h \
	Jugador.cpp \
	Jugador.h \
	MapImpSet.cpp \
	MapImpSet.h \
	MapaBajoNivel.h \
	MemoryReader.cpp \
	MemoryReader.h \
	ModeloCommon.cpp \
	ModeloCommon.h \
	MundoBajoNivel.h \
	MundoBasicImp.cpp \
	MundoBasicImp.h \
	NovedadComestible.cpp \
	NovedadComestible.h \
	Operacion.h \
	OperacionNula.h \
	OutputBitStream.cpp \
	OutputBitStream.h \
	PacMan.cpp \
	PacMan.h \
	Paquete.cpp \
	Paquete.h \
	PaqueteInitCommon.cpp \
	PaqueteInitCommon.h \
	PaqueteMensajeCommon.cpp \
	PaqueteMensajeCommon.h \
	PaqueteQuitCommon.cpp \
	PaqueteQuitCommon.h \
	PaqueteStartCommon.cpp \
	PaqueteStartCommon.h \
	PaqueteStatusCommon.cpp \
	PaqueteStatusCommon.h \
	PaqueteStopCommon.cpp \
	PaqueteStopCommon.h \
	PaqueteTeclaCommon.cpp \
	PaqueteTeclaCommon.h \
	Personaje.cpp \
	Personaje.h \
	Posicion.cpp \
	Posicion.h \
	PowerUp.cpp \
	PowerUp.h \
	Quesito.h \
	SocketReader.cpp \
	SocketReader.h

libpme_server_a_CPPFLAGS = \
	-I@top_srcdir@ \
	-I@top_srcdir@/common

#libpme_server_a_LDFLAGS = -static

#libpme_server_a_LDADD = \
#	$(top_builddir)/common/common/libpme-common.la \
#	$(top_builddir)/common/tinyxml/libtinyxml.la

CLEANFILES = *~
