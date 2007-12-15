
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
	DataStore.h \
	KeyOp.cpp \
	KeyOp.h \
	Main.cpp \
	MapImpSet.h \
	ModeloServidor.cpp \
	ModeloServidor.h \
	PaqueteInit.cpp \
	PaqueteInit.h \
	PaqueteStart.cpp \
	PaqueteStart.h \
	PaqueteStatus.cpp \
	PaqueteStatus.h \
	PaqueteTecla.cpp \
	PaqueteTecla.h \
	Servidor.cpp \
	Servidor.h \
	reloj.cpp \
	reloj.h \
	traductor.cpp \
	traductor.h

pme_server_CPPFLAGS = \
	-I@top_srcdir@/common

pme_server_LDADD = \
	$(top_builddir)/common/server/libpme-server.a \
	$(top_builddir)/common/editor/libpme-editor.a \
	$(top_builddir)/common/common/libpme-common.a \
	$(top_builddir)/common/tinyxml/libtinyxml.a 

CLEANFILES = *~
