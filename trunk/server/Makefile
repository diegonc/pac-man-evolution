# Makefile de ejemplo para programa cliente-servidor en C/C++
# 
# Creado: vie abr 27 00:37:46 ART 2007
#
# Copyleft 2007 - Leandro Lucarella, Bajo licencia GPL [http://www.gnu.org/]
#

# CONFIGURACION
################

# Extensión de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp

# CONFIGURACION "AVANZADA"
###########################

# Opciones para el compilador C.
CFLAGS = -Wall -ansi -pedantic-errors

# Para valgrind o debug
CFLAGS += -DDEBUG -ggdb -fno-inline

# Opciones del enlazador.
LDFLAGS=-lm -lpthread

# Usamos ccache para acelerar la cosa...
CC=gcc 
CXX=g++ 

CXXFLAGS = $(CFLAGS)
# VARIABLES CALCULADAS A PARTIR DE LA CONFIGURACION
####################################################
gtk = uso

# Agrego flags y libs de GTK+ de ser necesario.
ifdef gtk
#CFLAGS += $(shell pkg-config --cflags gtk+-2.0)
#CXXFLAGS += $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS += $(shell pkg-config --libs gtk+-2.0)
endif

# Uso enlazador de c++ si es código no C.
ifeq ($(extension), c)
enlazador = $(CC)
else
enlazador = $(CXX) 
endif

extension_o = o

# Si no especifica archivos, tomo todos.
fuentes ?= $(wildcard *.$(extension))
fuentes_common ?= $(wildcard ../common/*.$(extension))
#fuentes_map_editor ?= $(wildcard ../map_editor/*.$(extension_o))
#fuetnes_tiny_xml ?= $(wildcard ../common/tinyxml/*.$(extension_o))

# REGLAS
#########

.PHONY: all clean

all: server
#o_tinyxml_files = $(patsubst %.$(extension),%.o,$(fuentes_tiny_xml))
#o_map_editor = $(patsubst %.$(extension),%.o,$(fuentes_map_editor)) #$(o_common_files) $(o_server_files) $(o_tinyxml_files)
o_map_editor_files ?= $(wildcard ../map_editor/*.$(extension_o))

o_map_editor_files_2 = $(subst ../map_editor/editor_mapas.o, ,$(o_map_editor_files))

o_tinyxml_files ?= $(wildcard ../common/tinyxml/*.$(extension_o))
o_common_files = $(patsubst %.$(extension),%.o,$(fuentes_common))
o_files = $(patsubst %.$(extension),%.o,$(fuentes)) $(o_common_files) $(o_map_editor_files_2) $(o_tinyxml_files)

server: $(o_files)
	@if [ -z "$(o_files)" ]; \
	then \
		echo "No hay archivos de entrada para el cliente (archivos client*.$(extension))."; \
		false; \
	fi >&2
	$(enlazador) $(LDFLAGS) $(o_files) $(LOADLIBES) $(LDLIBS) -o miEjecutable $(LDADD)

clean:
	@$(RM) -fv *.o server \
   rm ../common/*.o \
   rm miEjecutable

