# Makefile de ejemplo para programa cliente-servidor en C/C++
# 
# Creado: vie abr 27 00:37:46 ART 2007
#
# Copyleft 2007 - Leandro Lucarella, Bajo licencia GPL [http://www.gnu.org/]
#

# CONFIGURACION
################

DEFS := -DTIXML_USE_STL

CXXFLAGS := ${CXXFLAGS} ${DEFS}

# Extensión de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp


# CONFIGURACION "AVANZADA"
###########################

# Opciones para el compilador C.
CFLAGS = -Wall -ansi -pedantic-errors -DLINUX `sdl-config --cflags`

# Para valgrind o debug
CFLAGS += -DDEBUG -ggdb -fno-inline

# Opciones del enlazador.
LDFLAGS=-lm -lpthread `sdl-config --libs` -lGL -lGLU

# Usamos ccache para acelerar la cosa...
CC=gcc 
CXX=g++ 

CXXFLAGS = $(CFLAGS)

gtk = si 
# VARIABLES CALCULADAS A PARTIR DE LA CONFIGURACION
####################################################

# Agrego flags y libs de GTK+ de ser necesario.
ifdef gtk
CFLAGS += $(shell pkg-config --cflags gtk+-2.0)
CXXFLAGS += $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS += $(shell pkg-config --libs gtk+-2.0)
endif

# Uso enlazador de c++ si es código no C.
ifeq ($(extension), c)
enlazador = $(CC)
else
enlazador = $(CXX) 
endif

# Si no especifica archivos, tomo todos.
fuentes ?= $(wildcard *.$(extension))
fuentes_common ?= $(wildcard ../../common/*.$(extension))
fuentes_server_2 ?= $(wildcard ../../server/*.$(extension))
fuentes_map_2 ?= $(wildcard ../../map_editor/*.$(extension))
fuentes_tiny_xml ?= $(wildcard ../../common/tinyxml/*.$(extension))

fuentes_server = $(subst ../../server/Main.cpp, ,$(fuentes_server_2))
fuentes_map = $(subst ../../map_editor/editor_mapas.cpp, ,$(fuentes_map_2))

# REGLAS
#########

.PHONY: all clean

all: subproyecto

o_common_files = $(patsubst %.$(extension),%.o,$(fuentes_common))
o_tinyxml_files = $(patsubst %.$(extension),%.o,$(fuentes_tiny_xml))
o_server_files = $(patsubst %.$(extension),%.o,$(fuentes_server))
o_map_files = $(patsubst %.$(extension),%.o,$(fuentes_map)) $(o_server_files) $(o_common_files) $(o_tinyxml_files)
o_files = $(patsubst %.$(extension),%.o,$(fuentes)) $(o_map_files)

subproyecto: $(o_files)
	@if [ -z "$(o_files)" ]; \
	then \
		echo "No hay archivos de entrada para el cliente (archivos client*.$(extension))."; \
		false; \
	fi >&2
	$(enlazador) $(LDFLAGS) $(o_files) $(LOADLIBES) $(LDLIBS) -o miEjecutable $(LDADD)

clean:
	@$(RM) -fv *.o subproyecto \
   rm ../../common/*.o \
   rm ../../server/*.o \
   rm miEjecutable



