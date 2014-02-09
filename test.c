

#include "string.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char *argv[])
{

int num = atoi(argv[1]);;
write(1,argv[1] ,sizeof(argv[1]));
printf("%d\n" , num);
printf("%s\n",argv[1]);
printf("%d\n",argc);


}
