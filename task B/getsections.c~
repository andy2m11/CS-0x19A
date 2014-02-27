#include "bfd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>                      
#include <string.h>

 
extern size_t itoa (int x, char *s, unsigned base);
extern void print_int (int x, unsigned base);
extern void getsects(bfd *abfd);



int main(int argc, char *argv[])
{
	bfd *abfd;
	asymbol *ptrs[2];
	asymbol *new;
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



	getsects(abfd);

	bfd_close (abfd);
	return 0;
}



