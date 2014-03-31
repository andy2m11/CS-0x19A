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
void scanLink(char *pathname, char *findthis);
void scanFile(char *pathname, char *findthis);
int wildcards(char **outputstr, char *inputstr);
int match(char *first, char * second);
void wcScan(char *pathname, char *findthis);
int cdot(char *pathname, char *findthis);
void scanFile2(char *pathname, char *findthis);


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
             ar.l = 1;       
             break;
           case 'f':
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
             ar.pval = optarg;
             if ((dp = opendir((char*)ar.pval)) == NULL){
               fprintf (stderr,"%s is not a valid pathname\n", ar.pval);
               return 1;             
             }
             else{          
               ar.p = 1;
               int nlen = strlen(ar.pval);
               fprintf(stderr, "%d... %c\n " ,nlen, ar.pval[nlen-1]);
               if(ar.pval[nlen-1] == '/'){             
                 fprintf(stderr, "deleting... %c\n " ,ar.pval[nlen-1]);
                 ar.pval[nlen-1] = 0;
               }
             }

             break;
           case 's':
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



///////////////////////////////////////////////////////////////////////////////////////
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
//---------------------------------------------------------------------
myftw(char *pathname, Myfunc *func)
{
 	fprintf(stderr, "Searching for %s in: %s\n",ar.sval, pathname);
	ar.pval = (char*)path_alloc(&pathlen);
	/* malloc PATH_MAX+1 bytes */
	if (pathlen <= strlen(pathname)) {
		pathlen = strlen(pathname) * 2;
		if ((ar.pval = realloc(ar.pval, pathlen)) == NULL)
			 fprintf(stderr, "%s\n", "Alloc failed");
	}
	strcpy(ar.pval, pathname);
	return(getPaths(func));
}
//---------------------------------------------------------------------
int getPaths(Myfunc* func){

	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	int ret, n, fnlen;
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
//	fprintf(stdout, "Dir: %s\n", ar.pval); //print directory name
	while ((dirp = readdir(dp)) != NULL) {
		if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0){
		  continue;/* ignore dot and dot-dot */
		}		
		strcpy(&ar.pval[n], dirp->d_name); /* append name after "/" */
		fnlen = strlen(dirp->d_name) - 1;
		if(ar.f > 0){	//if the f flag was set
		  if(ar.pval[n+fnlen] == ar.fval[0]){	//match with chosen file type
//		    fprintf(stdout, "%s\n", ar.pval); // print full file pathname
//		    fprintf(stdout, "%s\n", dirp->d_name); // print name of file
//		    scanFile(ar.pval, ar.sval);
//		    scanFile(dirp->d_name, ar.sval);
//		  cdot(ar.pval, ar.sval);		    
 		  }
 		}
 		else{
//		  fprintf(stdout, "%s\n", ar.pval); // print full file pathname
		  scanFile2(ar.pval, ar.sval);
//		  wcScan(ar.pval, ar.sval);
//		  cdot(ar.pval, ar.sval);
	
 		}
 		if(ar.l > 0){ 		
		  scanLink(ar.pval, ar.sval);
 		}
		if ((ret = getPaths(func)) != 0){	/* recursive */
		  fprintf(stderr, "Got getPaths != 0 %d %s\n", ret, dirp->d_name);
		  break; /* time to leave */
		}
	}
	ar.pval[n-1] = 0; /* erase everything from slash onward */
	if (closedir(dp) < 0){
	  fprintf(stderr, "%s\n", "Can't close directory");
	}
	return(ret);
  

}

void scanLink(char *pathname, char *findthis){
	char *match;
	match = strstr(pathname,findthis);
	if(match != NULL){
	  fprintf(stdout, "\"%s\" found on %s\n", findthis, pathname);	      
	}

}
void scanFile(char *pathname, char *findthis){
	int buflen = 2048;
	char line[buflen];
	char *match;
	int line_count = 0;
//	fprintf(stderr, "Looking for %s in: %s\n",findthis ,pathname);
	FILE* pFile;
	pFile = fopen(pathname, "r");
	if (pFile == NULL){
	  fprintf(stderr, "Unable to open: %s\n", pathname);
	}
	else{
	  while(fgets(line, buflen, pFile) != NULL){
	    line_count++;
	    match = strstr(line,findthis);
	    if(match != NULL){
	      fprintf(stdout, "\"%s\" found on line %d in: %s\n", findthis, line_count, pathname);
//	      fprintf(stdout, "line%d:  ", line_count);
//	      fprintf(stdout, "   %s",line);
//	      fprintf(stdout, "In:%s", pathname);		      
	    }
	  }
	  fclose(pFile);	  
	}
}

