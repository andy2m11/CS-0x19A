//#include "sysdep.h"
#include "bfd.h"

#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>                      
#include <string.h>




void (*findsections)(bfd *abfd, asection *sect, PTR obj);    


//void findsections(bfd *abfd, asection *sect, PTR obj){
	//This is the section where you print things out
	//write(1,abfd->sections,40);


//}

void itoa(	);	
void numtoarray(int num, int array[]);
void hextochar(int num, char* outc);



void reverse(char *s, size_t s_len);
size_t ultoa(char *s, unsigned long int n);      


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

  	_bfd_new_bfd();
  		bfd_perror(err);
  	
  	bfd_set_default_target(*list);
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

//write(1,(char)chk,20);		
//==========================		
//	bfd_set_format (abfd, bfd_object);
//	new = bfd_make_empty_symbol (abfd);
//	new->name = "dummy_symbol";
//	new->section = bfd_make_section_old_way (abfd, ".text");
//	new->flags = BSF_GLOBAL;
//	new->value = 0x12345;
//		bfd_perror(err);

//The old way		
	bfd_get_section_by_name(abfd, name1);	
		bfd_perror(err);
		write(1, bfd_get_section_by_name(abfd, name1)	, 25);          
	
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
	int arrayTest[20] = {0};
          for (p = abfd->sections; p != 0; p = p->next)
          {
//            	func(abfd, p, new);
//	printf("section: (name:%s vma:%x raw-sz:%x, cooked-sz:%x, offset:%x\n",
//	p->name, p->vma, p->rawsize, p->size, p->filepos);
		testn = p->name;
		testsize = p->size;
		testvma = (char*)p->vma;
		testfpos = (char*)p->filepos;
//		hextochar(testsize, cTest);
//		numtoarray(testsize,arrayTest);	
//		hextochar(arrayTest, (char*)cTest);

		write(1, (char*)p->name,(size_t)(sizeof(testn)));
		write(1, space, 10);
		write(1, (char*)cTest, 20);

//		write(1,(int*) testsize,(size_t)sizeof(testsize));
//		write(1, (char*)p->vma,(size_t)sizeof(testvma));
//		write(1, (char*)p->filepos,(size_t)sizeof(testfpos));
		write(1, "\n", 2);
         }
                          
//	ptrs[0] = new;
//	ptrs[1] = 0;

//	bfd_set_symtab (abfd, ptrs, 1);
	bfd_close (abfd);
	return 0;
}

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
