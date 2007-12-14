
## Makefile.am -- Process this file with automake to produce Makefile.in

##  robado del autobook - seccion 5.1

SUBDIRS = tinyxml

noinst_LTLIBRARIES = libpme-common.la

libpme_common_la_SOURCES = \
	arco.h \
	bloqueo.cpp \
	bloqueo.h \
	client_socket.cpp \
	client_socket.h \
	comparador.h \
	contador.h \
	evento.cpp \
	evento.h \
	grafo.h \
	mutex.cpp \
	mutex.h \
	observable.cpp \
	observable.h \
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
	wrapper.h 

libpme_common_la_LDFLAGS = -static

libpme_common_la_LIBADD = tinyxml/libtinyxml.la

CLEANFILES = *~
