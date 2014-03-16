#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>  
#include <sys/stat.h> 
struct arguments{
	int f;
	int l;
	int p;
	int s;
	char *fval;
	char *pval; 	
	char *sval; 	
} ar;
/* function type that is called for each filename */
typedef int Myfunc(const char *, const struct stat *, int);
static Myfunc myfunc;
 int myftw(char *, Myfunc *);
 int getPaths(Myfunc *);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;
#define FTW_F 1 /* file other than directory */
#define FTW_D 2 /* directory */
#define FTW_DNR 3 /* directory that can’t be read */
#define FTW_NS 4 /* file that we can’t stat */   
static size_t pathlen;

/*   
	finds -p pathname [-f c|h|S] [-l] -s s   

The pathname is a string identifying some location in the directory hierarchy e.g., /, /home/joe, ., or .. 
The -f flag is optional but must be followed by either "c", "h" or "S" to identify the file suffixes for the files that we wish to search. For example, "-f c" means search for all files with a .c ending, while "-f h" means search for all files with a .h ending. If the -f option is not used, it is assumed that you wish to search through all regular files from the pathname for those files containing "s".

The -l option, when specified, means search for regular files and symbolic links with the suffix specified by the -f option. If the -l option is specified and -f is not, then your program should search for all regular files and all symbolic links starting from pathname.

The final argument accepted by "finds" is specified by the -s flag and is followed by the search string "s".
*/
int main (int argc, char **argv)
{
       ar.l = 0;       
       ar.f = 0;       ar.fval = NULL;
       ar.p = 0;       ar.pval = NULL;
       ar.s = 0;       ar.sval = NULL;                  
       int index;
       int c;  
       opterr = 0;
       int filechk = 0;    
       DIR *dp;
        
       while ((c = getopt (argc, argv, "lp:s:f:")) != -1){
         switch (c)
           {
           case 'l':
             fprintf (stderr, "%s\n", "Case l");
             ar.l = 1;
             break;
           case 'f':
             fprintf (stderr, "%s\n", "Case f");
             ar.fval = optarg;
             if(strcmp(ar.fval, "c") != 0 && strcmp(ar.fval, "h") != 0 && strcmp(ar.fval, "S") != 0 ){
             	fprintf (stderr, "Option -%c only accepts 'c', 'h', or 'S' as arguments.\n", optopt);
             	return 1;
             }
             else{
           	  ar.f = (int)ar.fval[0]; //c = 99, S = 83, h = 104
//           	  fprintf (stderr, "fflag is: %d \n", ar.f);        
             }
             break;
           case 'p':
             fprintf (stderr, "%s\n", "Case p");
             ar.pval = optarg;
             if ((dp = opendir((char*)ar.pval)) == NULL){
               fprintf (stderr,"fd %d: %s is not a %s\n", filechk, ar.pval, "valid pathname");
               return 1;             
             }
             else{
               ar.p = 1;
             }
/*             filechk = open(ar.pval, O_RDONLY);
             if(filechk > 0){
    	       fprintf (stderr,"Opening fd %d: %s\n", filechk, ar.pval);
               ar.p = 1;       
             }
             else{
               fprintf (stderr,"fd %d: %s is not a %s\n", filechk, ar.pval, "valid pathname");
               return 1;
             }					*/
             break;
           case 's':
             fprintf (stderr, "%s\n", "Case s");    
             ar.s = 1;
             ar.sval = optarg;           
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
           } //end switch(c)
       }  //end while getopt

       printf ("pflag = %d, fflag = %d, lflag = %d, sflag = %d\n",
               ar.p, ar.f, ar.l, ar.s );    
       printf ("fvalue = %s, pvalue = %s, svalue = %s\n",
               ar.fval, ar.pval, ar.sval );  
                       
       if(ar.s == 0 || ar.p == 0 ){
         fprintf(stderr, "%s\n", "Missing essential -p and -s arguments");
         return 1;
       }    
       
       //Print out bad arguments
       for (index = optind; index < argc; index++){
         printf ("Non-option argument: %s\n", argv[index]);
       }       
       
         //traverse through directory
	 myftw(ar.pval, myfunc);

       return 0;       
       
}
///////////////////////////////////////////////////////////////////////////////////
#ifdef  PATH_MAX
static int pathmax=PATH_MAX;
#else
static int pathmax=0;
#endif
#define PATH_MAX_GUESS 1024
char *path_alloc(int *size)
{
    /* return allocated size, if nonull */
    char *ptr;
    if(pathmax == 0){
        errno = 0;
    if((pathmax = pathconf("/", _PC_PATH_MAX)) < 0)
    {
        if(errno == 0)
            pathmax = PATH_MAX_GUESS;
        else
            printf("pathconf error for _PC_PATH_MAX");
    }
    }
    else
    {
        pathmax++;
    }
   
    if((ptr = malloc(pathmax + 1)) == NULL)
        printf("malloc error for pathname\n");
    if(size != NULL)
        *size = pathmax + 1;
    return (ptr);
}
myftw(char *pathname, Myfunc *func)
{
 	fprintf(stderr, "Searching directory: %s\n", pathname);
	ar.pval = (char*)path_alloc(&pathlen);
	/* malloc PATH_MAX+1 bytes */
	/* (Figure 2.16) */
	if (pathlen <= strlen(pathname)) {
		pathlen = strlen(pathname) * 2;
		if ((ar.pval = realloc(ar.pval, pathlen)) == NULL)
			 fprintf(stderr, "%s\n", "Alloc failed");
	}
	strcpy(ar.pval, pathname);
	return(getPaths(func));
}

