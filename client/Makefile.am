
# Makefile.am -- Process this file with automake to produce Makefile.in

#  robado del autobook - seccion 5.1

bin_PROGRAMS = pme-client

pme_client_SOURCES = \
	Aplicacion.cpp \
	Aplicacion.h \
	AplicacionGrafica.cpp \
	AplicacionGrafica.h \
	Cargadorde3DS.cpp \
	Cargadorde3DS.h \
	CargadordeTexturas.cpp \
	CargadordeTexturas.h \
	ColeccionObjetos.cpp \
	ColeccionObjetos.h \
	Escenario.cpp \
	Escenario.h \
	EstadoAplicacion.h \
	JugadorLocal.cpp \
	JugadorLocal.h \
	ModeladorObjetos.cpp \
	ModeladorObjetos.h \
	ModeloServidor.cpp \
	ModeloServidor.h \
	ObjetoVisual.h \
	OperacionInit.cpp \
	OperacionInit.h \
	OperacionStart.cpp \
	OperacionStart.h \
	OperacionStatus.cpp \
	OperacionStatus.h \
	PaqueteInit.cpp \
	PaqueteInit.h \
	PaqueteStart.cpp \
	PaqueteStart.h \
	PaqueteStatus.cpp \
	PaqueteStatus.h \
	PaqueteTecla.cpp \
	PaqueteTecla.h \
	PosicionGraf.h \
	SelectorCamara.cpp \
	SelectorCamara.h \
	main.cpp

##pme_client_CPPFLAGS = @GTK_CFLAGS@
pme_client_CPPFLAGS = \
	-I@top_srcdir@/common

pme_client_LDADD = \
	$(top_builddir)/common/server/libpme-server.a \
	$(top_builddir)/common/editor/libpme-editor.a \
	$(top_builddir)/common/common/libpme-common.a \
	$(top_builddir)/common/tinyxml/libtinyxml.a

CLEANFILES = *~
