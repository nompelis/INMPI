
MPICC = mpicc
COPTS = -Wall -fPIC -O0 -g
COPTS = -fPIC
LINK_OPTS = -shared -Wl,-soname,libindsde.so -o libindsde.so 

all: lib

lib:
	$(MPICC) -c $(COPTS) indsde.c
	ar rsc libindsde.a indsde.o
	$(MPICC) $(LINK_OPTS) indsde.o

clean:
	rm -Rf *.so *.a *.o 