void scanFile2(char *pathname, char *findthis){
	int buflen = 2048;
	char line[buflen];
	int line_count = 0;
	int ii = 0;
	int linepos = 0;
	int matchcount = 0;
	int needlen = strlen(findthis);
	char cc; char dot; 
	int fdot=0;
	char temp[50]; 
	char trans;
	int hits = 0;
//	fprintf(stderr, "Looking for %s in: %s\n",findthis ,pathname);

	for(ii = 0; findthis[ii] != NULL; ii++)
	{
		trans = findthis[ii];
		temp[ii] = trans;
	}
	FILE* pFile;
	pFile = fopen(pathname, "r");
	if (pFile == NULL){
	  fprintf(stderr, "Unable to open: %s\n", pathname);
	}
	else{
	
	  while(fgets(line, buflen, pFile) != NULL)
	  {
	    line_count++;
	    linepos = 0;
	    while(linepos < strlen(line))//while(line[linepos] != '\n')
	    {   
//	    if(line[linepos] == '\n')
//	    {printf("NEWLINE FOUND \n");}
//	    printf(" %c ", line[linepos]);
//	    printf(" \nLENGTH: %d \n", strlen(line)); 
	    	cc = line[linepos];
	    	if(cc == findthis[hits] )
	    	{
	    	hits++;
	    	}
	    	else if(findthis[hits] == '.')
	    	{	
	    	dot = line[linepos];
	    	temp[hits] = dot;		    	
//	    	printf("Findthis:%s Temp is:\"%s\"   cc:%c\n",findthis, temp, line[linepos]);	
	    	hits++;    fdot = 1;
	    	}
	    	else if(findthis[hits+1] == '*')//qwea*bcd = qweabcd, qwebcd, qweaabcd
	    	{
	    		char afterstar = findthis[hits+2];
	    		char beforestar = findthis[hits];	    		
	    		if(line[linepos+1] == beforestar)
	    		{
	    			hits++; linepos++;
	    			while(line[linepos++] == beforestar)
	    			{
	    			  needlen++;
	    			  hits++;	    			
	    			}
	    			if(line[linepos] != afterstar)
	    			{
	    			  needlen = strlen(findthis);
	    			  hits = 0;
	    			}
	    			else
	    			{
	    			  needlen--;
	    			  hits++;
	    			}
	    		}
	    		else if(line[linepos+1] == afterstar)
	    		{
	    		linepos++;
	    		needlen -= 2;
	    		hits++;
	    		}
	    		else
	    		{
	    		hits = 0; 
	    		needlen = strlen(findthis);
	    		}	    	
	    	}
	    	else if(findthis[hits+2] == '*')//qwea*bcd = qweabcd, qwebcd, qweaabcd
	    	{
	    		char afterstar = findthis[hits+3];
	    		char beforestar = findthis[hits+1];
	    		if(line[linepos+1] == beforestar)
	    		{
	    			hits++; linepos++;
	    			while(line[linepos++] == beforestar)
	    			{
	    			  needlen++;
	    			  hits++;	    			
	    			}
	    			if(line[linepos] != afterstar)
	    			{
	    			  needlen = strlen(findthis);
	    			  hits = 0;
	    			}
	    			else
	    			{
	    			  needlen--;
	    			  hits++;
	    			}
	    		}
	    		else if(line[linepos+1] == afterstar)
	    		{
	    		linepos++;
	    		needlen -= 2;
	    		hits++;
	    		}
	    		else
	    		{
	    		hits = 0;
	    		needlen = strlen(findthis);
	    		}
	    	}
	    	else if(cc == '?')
	    	{
	    	
	    	}
	    	else
	    	{
	    		hits = 0;
	    		fdot = 0;
	    		
	    	}
	    
	    	if(hits == needlen)
	    	{
		    	if(fdot == 1)
		    	{
		    	printf("\"%s\" found on line %d in: %s\n", temp, line_count, pathname);
		    	}
		    	else
		    	{
		    	printf("\"%s\" found on line %d in: %s\n", findthis, line_count, pathname);		    	
		    	}
	    	}
	    linepos++;
	    }
	    
	  }
	  
	  fclose(pFile);	  
	}

}

//-----------------------------------------------------------------------------


int splitdot(char *input, int dotpos, char *out1, char *out2){

	int len = strlen(input);
//	printf("len =%d, dotpos=%d \n", len, dotpos);
	memmove(out1, input, dotpos);
	memmove(out2, input+dotpos+1, len-dotpos);

}


