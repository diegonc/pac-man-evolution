
# Makefile.am -- Process this file with automake to produce Makefile.in

#  robado del autobook - seccion 5.1

bin_PROGRAMS = pme-client

pme_client_SOURCES = \
	Abecedario.cpp \
	Abecedario.h \
	Aplicacion.cpp \
	Aplicacion.h \
	AplicacionGrafica.cpp \
	AplicacionGrafica.h \
	BufferMensajes.cpp \
	BufferMensajes.h \
	Cargadorde3DS.cpp \
	Cargadorde3DS.h \
	CargadordeTexturas.cpp \
	CargadordeTexturas.h \
	CreadorPaquete.cpp \
	ColeccionObjetos.cpp \
	ColeccionObjetos.h \
	ConfCliente.cpp \
	ConfCliente.h \
	Escenario.cpp \
	Escenario.h \
	EstadoAplicacion.h \
	JugadorLocal.cpp \
	JugadorLocal.h \
	MiniMapa.cpp \
	MiniMapa.h \
	ModeladorObjetos.cpp \
	ModeladorObjetos.h \
	ModeloServidor.cpp \
	ModeloServidor.h \
	NotificadorMensajes.cpp \
	NotificadorMensajes.h \
	ObjetoVisual.h \
	OperacionInit.cpp \
	OperacionInit.h \
	OperacionMensaje.cpp \
	OperacionMensaje.h \
	OperacionStart.cpp \
	OperacionStart.h \
	OperacionStatus.cpp \
	OperacionStatus.h \
	OperacionStop.cpp \
	OperacionStop.h \
	OperacionQuit.cpp \
	OperacionQuit.h \
	PaqueteInit.cpp \
	PaqueteInit.h \
	PaqueteMensaje.h \
	PaqueteMensaje.cpp \
	PaqueteStart.cpp \
	PaqueteStart.h \
	PaqueteStatus.cpp \
	PaqueteStatus.h \
	PaqueteStop.h \
	PaqueteStop.cpp \
	PaqueteTecla.cpp \
	PaqueteTecla.h \
	PaqueteQuit.cpp \
	PaqueteQuit.h \
	PosicionGraf.h \
	SelectorCamara.cpp \
	SelectorCamara.h \
	Sonidos.cpp \
	Sonidos.h \
	main.cpp \
	$(top_srcdir)/pme-server/KeyOp.cpp \
	$(top_srcdir)/pme-server/KeyOp.h

pme_client_EXTRA_DIST = \
	ABC.bmp \
	Icon.bmp \
	Letra.bmp \
	Mapa.bmp \
	banana.3DS \
	banana.bmp \
	cerecita.3DS \
	cerecita.bmp \
	fantasma.3DS \
	fantasma.bmp \
	font.bmp \
	pacman.3DS \
	pacman.bmp \
	pared.bmp \
	pastilla.3DS \
	pastilla.bmp \
	piso.bmp \
	powerup.3DS \
	powerup.bmp \
	textura.bmp \
	MiniMap

##pme_client_CPPFLAGS = @GTK_CFLAGS@
pme_client_CPPFLAGS = \
	-DDEBUG -ggdb \
	-I@top_srcdir@/common

pme_client_LDADD = \
	$(top_builddir)/common/server/libpme-server.a \
	$(top_builddir)/common/editor/libpme-editor.a \
	$(top_builddir)/common/common/libpme-common.a \
	$(top_builddir)/common/tinyxml/libtinyxml.a \
	-lSDL -lGL -lGLU -lSDL_mixer

CLEANFILES = *~
