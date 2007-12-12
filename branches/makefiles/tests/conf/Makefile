.PHONY: all test clean

LDFLAGS=-lpthread

CXXFLAGS=-ggdb -I../..

TARGET=test-conf

COMMON_O = ../../common/mutex.o \
	   ../../common/bloqueo.o

OPT_O = ../../opt/ConfValue.o \
	../../opt/Configuracion.o

OBJS=main.o test-load.o test-equal.o $(OPT_O) $(COMMON_O)


all: test

$(TARGET): $(OBJS)
	g++ -o $@ $(CXXFLAGS) $(LDFLAGS) $^

test: $(TARGET)
	@./$^

print:
	@echo $(OBJS) | sed -e 's/ /\n/g' - | sort

clean:
	@rm -vf $(OBJS) $(TARGET)
