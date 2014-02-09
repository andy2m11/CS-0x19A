//#include "sysdep.h"
#include "bfd.h"
           
           
           
           
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
		
	const char *name1 = ".data";
//	 bfd_get_section_by_name(abfd, name);
		bfd_perror(err);
		
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

//loopy
          asection *p;
          for (p = abfd->sections; p != 0; p = p->next)
          {
//            	func(abfd, p, new);
                write(1, *p, 25);          

          }
                          
	write(1,new->section,25);

	ptrs[0] = new;
	ptrs[1] = 0;

	bfd_set_symtab (abfd, ptrs, 1);
	bfd_close (abfd);
	return 0;
}