//void wildcards(char **outputstr, char *inputstr){
int wildcards(char **outputstr, char *inputstr){

	int len = strlen(inputstr);
	int ii = 0;
	int wcount = 0;
	int total = 0;
	char dot = NULL;
	char star = NULL;	int sc = 0;
	char qmark = NULL;

	for(ii = 0; ii < len; ii++){
	  if(inputstr[ii] == '.'){
	    wcount++;
	    
	  }
	  else if(inputstr[ii] == '*'){
	    wcount++;
//	    star = inputstr[ii-1];

	  }
	  else if(inputstr[ii] =='?'){
	    wcount++;
//	    qmark = inpustr[ii-1];
	    
	  } 
	  // a .* copy of whatever . takes repeated till 2nd str
	  // if .*, auto skip one, keep skipping if next = one
	  //if .? auto skip one, if next = one skip.
	  //if ?*/*? cancel out?
	 
	  
	  
	}	//end for
	
   return wcount;
}

int match(char *first, char * second)
{
    // If we reach at the end of both strings, we are done
    if (*first == '\0' && *second == '\0')
        return 1;
 
    // Make sure that the characters after '*' are present in second string.
    // This function assumes that the first string will not contain two
    // consecutive '*' 
    if (*first == '*' && *(first+1) != '\0' && *second == '\0')
        return 0;
 
    // If the first string contains '?', or current characters of both 
    // strings match
    if (*first == '?' || *first == *second)
        return match(first+1, second+1);
 
    // If there is *, then there are two possibilities
    // a) We consider current character of second string
    // b) We ignore current character of second string.
    if (*first == '*')
        return match(first+1, second) || match(first, second+1);
    return 0;
}
void wcScan(char *pathname, char *findthis){
	int buflen = 2048;
	char line[buflen];
	int line_count = 0;
	int m = 0;
//	fprintf(stderr, "Looking for %s in: %s\n",findthis ,pathname);
	FILE* pFile;
	pFile = fopen(pathname, "r");
	if (pFile == NULL){
	  fprintf(stderr, "Unable to open: %s\n", pathname);
	}
	else{
	  while(fgets(line, buflen, pFile) != NULL){
	    line_count++;
	    m = match(line, findthis);
	    if(m != 0){
//	      fprintf(stdout, "%d \n", m);
	      fprintf(stdout, "\"%s\" found on line %d in: %s\n", findthis, line_count, pathname);		      
	    }
	  }
	  fclose(pFile);	  
	}	
}

int match_dot(char *compare, char *findthis){

	char *w1;
	char *w2;
	printf("compare:%s , find:%s \n", compare, findthis);	
	int ii = 0;
	int pos = 0;
	char *match1;
	char *match2;	//testing.one 
	int len = strlen(findthis);
	int clen = 0;
	int lw1 = 0;
	int lw2 = 0;
	for(ii = 0; ii < len; ii++)
	{
		if(findthis[ii] == '.')
		{ pos = ii;	}
	}
	splitdot(findthis, pos, w1, w2);
	w2[2] = '\0';
	w1[2] = '\0';
	fprintf(stderr, "in:%s  pos:%d out1:%s   out2:%s    \n ", findthis, pos, w1, w2);
//	w2[2] = '\0';
	
	clen = strlen(w2);
	char line[2];

//	for(ii = 0; ii < 5; ii++)
//	{
//		line[ii] = compare[ii];
	
//	}
//	line[4] = '\0';
	lw1 = strlen(w1); lw2 = strlen(w2);
	fprintf(stderr, "w1:%d w2:%d \n" , lw1, lw2);
//	match1 = strstr(line, w1);
//	match1 = strstr(line, w1);//
//	if(match1 == NULL)
//	{ return 0;		}
//	match2 = strstr(compare, w2);
//	printf("m1:%s  m2:%s \n", match1, match2);

}

int cdot(char *pathname, char *findthis){//pathname, findthis
	fprintf(stderr, "CDOT ENTERED \n");
	int buflen =1024;
	char line[buflen];
	int line_count = 0;
	int m = 0;
	int len = strlen(findthis);
	int ii = 0;
	int count = 0;

//	fprintf(stderr, "Looking for %s in: %s\n",findthis ,pathname);
	FILE* pFile;
	pFile = fopen(pathname, "r");
	if (pFile == NULL){
	  fprintf(stderr, "Unable to open: %s\n", pathname);
	}
	else{
	  while(fgets(line, buflen, pFile) != NULL){	  
	  fprintf(stderr, "line: %s\n", line);
	    line_count++;
	    m = match_dot(line, findthis);
	    if(m != 0){
//	      fprintf(stdout, "%d \n", m);
	      fprintf(stdout, "\"%s\" found on line %d in: %s\n", findthis, line_count, pathname);
	      	      
	    }
	  }
	  fclose(pFile);	  
	}	  
}
int cstar(char *pathname, char *findthis){

}
int cqmark(char *pathname, char *findthis){

}




//---------------------------------------------------------------------
int myfunc(const char *pathname, const struct stat *statptr, int type)
{
//	fprintf(stderr, "%s\n", pathname);
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


