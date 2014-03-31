#$(shell export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH)


PROGS = finds test

all: $(PROGS)

	
finds: getopt.c
	gcc -o $@ getopt.c
	
test: simpletest.c
	gcc -o $@ simpletest.c	
	
clean:
	rm -f *.0 *~ *.so *.a $(PROGS)


