CC = gcc
F77 = g77
OPTFLAGS = -O3 -mcpu=pentium3
CFLAGS = -std=gnu9x $(OPTFLAGS)

CPPFLAGS = "-DCOMPILER=\"$(CC)\"" "-DFLAGS=\"$(OPTFLAGS)\"" \
           "-DPLATFORM=\"$(PLATFORM)\""

# Agregue -DDEBUG_RUN a CPPFLAGS para no ver todos los casos

# Compilar 
LIBS =
OBJS = main.o cpu_info.o

TARGETS=cpuinfo

.PHONY:	all clean

all:	$(TARGETS)

cpuinfo: $(OBJS)
	$(CC) -o $@.exe $^ $(LDFLAGS) $(LIBS)

clean:
	rm -fv $(TARGETS) $(OBJS)