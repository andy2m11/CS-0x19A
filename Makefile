$(shell export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH)


PROGS = getsections getsyms
OBJS = objsect.o objsym.o
LIBS = libobjdata.a
all: $(LIBS) $(PROGS) $(OBJS)


getsections: getsections.c 
	gcc -o $@ getsections.c -lbfd -L. -lobjdata

getsyms: getsyms.c 
	gcc -o $@ getsyms.c -lbfd -L. -lobjdata

objsect.o: objsect.c
	gcc -c objsect.c
	
objsym.o: objsym.c
	gcc -c objsym.c


libobjdata.a: objsect.o objsym.o
	ar rc libobjdata.a objsect.o objsym.o
	ranlib libobjdata.a

clean:
	rm -f *.0 *~ *.so $(PROGS)


