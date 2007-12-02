PLATFORM = $(shell ./config.guess)
include make.$(PLATFORM)

CPPFLAGS = "-DCOMPILER=\"$(CC)\"" "-DFLAGS=\"$(OPTFLAGS)\"" \
           "-DPLATFORM=\"$(PLATFORM)\""

# Agregue -DDEBUG_RUN a CPPFLAGS para no ver todos los casos

# Compilar 
LIBS = -lm -lrt
OBJS = matmul.o timing.o

TARGETS=matmul matmul-bloques matmul-lineas matmul-3loopi

.PHONY:	all
all:	$(TARGETS)

# ---

matmul: $(OBJS) mmult_basico.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

matmul-bloques:	$(OBJS) mmult_xbloques.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

matmul-3loopi: $(OBJS) mmult_3loopi.c
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

matmul-lineas:	$(OBJS) mmult_xlinea.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

# ---
# Esto es solo una sugerencia para hacer graficos de performance...
# sientase libre de mejorarlo, siempre que muestre MFlops/s vs tamaño de matriz

MILLRUN = env

timing:	matmul
	$(MILLRUN) `pwd`/matmul-bloques > timing.raw
	perl -ne 'if (/Tam:\s+(\S+).*s:\s+(\S+)/) {print "$$1 $$2\n";}' timing.raw > timing

.PHONY:	display
display:	timing
	echo "set term x11;" | gnuplot -persist - timing.gnuplot

timing.ps:	timing
	echo "set term postscript; set output 'timing.ps';" \
	  | gnuplot - timing.gnuplot

timing.ppm:	timing
	echo "set term pbm color; set output 'timing.ppm';" \
          | gnuplot - timing.gnuplot

# ---

.PHONY:	clean realclean
clean:
	rm -f $(TARGETS) *.o

realclean:	clean
	rm -f *~ timing timing.raw timing.ps timing.ppm
