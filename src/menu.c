#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>


#ifdef _WIN32
#include <conio.h>
#else
#include <locale.h>
#include "linx_conio.h"
#endif


#ifdef  _WIN32
#define clear_screen() system("cls")
#else
#define clear_screen() system("clear")
#endif


extern int file_magic(FILE *stream, FILE *output);
extern int menu();
int file_check_and_operatin(char in_file_name[], uint8_t stdin_on,  char out_file_name[], uint8_t stdout_on);

#define NUM_OF_MENU_ENTRYS  5  //(sizeof(menu_choice) / sizeof(char))
#define IN_NAME_BUFFER 200




int menu()
{


  char *menu_choice[] = {
    "Вход файл Изход file",
    "Вход файл Изход терминал",
    "Вход терминал Изход терминал",
    "Choice 4",
    "Exit"
  };

  uint8_t selection = 0;

  while (1)
  {
    char  ch;
    clear_screen();
    for (int i = 0; i < NUM_OF_MENU_ENTRYS; ++i)
    {
      if (i == selection)
      {
        printf("--> %s\n" , menu_choice[i] );
      }
      else
      {
        printf("    %s\n", menu_choice[i] );
      }
    }

    ch = getch();

    switch (ch)
    {
    case 4 :
    case 'q':
    {

      exit(0);
      break;
    }

    case 'w':
    case 65:
    {
      if (selection > 0)
      {
        selection--;
      }
      break;
    }

    case 's':
    case 66:
    {
      if (selection < NUM_OF_MENU_ENTRYS - 1)
      {
        selection++;
      }
      break;
    }

    case 10:
    {
      switch (selection + 1)
      {
      case 1:
      {
        puts(" 1");

        char namein[IN_NAME_BUFFER ];
        char nameout[IN_NAME_BUFFER];

        printf("Въведи име на входния файл\n");
        fgets(namein, IN_NAME_BUFFER, stdin);

        uint16_t legth = strlen(namein);

        namein[legth - 1] = '\0';

        if (namein[legth - 3] != '.' || namein[legth - 2] != 'c' )
        {
          puts("въведи с фаил");
          exit(1);
        }



        printf("Въведи име на Изход файл\n");
        fgets(nameout, IN_NAME_BUFFER, stdin);
        nameout[strlen(nameout) - 1] = '\0';



        return file_check_and_operatin(namein, 0, nameout, 0);

        break;
      }
      case 2:
      {
        puts(" 2");

        char namein[IN_NAME_BUFFER ];


        printf("Въведи име на входния файл\n");
        fgets(namein, IN_NAME_BUFFER, stdin);

        uint16_t legth = strlen(namein);

        namein[legth - 1] = '\0';

        if (namein[legth - 3] != '.' || namein[legth - 2] != 'c' )
        {
          puts("въведи с фаил");
          exit(1);
        }

        return file_check_and_operatin(namein, 0, "", 1);
      }
      case 3:
      {
        puts(" 3");

        printf("Въведи C код\n");
        return file_check_and_operatin("", 1, "", 1);
        break;
      }
      case 4:
      {
        char nameout[IN_NAME_BUFFER];
        printf("Въведи име на Изход файл\n");
        fgets(nameout, IN_NAME_BUFFER, stdin);
        nameout[strlen(nameout) - 1] = '\0';


        printf("Въведи C код\n");
        return file_check_and_operatin("", 1, nameout, 0);
        break;
      }

       
      }

      return selection + 1;
      break ;
    }
    }

  }


}





int file_check_and_operatin(char in_file_name[], uint8_t stdin_on,  char out_file_name[], uint8_t stdout_on)
{
  FILE *stream = (stdin_on ) ? stdin  :  fopen(in_file_name, "rb");
  FILE *output = (stdout_on) ? stdout :  fopen(out_file_name, "w");

  if (stream == NULL || output == NULL)
  {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  file_magic(stream, output);

  fclose(stream);
  fclose(output);
  return 0;
}