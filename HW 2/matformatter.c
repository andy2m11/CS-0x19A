#include <stdio.h>
#include <stdlib.h>



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
   args = malloc(1024 *sizeof(char*));
   line_res = malloc(1024 *sizeof(char*));


        while(line[0] != '\n' && space < 1)
        {	
        
	        line_res = fgets(line, 1024, stdin);	
                if(line[0] == '\n')
                {
                        if(space == 0)
                        {arows = xx;}
                        else
			{brows = xx;}
                        xx = 0;
                        space++;
                }
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
		
		if(space == 0)
		{acols = argc1;}
		else
		{bcols = argc1;}
		
		for(yy = 0; yy < argc1; yy++)
		{
                        mat1[xx][yy] = atoi(args[yy]);

		}
		xx++;
	 
	}
printf("arows:%d acols:%d  \n", arows, acols);	
int counting = 0; int c2 = 0;
for(counting = 0; counting < acols; counting++)
{
	for(c2 = 0; c2 < arows; c2++)
	{
	
	printf("%d ",mat1[c2][counting]);
	}
	printf("\n");

}
}

