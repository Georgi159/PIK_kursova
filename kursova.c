#pragma warning(disable:4996)

#include <conio.h>	
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <conio.h>

#define clear_screen() system("cls")
int file_magic(FILE *stream, FILE *output);

#define NUM_OF_MENU_ENTRYS  5  //(sizeof(menu_choice) / sizeof(char))
#define IN_NAME_BUFFER 200

#define PAUSE_EXIT(exit_code) system("pause"); exit(exit_code);

// extern int file_magic(FILE *stream,FILE *output);
 int menu();
 int file_check_and_operatin(char in_file_name[], uint8_t stdin_on, char out_file_name[], uint8_t stdout_on);


int main(void)
{
	system("chcp 1251 >nul 2>&1");
	
	menu();
		
	
	PAUSE_EXIT(EXIT_SUCCESS);
} 



int menu()
{


	char *menu_choice[] = {
	  "Вход файл Изход file",
	  "Вход файл Изход терминал",
	  "Вход терминал Изход терминал",
	  "Вход терминал ",
	  "Exit"
	};

	uint8_t selection = 0;


	while (1)
	{
		char  ch;
		clear_screen();
		system("chcp 1251 >nul 2>&1");
		for (int i = 0; i < NUM_OF_MENU_ENTRYS; ++i)
		{
			if (i == selection)
			{

				printf("--> %s\n", menu_choice[i]);
			}
			else
			{
				printf("    %s\n", menu_choice[i]);
			}
		}

		ch = getch();

		switch (ch)
		{
		case 4:
		case 'q':
		{

			PAUSE_EXIT(0);
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
		case 13:
		{
			switch (selection + 1)
			{
			case 1:
			{
				puts(" 1");

				char namein[IN_NAME_BUFFER];
				char nameout[IN_NAME_BUFFER];

				printf("Въведи име на входния файл\n");
				fgets(namein, IN_NAME_BUFFER, stdin);

				size_t legth = strlen(namein);

				namein[legth - 1] = '\0';

				if (namein[legth - 3] != '.' || namein[legth - 2] != 'c')
				{
					puts("въведи с фаил");
					PAUSE_EXIT(1);
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

				char namein[IN_NAME_BUFFER];


				printf("Въведи име на входния файл\n");
				fgets(namein, IN_NAME_BUFFER, stdin);

				size_t legth = strlen(namein);

				namein[legth - 1] = '\0';

				if (namein[legth - 3] != '.' || namein[legth - 2] != 'c')
				{
					puts("въведи с фаил");
					PAUSE_EXIT(1);
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
			break;
		}
		}

	}


}





int file_check_and_operatin(char in_file_name[], uint8_t stdin_on, char out_file_name[], uint8_t stdout_on)
{
	FILE *stream = (stdin_on) ? stdin : fopen(in_file_name, "rb");
	FILE *output = (stdout_on) ? stdout : fopen(out_file_name, "w");

	if (stream == NULL || output == NULL)
	{
		perror("fopen");
		PAUSE_EXIT(EXIT_FAILURE);
	}

	file_magic(stream, output);

	if (stream != stdin)
	{
		fclose(stream);
	}

	if (output != stdout)
	{
		fclose(output);
	}
	
	return (int)0;
}


#define READ_SIZE 500

#define IS_VAR(var,not_beginig_detection) (( \
				( (var)>='A' && (var)<='Z') || \
				( (var)>='a' && (var)<='z') || \
				( (var)>='0' && (var)<='9' && (not_beginig_detection)) || \
				( (var) == '_' ) \
				)?1:0)




int file_magic(FILE *stream, FILE *output)
{

	char line[READ_SIZE + 3] = { 0 };

	union
	{
		uint8_t all_flags;
		struct
		{
			uint8_t	sigleline_coment : 1;
			uint8_t	multiline_coment : 1;
			uint8_t	string : 1;
			uint8_t	ch : 1;
		};
	} flags = { 0 };

	struct
	{
		uint8_t  start;
		uint8_t  couted;
		uint32_t count;
	} var = { 0, 0, 0};


	int left = 0, right = 0, pairs = 0;
	uint8_t error = 0;


	for (int i = 0; fgets(&line[2], READ_SIZE, stream); ++i)
	{

		for (int k = 2; line[k] != '\0'; ++k)
		{

			switch (line[k])
			{

			case '\n':
			{
				flags.sigleline_coment = 0;
				break;
			}


			case '"':
			{

				if (line[k - 1] == '\\') break;
				if (line[k - 1] == '\'') break;
				if (flags.multiline_coment || flags.sigleline_coment) break;

				flags.string = !flags.string;

				break;
			}

			case '\'':
			{
				if (line[k - 1] == '\\'  && line[k - 2] != '\\') break;
				// if (line[k - 1] == '\'') break;
				if (flags.multiline_coment || flags.sigleline_coment || flags.string) break;

				flags.ch = !flags.ch;
				break;
			}

			case '*':
			{
				if (line[k - 1] == '/')
				{
					flags.multiline_coment = 1;
				}

				break;
			}

			case '/':
			{
				if (line[k - 1] == '/')
				{
					flags.sigleline_coment = 1;
				}


				if (line[k - 1] == '*')
				{
					flags.multiline_coment = 0;
				}
				break;
			}

			case  '{':
			{
				if (flags.all_flags)
				{
					break;
				}

				right++;
				break;
			}
			case  '}':
			{

				if (flags.all_flags)
				{
					break;
				}

				if (right > left)
				{
					pairs++;
				}

				left++;

				if (right < left)
				{
					error = 1;
				}

				break;
			}

			}


			if (IS_VAR(line[k], var.start) && !flags.all_flags)
			{
				if (var.start == 0)
				{
					var.start = 1;
					var.couted = 0;
				}

			}
			else
			{
				if (var.couted == 0 && var.start == 1)
				{
					var.count++;
					var.couted = 1;
					var.start = 0;
				}
			}


		}


	}
	if (right != left)
	{
		error = 1;
	}

	fprintf(output, "Блокове код = %d \nгрешки = %s \nброй \"променливи\" = %d\n", pairs, (error) ? "има" : "няма", var.count);

	return 0;
}