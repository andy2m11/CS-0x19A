#include "bfd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>                      
#include <string.h>
#include <dlfcn.h> 
                     
extern size_t itoa (int x, char *s, unsigned base);
extern void print_int (int x, unsigned base);
extern void getsects(bfd *abfd);

#define rdtsc(x)      __asm__ __volatile__("rdtsc \n\t" : "=A" (*(x)))

int main(int argc, char *argv[])
{
	bfd *abfd;
	void *handle;
	void (*func)(bfd *obj);
        char *error;
        
	unsigned long long start, finish;



  	char *msg="a.out"; 
  	char *err;
     	bfd_init();
     	char *target= "elf64-x86-64";
     	const char **list = bfd_target_list();
     		bfd_perror(err);    
  	
  	_bfd_new_bfd();
  		bfd_perror(err);
  	
  	bfd_set_default_target(target);
//  	bfd_find_target(msg,abfd);  
  		bfd_perror(err);
  	
  	abfd = bfd_openr (argv[1],target);
//	abfd = bfd_openr ("test1",target); 
		bfd_perror(err);
	
	int chk = 0;
	chk = bfd_check_format (abfd, bfd_object);
		bfd_perror(err);
	
	rdtsc(&start);
		
	write(1,"XXXXxxxxxxxxX\n",15);
	handle = dlopen("./libobjdata.so",RTLD_LAZY);
	if (!handle) {
            fputs (dlerror(), stderr);
            exit(1);
        }
        
	write(1,"XXXXxxxxxxxxX\n",15);
	
	func = dlsym(handle, "getsects");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }	
	
	write(1,"XxxxxxxxxXXXX\n",15);
	
	getsects(abfd);
	rdtsc(&finish);
		
	dlclose(handle);
	bfd_close (abfd);
	
	return 0;
}


