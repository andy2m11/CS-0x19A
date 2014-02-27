//#include "sysdep.h"
#include "bfd.h"
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <dlfcn.h>                 


extern itoa (int x, char *s, unsigned base); 
extern void print_int (int x, unsigned base);
extern void getsyms(bfd *abfd);
        
#define rdtsc(x)      __asm__ __volatile__("rdtsc \n\t" : "=A" (*(x)))
        
     
int main(int argc, char *argv[]){

	bfd *abfd;
	void *handle;
	void (*func)(bfd *obj);
  	char *err;
     	bfd_init();
     	char *target= "elf64-x86-64";
//     	const char **list = bfd_target_list(); 
//     		bfd_perror(err);     
	        	
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

	unsigned long long start, finish;    		
  	rdtsc(&start);
	long tick1, tick2; 

	unsigned c,d,e,f;
	asm volatile("rdtsc" : "=a" (c), "=d" (d));
	tick1 = (((long)c) | (((long)d) << 32)); // calculating the tick value.
	printf("time start: %lu\n",tick1);
  	
  	asection *p;
	handle = dlopen("./libobjdata.so",RTLD_LAZY);
	func = dlsym(handle, "getsyms");
	

	getsyms(abfd);	
	
	dlclose(handle);	
	
	asm volatile("rdtsc" : "=a" (e), "=d" (f));  
	tick2 = (((long)e) | (((long)f) << 32)); // calculating the tick value.
	printf("time end: %lu\n",tick1);
	unsigned time;
	time = (unsigned)((tick2 -tick1)/2530000); //cpu is 2.53 GHZ
	printf("time(ms): %u\n",time);
	
	
	rdtsc(&finish);
		
		
}


