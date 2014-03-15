$(shell export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH)


PROGS = tshell exshell gopt
#OBJS = objserver.o
#LIBS = libobjserver.a #libobjserver.so
all: $(LIBS) $(PROGS) $(OBJS)


exshell: shell_example.c
	gcc -o $@ shell_example.c

tshell: tshell.c
	gcc -o $@ tshell.c

gopt: getopt.c
	gcc -o $@ getopt.c
	
	
clean:
	rm -f *.0 *~ *.so *.a $(PROGS)


