$(shell export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH)


PROGS = finds

all: $(PROGS)

	
finds: getopt.c
	gcc -o $@ getopt.c
	
	
clean:
	rm -f *.0 *~ *.so *.a $(PROGS)


