#include<unistd.h>
#include <stdio.h>

int main(){
	int x = 0;
	x = 5+7;
	printf( "now? %d \n" , x);
	write(1,"Hello World\n",12);
	return 0;
}
