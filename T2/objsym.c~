#include "bfd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
 

extern void print_int (int x, unsigned base);

void getsyms(bfd *obj){
	long storage_needed;
	asymbol **symbol_table;
	long number_of_symbols;
	int i;
	
	storage_needed = bfd_get_symtab_upper_bound (obj);
	
	if (storage_needed <= 0){
	printf("no symbols in obj file \n");
	write(1,"no symbols in obj file \n",sizeof("no symbols in obj file \n"));
	exit(-1);
	}
	
	symbol_table = (asymbol **) malloc (storage_needed);
	number_of_symbols = bfd_canonicalize_symtab (obj, symbol_table);
	
	if (number_of_symbols < 0){
	printf("unable to find symbols\n");
	write(1,"unable to find symbols\n",sizeof("unable to find symbols\n")); 
	exit(-1);
	}
//	printf("number_of_symbols %d\n",number_of_symbols); 
	
	
	write(1,"VMA                ",sizeof("VMA               "));
	write(1,"NAME        \n",sizeof("NAME       \n"));
	
	for (i = 0; i < number_of_symbols; i++) {

		print_int(symbol_table[i]->section->vma+symbol_table[i]->value,16);
		
		write(1,"     ",5);
		write(1,symbol_table[i]->name,strlen(symbol_table[i]->name));
		write(1,"   \n",5);

	}
//	write(1,"DONE\n",6);  //  
	
}    

