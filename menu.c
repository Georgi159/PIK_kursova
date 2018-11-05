#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include <locale.h>



extern int file_magic(FILE *stream,FILE *output, unsigned char File_in, char *line, unsigned size_of_line  , unsigned char stream_in);

extern int menu();

#define NUM_OF_MENU_ENTRYS 5
#define IN_NAME_BUFFER 200

int file_check_and_operatin(char in_file_name[])
{
	clear();
    endwin();

	FILE *stream;
	stream = fopen(in_file_name, "rb");

	if (stream == NULL) 
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	file_magic(stream,stdout, 1 , NULL, 0, 0 );

 	fclose(stream);
	return 0;
}


int menu()
{

	
	char *menu_choice[] = {
                        "Вход файл Изход file",
                         "Вход файл Изход терминал",
                        "Вход терминал Изход терминал",
                        "Choice 4",
                        "Exit",
                  };

    initscr();
    cbreak();
    noecho();
	keypad(stdscr, TRUE);   




	if(has_colors() == FALSE)
	{	
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
    
    start_color();	
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    WINDOW *menu_sel= newwin(10,50, 18, 15);

    // mvwprintw(menu_sel,2,4,"adsdddddddddddd");
    wrefresh(stdscr);
    wrefresh(menu_sel);

	char selection =0;
	// wrefresh(stdscr);
    // wrefresh(menu_sel);
     noecho();
    curs_set(0);
    mvwprintw(menu_sel,2,4,"adsdddddddddddd");


    while(1)
    {


    	for (int i = 0; i < NUM_OF_MENU_ENTRYS; ++i)
    	{
    		if (i==selection)
    		{
    			wattron(menu_sel,COLOR_PAIR(1));
    			mvwprintw(menu_sel,i+2,4,"%s",menu_choice[i]);
    			wattroff(menu_sel,COLOR_PAIR(1));	
    		}
    		else
    		{
    			mvwprintw(menu_sel,i+2,4,"%s",menu_choice[i]);
    		}

   			
    	}
    	wborder(menu_sel, '|', '|', '-', '-', 0, 0, 0, 0);
    	// wborder(stdscr, '|', '|', '-', '-', 0, 0, 0, 0);
	
    	wrefresh(menu_sel);
    	char ch = getch();


    //	mvprintw(30,30,"%d",ch);

    	
    	
    	// while(getch()!=ERR);

    	switch(ch)
    	{
    		case 4 :
    		case 'q':
    		{
    			endwin();
    			exit(0);
    			break;	
    		}

    		case 'w': 
    		case 3: 
    		{
    			if (selection > 0)
    			{
    				selection--;
    			}
    			break;	
    		} 
				
			case 's':
			case 2: 
			{
				if (selection < NUM_OF_MENU_ENTRYS-1)
    			{
    				selection++;
    			}
    			break;	
    		} 

    		case 10:
    		{
    			switch(selection+1)
				{
					case 0:
					{
			    			puts(" 0"); 

			    			break ;
			    	}
					case 1:
					{
						puts(" 1");
						file_check_and_operatin("test.c");

						break;
					}
					case 2:
					{
						puts(" 2");
						WINDOW *input= newwin(10,50, 10, 4);
      					mvwprintw(input,2,4,"%s","Въведи името на входния файл");
      
      					wborder(input, '|', '|', '-', '-', 0, 0, 0, 0);
      					wrefresh(input);

      					

      					char name[IN_NAME_BUFFER+1];
      					 char ch_in;
      					for (int i = 0; i < IN_NAME_BUFFER; ++i)
      					{

      						ch_in = getch();

      						if (ch_in==4 || ch_in==10 || ch_in ==0)
      						{
      							name[i]='\0';
      							break;

      						}
      						name[i]=ch_in;
      						mvwprintw(input,3,4+i,"%c",ch_in);
      						wrefresh(input);
      					}
    					
      					mvwprintw(input,4,4,"%s\n",name);
      					wrefresh(input);

						file_check_and_operatin(name);
						break;
					}
					case 3:
					{
						puts(" 3");
						WINDOW *input= newwin(10,50, 10, 10);
      					mvwprintw(input,2,4,"%s","Въведи входния код");
      
      					wborder(input, '|', '|', '-', '-', 0, 0, 0, 0);
      					wrefresh(input);

      					char *terminal_code = malloc(sizeof(char)*IN_NAME_BUFFER+2);
      					unsigned int multiplier = 1 ;
      				
      					char ch_in;
      					for (int i = 0; i < IN_NAME_BUFFER * multiplier; ++i)
      					{

      						ch_in = getch();

      						if (ch_in==4  || ch_in ==0)
      						{
      							terminal_code[i]='\0';
      							break;

      						}

      						if (IN_NAME_BUFFER * multiplier - 10 < i )
      						{
      							multiplier++;
      							terminal_code= realloc(terminal_code, IN_NAME_BUFFER * multiplier);
      							if (terminal_code == NULL)
      							{
      								exit(2);
      							}
      						}

      						terminal_code[i]=ch_in;

      						wprintw(input, "%c", ch_in);
      						// mvwprintw(input,3,4+i,"%c",ch_in);
      						wrefresh(input);
      					}
    					
      					mvwprintw(input,4,4,"%s\n",terminal_code);
      					wrefresh(input);
      					endwin();

						file_check_and_operatin("test.c");
						break;
					}
					case 4:puts(" 4"); break; 
				}
    			
				endwin();
    			return selection+1;
    			break ;
    		}
		}

		

    	
    	
    	wrefresh(stdscr);
    	wrefresh(menu_sel);
    }

    clear();
    refresh();
    endwin();	
}