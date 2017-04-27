
MPICC = mpicc
COPTS = -Wall -fPIC -O0 -g
COPTS = -fPIC
LINK_OPTS = -shared -Wl,-soname,libINmpi.so -o libINmpi.so 
COPTS += -D_DEBUG_

all: lib

lib:
	$(MPICC) -c $(COPTS) indsde.c
	$(MPICC) -c $(COPTS) inmpi_mutex.c
	$(MPICC) -c $(COPTS) inmpi_sema.c
	ar rsc libINmpi.a indsde.o inmpi_mutex.o inmpi_sema.o 
	$(MPICC) $(LINK_OPTS) indsde.o inmpi_mutex.o inmpi_sema.o

clean:
	rm -Rf *.so *.a *.o 

