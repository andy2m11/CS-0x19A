#include <stdin>
#include <stdio>
#include <stdlib>



int main(int argc, char *argv)
{

int mat1[10][10];
int mat2[10][10];
int arows = 0;
int acols = 0;
int brows = 0;
int bcols = 0;
int xx = 0; int yy = 0;
int space = 0;
   char  line[1024];
   char  *line_res;
   char **args;


        while(line[0] != '\n' && space < 2)
        {	
                line_res = fgets(line, 1024, stdin);
		//remove the new line character to avoid it being included by strtok
		int len = strlen(line);
		if( len > 0 && line[len-1] == '\n')
		{   line[len-1] = '\0';	}
		
	   	//use strtok function to split the arguments up    
		int argc1 = 0;
		int argc2 = 0;
		char *token;
		token = strtok(line," ");
		while (token != NULL) {
		    args[argc1] = token;
		    token = strtok (NULL," ");
		    argc1++;
		}	
	
		for(yy = 0; yy < argc1; yy++)
		{
			mat1[xx][yy] = atoi(args[yy]);
		
		}
	 
	}	
	
	int matA[arows][acols]={0};
	int matB[brows][bcols]={0};
	int matC[xx][yy]={0};
	int i,j,k;
	    for (i=0;i<2;i++){
		for(j=0;j<2;j++){
		        for(k=0;k<2;k++){
		        matC[i][j] += matA[i][k] * matB[k][j];
		    } 
		} 
	    }	

	
	
		if(acols == brows)
		{


		}
		else
		{
	
	
		}
		
	
}

