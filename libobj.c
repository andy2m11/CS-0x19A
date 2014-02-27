//#include "sysdep.h"
#include "bfd.h"
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
 
                     
//void (*findsections)(bfd *abfd, asection *sect, PTR obj);    

      
      
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
	
	for (i = 0; i < number_of_symbols;) {
		printf("symbol name:%s, value:%x\n", 
		symbol_table[i]->name,
		symbol_table[i]->section->vma+symbol_table[i]->value);
	}
}    

void findsections(bfd *abfd, asection *sect, PTR obj){
	printf("section: (name:%s vma:%x raw-sz:%x, cooked-sz:%x, offset:%x\n",
	sect->name, sect->vma, sect->rawsize, sect->size, sect->filepos);

}      
      




