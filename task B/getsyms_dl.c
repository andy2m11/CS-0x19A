#include "bfd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  
#include <dlfcn.h>                 




extern void getsyms(bfd *abfd);
        
#define rdtsc(x)      __asm__ __volatile__("rdtsc \n\t" : "=A" (*(x)))
        
     
int main(int argc, char *argv[]){ 

	bfd *abfd;
	void *handle;
	void (*func)(bfd *obj); 
  	char *err ="";
  	char *error;
       	bfd_init();
     	char *target= "elf64-x86-64";
//     	const char **list = bfd_target_list(); 
//     		bfd_perror(err);      
	        	
  	_bfd_new_bfd();
  		write(1, "Creating bfd obj......", sizeof("Creating bfd obj...."));
  		bfd_perror(err);

  	
  	bfd_set_default_target(target);
  		write(1, "Setting Target........", sizeof("Setting Target......"));
  		bfd_perror(err);
  	
  	
  	abfd = bfd_openr (argv[1],target);
		write(1, "Opening File..........", sizeof("Opening File........"));
		bfd_perror(err);

	int chk = 0;
	chk = bfd_check_format (abfd, bfd_object);
		write(1, "Validating Format... ", sizeof("Validating Format... "));
		bfd_perror(err);
//	printf("check is: %d\n",chk);

	int iflag = 1;
	char *lazy = "1";
	char *now = "2";
	if(argv[2] != NULL){
		char *dflag = argv[2];	
		if(strcmp(dflag,now) == 0){
		 iflag = 2; 
		 write(1, "Setting flag to RTLD_NOW\n",sizeof("Setting flag to RTLD_NOW\n")); 
		 }
		 else{
		 write(1, "Setting flag to RTLD_LAZY\n",sizeof("Setting flag to RTLD_LAZY\n")); 		 
		 }	
	}
	else{
		 write(1, "Setting flag to default RTLD_LAZY\n",sizeof("Setting flag to default RTLD_LAZY\n"));
	}
    	asection *p;
  		
	unsigned long long start, finish;    		
/*
	long tick1, tick2; 
	unsigned c,d,e,f;
	asm volatile("rdtsc" : "=a" (c), "=d" (d));
	tick1 = (((long)c) | (((long)d) << 32)); // calculating the tick value.
//	printf("time start: %lu\n",tick1);
	write(1,"time start: ", sizeof("time start: "));
	print_int(tick1, 10);
 */ 	
	rdtsc(&start);	
	handle = dlopen("./libobjdata.so",iflag);
	if (!handle) {
            fputs (dlerror(), stderr);
            exit(1);
        }	
 	rdtsc(&finish);
 	       
	func = dlsym(handle, "getsyms");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }		

	getsyms(abfd);	 
	
	dlclose(handle);	

/*		
	asm volatile("rdtsc" : "=a" (e), "=d" (f));  
	tick2 = (((long)e) | (((long)f) << 32)); // calculating the tick value. 
//	printf("time end: %lu\n",tick2);
	write(1,"\ntime end: ", sizeof("\ntime end: "));
	print_int(tick2, 10);
	
	double time;
	time = (double)((tick2 -tick1)/3330000); //cpu is 2.53 GHZ
//	printf("time(ms): %u\n",time);
	write(1,"\ndifference: ", sizeof("\ndifference: "));
	print_int(tick2-tick1,10);
	write(1,"\n",2);
*/	
//	write(1,"time(ms): ", sizeof("time(ms): "));
//	print_int(time, 10);
	
//	printf("rdtsc start: %llu\n",start);
	write(1,"\nstart: ", sizeof("\nstart: "));
	print_int(start, 10);
		
//	printf("rdtsc finish: %llu\n",finish);	
	write(1,"\nfinish: ", sizeof("\nfinish: "));
	print_int(finish, 10);
	
	write(1,"\ndifference: ", sizeof("\ndifference: "));
	print_int(finish-start,10);

//	printf("rdtsc time: %llu\n",(finish-start)/2530000000);	
	double rtime = (finish-start)/33000000000;
	write(1,"\nrdtsc time: ", sizeof("\nrdtsc time: "));
	print_int((finish-start)/33000000000, 10);	
	

	write(1,"\n", sizeof("\n"));

//	dlclose(handle);	
		
}


