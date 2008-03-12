dnl configure.ac

dnl  robado de http://live.gnome.org/Create_a_GTK_Project_using_autotools

AC_PREREQ(2.60)
AC_INIT([pac-man-evolution], [0.1], [name@domain.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.9.6 -Wall -Werror dist-bzip2])

AC_PROG_CXX
AC_PROG_CC
# Compiling sources with per-target flags requires AM_PROG_CC_C_O
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h])
AC_CHECK_HEADERS([netdb.h])
AC_CHECK_HEADERS([stddef.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADERS([sys/socket.h])
AC_CHECK_HEADERS([pthread.h])

# Checks for libraries.
AC_CHECK_LIB(pthread,pthread_create)
AC_CHECK_LIB(socket, socket)
AC_CHECK_LIB(inet, connect)

# Check for SDL_mixer library
AC_CHECK_LIB(SDL_mixer, Mix_PlayMusic, , AC_MSG_ERROR([
*** Unable to find SDL_mixer libary (http://www.libsdl.org/projects/SDL_mixer/)
]))

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_CHECK_FUNCS([bzero memmove socket strchr strerror])

AM_PATH_GTK_2_0([2.8.0],,AC_MSG_ERROR([Gtk+ 2.8.0 or higher required.]))

AM_PATH_SDL( [1.2.11],,AC_MSG_ERROR([SDL 1.2.11 or higher required.]))
CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
CFLAGS="$CFLAGS $SDL_CFLAGS"
CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Makefile
	common/tinyxml/Makefile
	common/editor/Makefile
	common/common/Makefile
	common/server/Makefile
	common/Makefile
	pme-server/Makefile
	map_editor/Makefile
	pme-client/Makefile
	appdata/Makefile
	appdata/pme-client/Makefile
	appdata/pme-client/MiniMapa/Makefile
	appdata/map_editor/Makefile
	appdata/map_editor/imagenes/Makefile
])
AC_OUTPUT
