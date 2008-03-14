
## Makefile.am -- Process this file with automake to produce Makefile.in

##  robado del autobook - seccion 5.1

noinst_LIBRARIES = libpme-editor.a

libpme_editor_a_SOURCES = \
	bif_este.cpp \
	bif_este.h \
	bif_norte.cpp \
	bif_norte.h \
	bif_oeste.cpp \
	bif_oeste.h \
	bif_sur.cpp \
	bif_sur.h \
	bonus.cpp \
	bonus.h \
	casa_este.cpp \
	casa_este.h \
	casa_fantasmas.cpp \
	casa_fantasmas.h \
	casa_norte.cpp \
	casa_norte.h \
	casa_oeste.cpp \
	casa_oeste.h \
	casa_sur.cpp \
	casa_sur.h \
	casillero.cpp \
	casillero.h \
	componente.cpp \
	componente.h \
	cruce.cpp \
	cruce.h \
	dato_vertice.cpp \
	dato_vertice.h \
	definiciones.h \
	elemento.cpp \
	elemento.h \
	esq_este.cpp \
	esq_este.h \
	esq_norte.cpp \
	esq_norte.h \
	esq_oeste.cpp \
	esq_oeste.h \
	esq_sur.cpp \
	esq_sur.h \
	estructural.cpp \
	estructural.h \
	fab_elementos.cpp \
	fab_elementos.h \
	mapa.cpp \
	mapa.h \
	modelo.cpp \
	modelo.h \
	modificador.cpp \
	modificador.h \
	mundo.cpp \
	mundo.h \
	nivel.cpp \
	nivel.h \
	obj_nulo.h \
	pas_horiz.cpp \
	pas_horiz.h \
	pas_vert.cpp \
	pas_vert.h \
	portal.cpp \
	portal.h \
	portal_este.cpp \
	portal_este.h \
	portal_norte.cpp \
	portal_norte.h \
	portal_oeste.cpp \
	portal_oeste.h \
	portal_sur.cpp \
	portal_sur.h \
	power_up.cpp \
	power_up.h \
	punto.cpp \
	punto.h \
	recorredor_grafo.h \
	salida.cpp \
	salida.h

#libpme_editor_la_LDFLAGS = -static

libpme_editor_a_CPPFLAGS = \
	-DAPP_DATA_DIR="\"$(datadir)/map_editor\"" \
	-DAPP_DATA_DIR_S="\"$(datadir)/map_editor/\"" \
	-I@top_srcdir@/common

#libpme_editor_a_LIBADD = \
#	$(top_builddir)/common/tinyxml/libtinyxml.a

CLEANFILES = *~