int getPaths(Myfunc* func){

	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	int ret, n;
	if (lstat(ar.pval, &statbuf) < 0)
		return(func(ar.pval, &statbuf,FTW_NS));/* stat error */

	if (S_ISDIR(statbuf.st_mode) == 0)
		return(func(ar.pval, &statbuf,FTW_F));/* not a directory */

	/*
	* It’s a directory. First call func() for the directory,
	* then process each filename in the directory.
	*/
	if ((ret = func(ar.pval, &statbuf, FTW_D)) != 0)
		return(ret);
	n = strlen(ar.pval);
	if (n + NAME_MAX + 2 > pathlen) {
	/* expand path buffer */
		pathlen *= 2;
		if ((ar.pval = realloc(ar.pval, pathlen)) == NULL)
			 fprintf(stderr, "%s\n", "Alloc failed");
	}
	ar.pval[n++] = '/';
	ar.pval[n] = 0;
	if ((dp = opendir(ar.pval)) == NULL)	// can’t read directory 
		return(func(ar.pval, &statbuf, FTW_DNR));
//	fprintf(stderr, "%s\n", ar.pval); //print directory name
	while ((dirp = readdir(dp)) != NULL) {
		if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0){
		  continue;/* ignore dot and dot-dot */
		}		
		strcpy(&ar.pval[n], dirp->d_name); /* append name after "/" */
		fprintf(stderr, "%s\n", ar.pval);
//		fprintf(stderr, "%s\n", dirp->d_name); // print name of file or directory
		if ((ret = getPaths(func)) != 0){	/* recursive */
		  fprintf(stderr, "Got getPaths != 0 %d %s\n", ret, dirp->d_name);
		  break; /* time to leave */
		}
	}
	ar.pval[n-1] = 0; /* erase everything from slash onward */
	if (closedir(dp) < 0)
		fprintf(stderr, "%s\n", "Can't close directory");
	
	return(ret);
  

}

int myfunc(const char *pathname, const struct stat *statptr, int type)
{
//	fprintf(stderr, "%s\n", "My func");
	switch (type) {
		case FTW_F:
		  switch (statptr->st_mode & S_IFMT) {
		    case S_IFREG:
		      nreg++;
		      break;
		    case S_IFBLK:
		      nblk++;
		      break;
		    case S_IFCHR:
		      nchr++;
		      break;
		    case S_IFIFO:
		      nfifo++;
		      break;
		    case S_IFLNK:
		      nslink++;
		      break;
		    case S_IFSOCK: 
		      nsock++;
		      break;
		    case S_IFDIR:
	              /* directories should have type = FTW_D */
		      fprintf(stderr, "for s_IFDIR for %s\n", pathname);
		  }
		break;
		case FTW_D:
		  ndir++;
		  break;
		case FTW_DNR:
		  fprintf(stderr, "%s\n", "Can't read directory");	
		  break;
		case FTW_NS:
		  fprintf(stderr, "%s %s\n", "stat error for", pathname);
		  break;
		default:
		  fprintf(stderr, "unknown type %d for pathname %s", type, pathname);
	}
	return(0);
}


