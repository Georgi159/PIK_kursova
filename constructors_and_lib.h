#ifdef  _WIN32
    #pragma warning(disable:4996)
	#include <conio.h>	
#else
	#include <locale.h>
	#include "linx_conio.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>




int file_magic(FILE *stream, FILE *output);

int menu();

#define NUM_OF_MENU_ENTRYS  5  //(sizeof(menu_choice) / sizeof(char))
#define IN_NAME_BUFFER 200


#ifdef  _WIN32
#define clear_screen() system("cls")
#else
#define clear_screen() system("clear")
#endif