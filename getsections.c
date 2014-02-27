//#include "sysdep.h"
#include "bfd.h"

#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>                      
#include <string.h>




void (*findsections)(bfd *abfd, asection *sect, PTR obj);    

void numtoarray(int num, int array[]);
void hextochar(int num, char* outc);

void reverse(char *s, size_t s_len);
size_t ultoa(char *s, unsigned long int n);      
size_t itoa (int x, char *s, unsigned base);
static void print_int (int x, unsigned base);



      
      
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
	printf("number_of_symbols %l\n",number_of_symbols);
	
	if(number_of_symbols < 1000)
	{
		number_of_symbols = 1000;
	}
	
	write(1,"NAME        ",sizeof("NAME       "));
	
	for (i = 0; i < number_of_symbols; i++) {
		printf("symbol name:%s, value:%x\n", 
		symbol_table[i]->name,
		symbol_table[i]->section->vma+symbol_table[i]->value);
	}
}    




int main(int argc, char *argv[])
{
	bfd *abfd;
	asymbol *ptrs[2];
	asymbol *new;
  	char *msg="a.out"; 
  	char *err;
     	bfd_init();
     	char *target= "elf64-x86-64";
     	const char **list = bfd_target_list();
     		bfd_perror(err);    
//    		write(1,*list,55);
     		   
//        bfd_format aa;
//  		bfd_perror(err);       
 	 if (abfd != NULL)
 	 {
 	   //printf ("open bfd\n");
	    //write(1,argv[1],sizeof(argv[1]));
		write(1," opened\n",sizeof(" opened\n"));
  	}
  	
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
		
	const char *name1 = ".interp";
//	 bfd_get_section_by_name(abfd, name);
		bfd_perror(err);




	asection *sect;	
	
//void bfd_map_over_sections(abfd,func(abfd, sect,ptrs[0]), ptrs[0]);
//             bfd_perror(err);

asymbol **loc;
//loopy	
//BFD_SEND(abfd, _bfd_get_symtab_upper_bound, (abfd));
//	bfd_perror(err);
//BFD_SEND (abfd, _bfd_canonicalize_symtab,(abfd, loc));
//	bfd_perror(err);

	char *cTest;
	int ii = 0;
	char tester[100];
          asection *p;
          char *testn;
          int testsize;
          char *testvma;
          char *testfpos; 
	char *space = "           ";

	char *firstline = "\nSections:\n	Name:	     vma:		raw-sz:		cooked-sz:	offset: \n";
	write(1, firstline, 59);
//	Replace below with bfd_map_overSections which calls abfd, findsections(), NULL)
//	void bfd_map_over_sections(abfd,   findsections,    0);
//	int arrayTest[20] = {0};
      	
          for (p = abfd->sections; p != 0; p = p->next)
          {
//            	func(abfd, p, new);
//	printf("section: (name:%s vma:%x raw-sz:%x, cooked-sz:%x, offset:%x\n",
//	p->name, p->vma, p->rawsize, p->size, p->filepos);
/*
		testn = p->name;
		testsize = p->size;
		testvma = (char*)p->vma;
		testfpos = (char*)p->filepos;

		write(1, (char*)p->name,(size_t)(sizeof(testn)));
		write(1, space, 10);
		write(1, (char*)cTest, 20);


		write(1, "\n", 2);
*/		
	   write (1, sect->name, sizeof(sect->name));
	    //for(cnt; cnt<=18; cnt++){ write(1," ",1);}

		write(1,"     ",5);
		print_int(sect->lma,16);
	    print_int(sect->rawsize,16);
		print_int(sect->size,16);
		print_int(sect->filepos,16);
	    write(1,"\n",1);
	  
  
         }
                 
//	ptrs[0] = new;
//	ptrs[1] = 0;

//	bfd_set_symtab (abfd, ptrs, 1);
	bfd_close (abfd);
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
void numtoarray (int num, int array[]){
	
	int i = 0;
	int ii = 0;
	int kk = 0;
	int div = 1;
//	int array[20] = 0;
	
	while((num/div) > 1){

		num %= div;
		array[i] = num;
		i++; div*=10;
		
	}
	return;
}
void hextochar ( int num, char *s  ){
	
//	int size = sizeof(var);

	int ii = 0;
	int kk = 0;

	while (num != 10)
	{
		s[ii++] = num%10 + '0';
	}		
	s[ii] = '\0';
	reverse(s,ii);
}


void reverse(char *s, size_t s_len) {
	size_t i, j;
	char temp;
	
	for (i = 0, j = s_len - 1; i < j; ++i, --j) {
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}

size_t ultoa(char *s, unsigned long int n) {
	size_t i = 0;

	do {
	
	s[i++] = n % 10 + '0';
	} while (n /= 10);
	s[i] = '\0';

	reverse(s, i);
	return (i);
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

