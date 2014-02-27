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



void getsects(bfd *abfd)
{
	asection *sect;	
        asection *p;    
	char *space = "           ";
	char *firstline = "\nSections:\n	Name:	     vma:		raw-sz:		cooked-sz:	offset: \n";
	write(1, firstline, 59);   	
        for (p = abfd->sections; p != 0; p = p->next)
        {
	   	write (1, sect->name, sizeof(sect->name));
		write(1,"     ",5);
		print_int(sect->lma,16);
	  	print_int(sect->rawsize,16);
		print_int(sect->size,16);
		print_int(sect->filepos,16);
	  	write(1,"\n",1);
        }
         
}


