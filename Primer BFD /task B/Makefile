$(shell export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH)


PROGS = getsections getsyms getsections_dl getsyms_dl
OBJS = objsect.o objsym.o
LIBS = libobjdata.so
all: $(LIBS) $(PROGS) $(OBJS)

###
libobjdata.so: objsect.o objsym.o
	gcc -shared -o $@ objsect.o objsym.o
	
objsect.o: objsect.c
	gcc -fPIC -c objsect.c
	
objsym.o: objsym.c
	gcc -fPIC -c objsym.c

	

getsections_dl: getsections_dl.c 
	gcc -o $@ getsections_dl.c -lbfd -L. -lobjdata -ldl

getsyms_dl: getsyms_dl.c 
	gcc -o $@ getsyms_dl.c -lbfd -L. -lobjdata -ldl



getsections: getsections.c 
	gcc -o $@ getsections.c -lbfd -L. -lobjdata

getsyms: getsyms.c 
	gcc -o $@ getsyms.c -lbfd -L. -lobjdata

#objsect.o: objsect.c
#	gcc -c objsect.c
	
#objsym.o: objsym.c
#	gcc -c objsym.c


#libobjdata.a: objsect.o objsym.o
#	ar rc libobjdata.a objsect.o objsym.o
#	ranlib libobjdata.a
	
	
	

clean:
	rm -f *.0 *~ *.so $(PROGS)


