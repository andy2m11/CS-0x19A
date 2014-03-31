#include <stdio.h>
#include <stdlib.h>




int splitdot(char *input, int dotpos, char **out1, char **out2){

int len = strlen(input);

printf("len =%d, dotpos=%d \n", len, dotpos);

memmove(*out1, input, dotpos);
memmove(*out2, input+dotpos+1, len-dotpos);


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
//	for(ii = 0; ii < clen; ii++)
//	{
//		line[1] = compare[1];
	
//	}
//	line[10] = '\0';
	lw1 = strlen(w1); lw2 = strlen(w2);
	fprintf(stderr, "w1:%d w2:%d \n" , lw1, lw2);
	match1 = strstr(compare, w1);
//	match1 = strstr(line, w1);//
//	if(match1 == NULL)
//	{ return 0;		}
//	match2 = strstr(compare, w2);
//	printf("m1:%s  m2:%s \n", match1, match2);
/*
	if(match1 + 1 == match2)
	{	printf("m1:%s  m2:%s \n", match1, match2);
		return 1;
	}
	else
	{
		return 0;
	}
*/
}

int cdot(char *pathname, char *findthis){//pathname, findthis
	fprintf(stderr, "CDOT ENTERED \n");
	int buflen = 2048;
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


/////////////////////////////////
int main(){

printf("This is a split test\n");

char *str1 = "testing.one";
char *w1;
char *w2;

int ii = 0;
int chk = 0;
int pos = 0;
int len = strlen(str1);
for(ii = 0; ii < len; ii++)
{
	if(str1[ii] == '.')
	{ pos = ii;	}
}
chk = splitdot(str1, pos, &w1, &w2);


printf("in:%s  pos:%d out1:%s   out2:%s    \n ", str1, pos, w1, w2);

};
