#include "bfd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>                      
#include <string.h>



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

void print_int (int x, unsigned base)
{
  //printf ("print_int\n");
  char buf[100];
  size_t n = itoa (x, buf, base);
//  size_t n2 = ultoa(buf, x);
  //printf("itoa(%d) = %.*s.\n", x, (int) n, buf);
  write (1, buf, n);
  for(n;n<=11;n++){ write(1," ",1);}
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

