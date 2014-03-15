#include "bfd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>                      
#include <string.h>
#include <dlfcn.h> 

           extern size_t ultoa(char *s, unsigned long int n, unsigned base);         
                     
#define rdtsc(x)      __asm__ __volatile__("rdtsc \n\t" : "=A" (*(x)))
        

int main(int argc, char *argv[])
{
	bfd *abfd;
	void *handle;
	void *handle2;
	void (*func)(bfd *obj);
	void (*pfunc)(int x, unsigned base );
        char *error;
        
	unsigned long long start, finish;

	
  	char *msg="a.out"; 
  	char *err = "";
     	bfd_init();
     	char *target= "elf64-x86-64";
     	const char **list = bfd_target_list();
     		bfd_perror(err);    
  	
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
	


	rdtsc(&start);		
	handle = dlopen("./libobjdata.so",iflag); // 1 = LAZY , 2 = NOW
	if (!handle) {
            fputs (dlerror(), stderr);
            exit(1);
        }

	rdtsc(&finish);

	pfunc = dlsym(handle, "print_int");
	if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }	


	int tester = 100000;
	pfunc(tester, 10);
//	write(1,"time(ms): ", sizeof("time(ms): "));
//	pfunc(time, 10);
	
//	printf("rdtsc start: %llu\n",start);
	write(1,"\nstart: ", sizeof("\nstart: "));
	pfunc(start, 10);
		
//	printf("rdtsc finish: %llu\n",finish);	
	write(1,"\nfinish: ", sizeof("\nfinish: "));
	pfunc(finish, 10);
	
	write(1,"\ndifference: ", sizeof("\ndifference: "));
	pfunc(finish-start,10);	
		
//	printf("rdtsc time: %llu\n",(finish-start)/2530000000);	
	double rtime = ((double)(finish-start))/(double)2530000000;
	int ddec = 0; int kk = 0;
	double test = 0;
	int ten = 10;
	int count = 0; int decplace = 0;
	for( kk = 1; ddec == 0; kk*=ten){
		ddec = rtime * (double)kk;
		test = rtime * (double)kk;
//		printf("kk is %d  %d %f\n" ,kk, ddec, test);
		count++;
	}

//	ddec = rtime*(double)kk;//*(double)10;
	ddec = rtime*(double)1000000;//*(double)10;
	if(count < 5){ decplace = 5 - count ; decplace += 3;}
	else{ decplace = count - 5; }		
	printf("cccc is %d  %d \n" ,count, decplace);	

	write(1,"\nrdtsc time(ms): ", sizeof("\nrdtsc time(ms): "));
	write(1,"0.", sizeof("0."));
	write(1,"000000", decplace);
	pfunc(ddec, 10);	

	func = dlsym(handle, "getsects");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }	

		
	write(1,"\n\n\n", sizeof("\n\n\n"));
	
//	getsects(abfd);		
	func(abfd);
	bfd_close (abfd);
	dlclose(handle);
	
	FILE *fp; 
	fp = fopen ("stats.txt", "a");
	
	char *fwchar;
	
  	size_t nn = ultoa(fwchar, ddec, 10);
  	write(1, fwchar, nn); 
  	write(1,"\n",2);
 // 	fwrite ((char*)buf , sizeof(char), sizeof(buf), fp);
	fwrite (fwchar , sizeof(char), sizeof(fwchar), fp);
	
	fclose(fp);


	
	return 0;
}



