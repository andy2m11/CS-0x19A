//#include "sysdep.h"
#include "bfd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
 
                     


extern itoa (int x, char *s, unsigned base);
extern void print_int (int x, unsigned base);
extern void getsyms(bfd *abfd);
         
int main(int argc, char *argv[]){

	bfd *abfd;
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
//	printf("chk: %d\n",chk);
  	
  	  asection *p;

	getsyms(abfd);	
	
}


