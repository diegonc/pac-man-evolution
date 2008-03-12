
# Makefile.am -- Process this file with automake to produce Makefile.in

#  robado del autobook - seccion 5.1

bin_PROGRAMS = pme-editor

pme_editor_SOURCES = \
	act_marcas.cpp \
	act_marcas.h \
	app_cleaner_editor.cpp \
	app_cleaner_editor.h \
	app_editor.cpp \
	app_editor.h \
	control_seleccion.cpp \
	control_seleccion.h \
	definiciones.h \
	editor_mapas.cpp \
	file_chooser.cpp \
	file_chooser.h \
	gui.cpp \
	gui.h \
	item.cpp \
	item.h \
	item_abrir.cpp \
	item_abrir.h \
	item_archivo.cpp \
	item_archivo.h \
	item_elem.cpp \
	item_elem.h \
	item_guardar.cpp \
	item_guardar.h \
	item_nuevo.cpp \
	item_nuevo.h \
	item_salir.cpp \
	item_salir.h \
	m_arch_factory.cpp \
	m_arch_factory.h \
	m_bar_factory.cpp \
	m_bar_factory.h \
	menu.cpp \
	menu.h \
	menubar.cpp \
	menubar.h \
	panel_elems.cpp \
	panel_elems.h \
	panel_mundo.cpp \
	panel_mundo.h \
	submenu.cpp \
	submenu.h \
	v_ingreso_datos.cpp \
	v_ingreso_datos.h \
	v_principal.cpp \
	v_principal.h \
	vista_mapa.cpp \
	vista_mapa.h 

pme_editor_EXTRA_DIST = imagenes

pme_editor_CPPFLAGS = \
	-DAPP_DATA_DIR="\"$(datadir)/map_editor\"" \
	@GTK_CFLAGS@ \
	-I@top_srcdir@/common

pme_editor_LDADD = \
	@GTK_LIBS@ \
	$(top_builddir)/common/editor/libpme-editor.a \
	$(top_builddir)/common/server/libpme-server.a \
	$(top_builddir)/common/common/libpme-common.a \
	$(top_builddir)/common/tinyxml/libtinyxml.a 

CLEANFILES = *~
