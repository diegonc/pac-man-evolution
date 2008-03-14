
## Makefile.am -- Process this file with automake to produce Makefile.in

##  robado del autobook - seccion 5.1

bin_PROGRAMS = pme-server

pme_server_SOURCES = \
	App.cpp \
	App.h \
	AvisadorNovedades.cpp \
	AvisadorNovedades.h \
	ClientPool.cpp \
	ClientPool.h \
	CreadorPaquete.cpp \
	KeyOp.cpp \
	KeyOp.h \
	Main.cpp \
	MessageDispatcher.cpp \
	MessageDispatcher.h \
	ModeloServidor.cpp \
	ModeloServidor.h \
	OperacionMensaje.cpp \
	OperacionMensaje.h \
	PaqueteInit.cpp \
	PaqueteInit.h \
	PaqueteMensaje.cpp \
	PaqueteMensaje.h \
	PaqueteStart.cpp \
	PaqueteStart.h \
	PaqueteStatus.cpp \
	PaqueteStatus.h \
	PaqueteStop.cpp \
	PaqueteStop.h \
	PaqueteTecla.cpp \
	PaqueteTecla.h \
	PaqueteQuit.cpp \
	PaqueteQuit.h \
	Servidor.cpp \
	Servidor.h \
	reloj.cpp \
	reloj.h \
	traductor.cpp \
	traductor.h

pkgdata_DATA = \
	pme-server.conf

pme_server_CPPFLAGS = \
	-I@top_srcdir@/common

pme_server_LDADD = \
	$(top_builddir)/common/server/libpme-server.a \
	$(top_builddir)/common/editor/libpme-editor.a \
	$(top_builddir)/common/common/libpme-common.a \
	$(top_builddir)/common/tinyxml/libtinyxml.a 

CLEANFILES = *~
