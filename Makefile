CXX = g++
CFLAGS = -g -O0 -std=c++23 -Iinclude
LIBS = -Llib/ -l:libmemflow_ffi.a

ODIR = ./

main.o: main.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

main.out: main.o
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)
	rm -f $(ODIR)/*.o

.PHONY: all
all: main.out

.DEFAULT_GOAL := all

clean:
	rm -f $(ODIR)/*.o
