#ifdef  _WIN32
    #pragma warning(disable:4996)
	#include <conio.h>	
#else
	#include <locale.h>
#endif

#include <stdio.h>
#include <stdlib.h>



// extern int file_magic(FILE *stream,FILE *output);
extern int menu();



int main(void)
{
	#ifdef  _WIN32
		system("chcp 1251 >nul 2>&1");
	#else
		setlocale(LC_ALL, "");
	#endif
	menu();
		
		

	exit(EXIT_SUCCESS);
} 

