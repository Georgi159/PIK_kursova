#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
// #include <wchar.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <errno.h>
#include <locale.h>

// initscr();			/* Start curses mode 		  */
// mvprintw(10,10,"Hello World !!!");	/* Print Hello World		  */
// cbreak();
// keypad(stdscr, TRUE);
// move(35,45); 
// char ch = 's';
// addch(ch | A_BOLD | A_UNDERLINE);
// refresh();			/* Print it on to the real screen */
// getch();
// //halfdelay()
// endwin();			/* End curses mode		  */

#define READ_SIZE 100


int main(int argc, char *argv[])
{
	FILE *stream;
	char *line = malloc(sizeof(char)*READ_SIZE+2);
	// size_t linen = 0;
	

	if (argc != 2) 
	{
	fprintf(stderr, "Usage: %s <file>\n", argv[0]);
	exit(EXIT_FAILURE);
	}
	stream = fopen(argv[1], "r");

	fseek(stream, 0L, SEEK_END);
	int sz = ftell(stream);
	rewind(stream);

    printf("%d\n",sz );

	
	if (stream == NULL) 
	{
	perror("fopen");
	exit(EXIT_FAILURE);
	}

	int read_size=READ_SIZE;

	// (sz/READ_SIZE == i +1 && sz%READ_SIZE != 0)

	for (int i = 0; i < sz/READ_SIZE  ||  (sz/READ_SIZE == i +1 && sz%READ_SIZE != 0) ; ++i)
	{
		if (sz/READ_SIZE == i)
		{
			read_size=sz%READ_SIZE;
	//		printf("%d\n",read_size );
		}

		fread(line+1, sizeof(char), read_size, stream);

		 printf("i= %d  sz/READ_SIZE = %d , read_size=%d\n",i, sz/READ_SIZE,read_size );
		fwrite(line, sizeof(char), read_size,stdout);
		//puts("\n--------------------");
	}
	// {} 
/*  

sdasfsdfsd

{}



 */

 // '{' '}'
	// "dasfs{}}d'{f"


	// printf("%d\n",sz/READ_SIZE  );

	free(line);
	fclose(stream);
	exit(EXIT_SUCCESS);
}


