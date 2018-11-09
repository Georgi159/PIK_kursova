// #include <stdio.h>
// #include <stdlib.h>
// #include <ncurses.h>
// // #include <wchar.h>
// // #include <stdlib.h>
// // #include <stdio.h>
// // #include <errno.h>
// #include <locale.h>

// // initscr();			/* Start curses mode 		  */
// // mvprintw(10,10,"Hello World !!!");	/* Print Hello World		  */
// // cbreak();
// // keypad(stdscr, TRUE);
// // move(35,45); 
// // char ch = 's';
// // addch(ch | A_BOLD | A_UNDERLINE);
// // refresh();			/* Print it on to the real screen */
// // getch();
// // //halfdelay()
// // endwin();			/* End curses mode		  */

// #define READ_SIZE 100


// int main(int argc, char *argv[])
// {
// 	FILE *stream;
// 	char *line = malloc(sizeof(char)*READ_SIZE+2);
// 	// size_t linen = 0;
	

// 	if (argc != 2) 
// 	{
// 	fprintf(stderr, "Usage: %s <file>\n", argv[0]);
// 	exit(EXIT_FAILURE);
// 	}
// 	stream = fopen(argv[1], "r");

// 	fseek(stream, 0L, SEEK_END);
// 	int sz = ftell(stream);
// 	rewind(stream);

//     printf("%d\n",sz );

	
// 	if (stream == NULL) 
// 	{
// 	perror("fopen");
// 	exit(EXIT_FAILURE);
// 	}

// 	int read_size=READ_SIZE;

// 	// (sz/READ_SIZE == i +1 && sz%READ_SIZE != 0)

// 	for (int i = 0; i < sz/READ_SIZE  ||  (sz/READ_SIZE == i +1 && sz%READ_SIZE != 0) ; ++i)
// 	{
// 		if (sz/READ_SIZE == i)
// 		{
// 			read_size=sz%READ_SIZE;
// 	//		printf("%d\n",read_size );
// 		}

// 		fread(line+1, sizeof(char), read_size, stream);

// 		 printf("i= %d  sz/READ_SIZE = %d , read_size=%d\n",i, sz/READ_SIZE,read_size );
// 		fwrite(line, sizeof(char), read_size,stdout);
// 		//puts("\n--------------------");
// 	}
// 	// {} 
// /*  

// sdasfsdfsd

// {}



//  */

//  // '{' '}'
// 	// "dasfs{}}d'{f"


// 	// printf("%d\n",sz/READ_SIZE  );

// 	free(line);
// 	fclose(stream);
// 	exit(EXIT_SUCCESS);
// }


#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <locale.h>

#define READ_SIZE 500

#define IS_VAR(var,not_beginig_detection) (( \
				( (var)>='A' && (var)<='Z') || \
				( (var)>='a' && (var)<='z') || \
				( (var)>='0' && (var)<='9' && (not_beginig_detection)) || \
				( (var) == '_' ) \
				)?1:0)




int file_magic(FILE *stream, FILE *output)
{

	char line[READ_SIZE + 2] = {0};

	union
	{
		uint8_t all_flags;
		struct
		{
			uint8_t	sigleline_coment: 1;
			uint8_t	multiline_coment: 1;
			uint8_t	string: 1;
			uint8_t	ch: 1;
		};
	} flags = {0};

	struct
	{
		uint8_t  start;
		uint8_t  couted;
		uint32_t count;
	} var = {0, 0, 0};


	int left = 0, right = 0, pairs = 0;
	uint8_t error = 0;


	for (int i = 0; fgets(&line[1], READ_SIZE, stream ) ; ++i)
	{

		for (int k = 1; line[k] != '\0' ; ++k)
		{


			switch (line[k])
			{

			case '\n':
			{
				flags.sigleline_coment = 0;
				break;
			}

		// }}}
			case '"':
			{

				if (line[k - 1] == '\\') break;
				if (line[k - 1] == '\'') break;
				if (flags.multiline_coment || flags.sigleline_coment) break;

				flags.string = ! flags.string;

				break;
			}
			// case '\\':

			case '\'' :
			{
				if (line[k - 1] == '\\') break;
				if (line[k - 1] == '\'') break;
				if (flags.multiline_coment || flags.sigleline_coment || flags.string) break;

				flags.ch = !flags.ch;
				break;
			}

			case '*':
			{
				if (line[k - 1] == '/' )
				{
					flags.multiline_coment = 1;
				}

				break;
			}

			case '/':
			{
				if (line[k - 1] == '/' )
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


			if (IS_VAR( line[k], var.start ) && !flags.all_flags)
			{
				if (var.start == 0)
				{
					var.start  = 1;
					var.couted = 0;
				}

			}
			else
			{
				if (var.couted == 0)
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

	printf("%d %d %d\n", right , left , flags.all_flags );
	fprintf(output, "Блокове код = %d \nгрешки = %s \nброй \"променливи\" = %d\n", pairs , (error)? "има" : "няма", var.count);

	return 0;
}