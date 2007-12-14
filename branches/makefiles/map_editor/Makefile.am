
# Makefile.am -- Process this file with automake to produce Makefile.in

#  robado del autobook - seccion 5.1

noinst_LTLIBRARIES = libpme-editor.la

bin_PROGRAMS = pme-editor

libpme_editor_la_SOURCES = \
	mundo.cpp \
	mundo.h \
	traductor.cpp \
	traductor.h \
	casillero.cpp \
	casillero.h \
	nivel.cpp \
	nivel.h \
	mapa.cpp \
	mapa.h \
	power_up.cpp \
	power_up.h \
	bonus.cpp \
	bonus.h \
	elemento.cpp \
	elemento.h \
	estructural.cpp \
	estructural.h \
	modelo.cpp \
	modelo.h \
	modificador.cpp \
	modificador.h \
	salida.cpp \
	salida.h \
	dato_vertice.cpp \
	dato_vertice.h \
	fab_elementos.h \
	fab_elementos.cpp \
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
	punto.cpp \
	punto.h \
	esq_este.cpp \
	esq_este.h \
	esq_norte.cpp \
	esq_norte.h \
	esq_oeste.cpp \
	esq_oeste.h \
	esq_sur.cpp \
	esq_sur.h \
	pas_horiz.cpp \
	pas_horiz.h \
	pas_vert.cpp \
	pas_vert.h \
	componente.cpp \
	componente.h

pme_editor_SOURCES = \
	act_marcas.cpp \
	app_cleaner_editor.cpp \
	app_editor.cpp \
	control_seleccion.cpp \
	editor_mapas.cpp \
	file_chooser.cpp \
	gui.cpp \
	item.cpp \
	item_abrir.cpp \
	item_archivo.cpp \
	item_elem.cpp \
	item_guardar.cpp \
	item_nuevo.cpp \
	item_salir.cpp \
	m_arch_factory.cpp \
	m_bar_factory.cpp \
	menu.cpp \
	menubar.cpp \
	panel_elems.cpp \
	panel_mundo.cpp \
	submenu.cpp \
	v_ingreso_datos.cpp \
	v_principal.cpp \
	vista_mapa.cpp

pme_editor_CPPFLAGS = @GTK_CFLAGS@

libpme_editor_la_LIBADD = \
	$(top_builddir)/common/libpme-common.la \
	$(top_builddir)/server/libpme-server.la

pme_editor_LDADD = \
	@GTK_LIBS@ \
	libpme-editor.la \
	$(top_builddir)/common/libpme-common.la \
	$(top_builddir)/server/libpme-server.la

CLEANFILES = *~
