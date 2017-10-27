#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	for(int i = 0; i < 19; i++)
	{
		int *p = (int *)malloc(1024 * 1024 * 1024);
		memset(p, 0, 1024 * 1024 * 1024 );
		
		if(p == NULL)
		{
			printf("err\n");
		}
		else
		{
			printf("ok\n");
		}	
		
	}
	
	getchar();
	return 0;
}