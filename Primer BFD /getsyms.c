#include "bfd.h"
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
 
                     
//void (*findsections)(bfd *abfd, asection *sect, PTR obj);    

static void print_int (int x, unsigned base);
size_t itoa (int x, char *s, unsigned base);
      
void getsyms(bfd *obj){
	long storage_needed;
	asymbol **symbol_table;
	long number_of_symbols;
	int i;
	
	storage_needed = bfd_get_symtab_upper_bound (obj);
	
	if (storage_needed <= 0){
	printf("no symbols in obj file \n");
	exit(-1);
	}
	
	symbol_table = (asymbol **) malloc (storage_needed);
	number_of_symbols = bfd_canonicalize_symtab (obj, symbol_table);
	
	if (number_of_symbols < 0){
	printf("unable to find symbols\n");
	exit(-1);
	}
	printf("number_of_symbols %d\n",number_of_symbols);
	
	if(number_of_symbols < 1000)
	{
		number_of_symbols = 1000;
	}
	write(1,"VMA                ",sizeof("VMA               "));
	write(1,"NAME        \n",sizeof("NAME       \n"));
	
	for (i = 0; i < number_of_symbols; i++) {

		print_int(symbol_table[i]->section->vma+symbol_table[i]->value,16);
		
		write(1,"     ",5);
		write(1,symbol_table[i]->name,sizeof(symbol_table[i]->name));
		write(1,"   \n",5);
		
		
	}
		write(1,"DONE\n",6);
}    

void findsections(bfd *abfd, asection *sect, PTR obj){
	printf("section: (name:%s vma:%x raw-sz:%x, cooked-sz:%x, offset:%x\n",
	sect->name, sect->vma, sect->rawsize, sect->size, sect->filepos);

}      
      
      
      
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

  	  asection *p;

	getsyms(abfd);	
	
	bfd_close (abfd);
	return 0;
}


size_t itoa (int x, char *s, unsigned base)
{
  //printf ("in itoa\n");
  char *p = s;
  int t = x;
  //flip value, if x is negative
  if (x < 0)
    t = -t;

  //if base is smaller than 10
  if (base <= 10)
  {
    do
    {
      *p++ = '0' + t % base;
      t /= base;
    }
    while (t);
    // add negative sign
    if (x < 0)
      *p++ = '-';
  }
  else if (base >= 10)
  {
    do
    {
      if (t % base < 10)
      {
        *p++ = '0' + t % base;
        t /= base;
      }
      else
      {
        *p++ = 'A' + (t % base - 10);
        t /= base;
      }
    }
    while (t);


    //put hexadecimal sign if base = 16
    if (base == 16)
    {
      *p++ = 'x';
      *p++ = '0';
    };

    // add negative sign
    if (x < 0)
      *p++ = '-';
  }
  //digits 
  size_t size = p - s;
  while (s < --p)
  {
    char t = *s;
    *s++ = *p;
    *p = t;
  }
  return size;
}


static void print_int (int x, unsigned base)
{
  //printf ("print_int\n");
  char buf[100];
  size_t n = itoa (x, buf, base);
  //printf("itoa(%d) = %.*s.\n", x, (int) n, buf);
  write (1, buf, n);
  for(n;n<=11;n++){ write(1," ",1);}
  write (1, "  ", 2);
}

