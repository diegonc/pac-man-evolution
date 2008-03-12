
## Makefile.am -- Process this file with automake to produce Makefile.in

##  robado del autobook - seccion 5.1

noinst_LIBRARIES = libpme-common.a

libpme_common_a_SOURCES = \
	arco.h \
	bloqueo.cpp \
	bloqueo.h \
	client_socket.cpp \
	client_socket.h \
	comparador.h \
	contador.h \
	errores.cpp \
	errores.h \
	evento.cpp \
	evento.h \
	grafo.h \
	mutex.cpp \
	mutex.h \
	observable.cpp \
	observable.h \
	observable.lo \
	observable.o \
	observador.h \
	server_socket.cpp \
	server_socket.h \
	smart_pointer.h \
	smart_pointer_arrays.h \
	socket.cpp \
	socket.h \
	thread.cpp \
	thread.h \
	vertice.h \
	wrapper.h \
	ConfValue.cpp \
	ConfValue.h \
	Configuracion.cpp \
	Configuracion.h

libpme_common_a_CPPFLAGS = \
	-I$(top_srcdir)/common

#libpme_common_la_LDFLAGS = -static

CLEANFILES = *~
