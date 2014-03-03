#include "bfd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>                      
#include <string.h>



void reverse(char *s, size_t s_len) {
	size_t i, j;
	char temp;
	
	for (i = 0, j = s_len - 1; i < j; ++i, --j) {
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}

size_t ultoa(char *s, unsigned long int n, unsigned base) {
	size_t i = 0;
	if(n < 0)
	{ n = -n;}
	do {
		if(n % base < 10){
			s[i++] = n % base + '0';
		}
		else{
			s[i++] = n % base + '0' + 7 +32;
		}
	} while (n /= base);
	s[i] = '\0';
	if(base == 16){
		s[i++] = 'x';
		s[i++] = '0';
	}
	reverse(s, i);
	
	return (i);
}

void print_int(int x, unsigned base)
{

  char buf[100];  	

  size_t n = ultoa(buf, x, base);
  
  write (1, buf, n);
  for(n; n<=11; n++)
  { 
  	write(1," ",1);
  }
  write (1, "  ", 2);

}

 

void getsects(bfd *abfd)
{
        asection *p;    
	char *space = "           ";
	char *firstline = "\nSections:\nName:               vma:	 raw-sz:        cooked-sz:    offset:       \n";
	write(1, firstline, strlen(firstline));   	
        for (p = abfd->sections; p != 0; p = p->next)
        {
	   	write (1, p->name, strlen(p->name));
		write(1,"                           ",(20-strlen(p->name)));
		print_int(p->lma,16);
	  	print_int(p->rawsize,16);
		print_int(p->size,16);
		print_int(p->filepos,16);
	  	write(1,"\n",2);
        }
         
}

