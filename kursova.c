#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>


extern int file_magic(FILE *stream,FILE *output, unsigned char File_in, char *line, unsigned size_of_line  , unsigned char stream_in);
extern int menu();





int main(int argc, char *argv[])
{
	#ifdef  _WIN32
        #pragma warning(disable:4996)
		system("chcp 1251 >nul 2>&1");
	#else
		// setlocale(LC_ALL, "UTF8");
		setlocale(LC_ALL, "");
	#endif

	menu();
	

	exit(EXIT_SUCCESS);
} 

