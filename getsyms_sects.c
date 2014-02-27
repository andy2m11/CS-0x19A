#include "bfd.h"
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <dlfcn.h>

extern void func(bfd *obj);
extern void findsections(bfd *abfd, asection *sect, PTR obj);

int main(int argc, char *argv[]){
	
	bfd *obj;
	void *handle;
	void (*func)(bfd *obj);
	
	bfd_init();
	obj = bfd_openr( argv[1], "elf32-i386");
	if(!obj){
		bfd_perror("open failure \n");
		exit(-1);
	}

	if(!bfd_check_format(obj, bfd_object)){
		printf("not an object file!\n");
		exit(-1);
	}
	
	handle = dlopen("./libobjdata.so", RTLD_LAZY);
	func = dlsym (handle, "getsyms");
	
	bfd_map_over_sections(obj,findsections, NULL);
	
	dlclose (handle);
	exit(0);
	
}
	
	
	

