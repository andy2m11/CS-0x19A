#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv)
{

int mat1[10][10];
int mat2[10][10];
int mat3[10][10];
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


        while(space < 2)//line[0] != '\n' && 
        {	
        
	        line_res = fgets(line, 1024, stdin);	
                if(line[0] == '\n')
                {
                        if(space == 0)
                        {arows = xx;}
                        else if(space == 1)
			{brows = xx;}
                        xx = 0;
                        space++;
                }
                else{
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
			else if(space == 1)
			{bcols = argc1;}
			
			if(argc1 != yy && xx != 0 )
			{
				printf("ERROR invalid matrix format\n");
				exit(-1);		
			}
			
			for(yy = 0; yy < argc1; yy++)
			{
	  //            printf("yy:%d args[yy]: %s    ",yy, args[yy], args[yy]);
		                if(space == 0)
		                {
		                mat1[xx][yy] = atoi(args[yy]);
	   //                     printf("mat:%d \n", mat1[xx][yy]);
		                }
		                else if(space == 1)
		                {
		                mat2[xx][yy] = atoi(args[yy]);
	    //                   printf("mat:%d \n", mat2[xx][yy]);                        
		                }
		
			}
			xx++;
		}
	 
	}
if(acols != brows)
{
	printf("ERROR mat A col do not match mat B rows\n");
	exit(-1);
}
	
printf("arows:%d acols:%d brows:%d bcols:%d \n", arows, acols, brows, bcols);	
printf("Mat A =\n");
int counting = 0; int c2 = 0;
for(counting = 0; counting < arows; counting++)
{
	for(c2 = 0; c2 < acols; c2++)
	{
	
	printf("%d ",mat1[counting][c2]);
	}
	printf("\n");

}

printf("Mat B =\n");
for(counting = 0; counting < brows; counting++)
{
	for(c2 = 0; c2 < bcols; c2++)
	{
	printf("%d ",mat2[counting][c2]);
	}
	printf("\n");

}

	int i,j,k;
	    for (i=0;i<arows;i++){
		for(j=0;j<bcols;j++){
			mat3[i][j]=0;
		        for(k=0;k<bcols;k++){
		        mat3[i][j] += mat1[i][k] * mat2[k][j];
		    } 
		} 
	    }	

printf("MatA * MatB = \n");
for(counting = 0; counting < arows; counting++)
{
	for(c2 = 0; c2 < bcols; c2++)
	{
	
	printf("%d ",mat3[counting][c2]);
	}
	printf("\n");

}	    

/*	
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
		
	*/
}

