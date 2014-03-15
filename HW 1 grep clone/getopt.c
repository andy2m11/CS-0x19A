     #include <ctype.h>
     #include <stdio.h>
     #include <stdlib.h>
     #include <unistd.h>
     #include <string.h>
    struct arguments{
    	int f;
    	int l;
    	int p;
    	int s;
  	char *fval;
   	char *pval; 	
   	char *sval; 	
    } ar;
   
/*   
	finds -p pathname [-f c|h|S] [-l] -s s   

The pathname is a string identifying some location in the directory hierarchy e.g., /, /home/joe, ., or .. 
The -f flag is optional but must be followed by either "c", "h" or "S" to identify the file suffixes for the files that we wish to search. For example, "-f c" means search for all files with a .c ending, while "-f h" means search for all files with a .h ending. If the -f option is not used, it is assumed that you wish to search through all regular files from the pathname for those files containing "s".

The -l option, when specified, means search for regular files and symbolic links with the suffix specified by the -f option. If the -l option is specified and -f is not, then your program should search for all regular files and all symbolic links starting from pathname.

The final argument accepted by "finds" is specified by the -s flag and is followed by the search string "s".
*/
int main (int argc, char **argv)
{
       int pflag = 0;       int fflag = 0;
       int lflag = 0;         
       int sflag = 0;       
       ar.l = 0;       
       ar.f = 0;       ar.fval = NULL;
       ar.p = 0;       ar.pval = NULL;
       ar.s = 0;       ar.sval = NULL;
       char *fvalue = NULL;
       char *pvalue = NULL;
       char *svalue = NULL;
                   
       int index;
       int c;
     
       opterr = 0;
     
       while ((c = getopt (argc, argv, "lp:s:f:")) != -1)
         switch (c)
           {
           case 'l':
             lflag = 1;
             break;
           case 'f':
             fvalue = optarg;
             if(strcmp(fvalue, "c") != 0 && strcmp(fvalue, "h") != 0 && strcmp(fvalue, "S") != 0 ){
             	fprintf (stderr, "Option -%c only accepts 'c', 'h', or 'S' as arguments.\n", optopt);
             	return 1;
             }
             else{
           	  fflag = 1;             
             }
             break;
           case 'p':
             pflag = 1;
             pvalue = optarg;                
             break;
           case 's':
             sflag = 1;
             svalue = optarg;                
             break;
           case '?':
             if (optopt == 'f')
               fprintf (stderr, "Option -%c requires an argument.\n", optopt);
             else if (optopt == 'p')
               fprintf (stderr, "Option -%c requires an argument.\n", optopt);
             else if (optopt == 's')
               fprintf (stderr, "Option -%c requires an argument.\n", optopt);
             else if (isprint (optopt))
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
             else
               fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
             return 1;
           default:
             abort ();
           }
     

       printf ("pflag = %d, fflag = %d, lflag = %d, sflag = %d\n",
               pflag, fflag, lflag, sflag );    

       printf ("fvalue = %s, pvalue = %s, svalue = %s\n",
               fvalue, pvalue, svalue );    
               
                              
       for (index = optind; index < argc; index++)
         printf ("Non-option argument %s\n", argv[index]);
       return 0;
}





