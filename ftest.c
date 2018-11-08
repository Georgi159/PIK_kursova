#include <stdio.h>
#include <stdlib.h>

#include <locale.h>


int main(int argc, char const *argv[])
{
		FILE *fp=fopen("test.c","rb");

char s [500];
	while(fgets(s, 500,	fp))
	{
		printf("_________________________________\n");
		printf("%s", s);
	}


	return 0;
}