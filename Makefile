$(shell export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH)



#getsections: getsections.c 
#	gcc -o objsect.o getsections.c -lbfd  $@


libobjdata.a: objsect.o objsym.o
	ar rc libobjdata.a object.o objsym.o

objsect.o: getsections.c
	gcc -c getsections.c
	
objsym.o: getsyms.c
	gcc -c getsyms.c







