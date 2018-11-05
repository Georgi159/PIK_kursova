#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include <locale.h>



extern int file_magic(FILE *stream,FILE *output);
extern int menu();

#define NUM_OF_MENU_ENTRYS 5

int file_check_and_operatin(char in_file_name[])
{

	FILE *stream;
	stream = fopen("test.c", "rb");

	if (stream == NULL) 
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	file_magic(stream,stdout);

	fclose(stream);
	return 0;
}


int menu()
{

	
	char *menu_choice[] = {
                        "Вход файл Изход терминал",
                        "Choice 2",
                        "Choice 3",
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
    	mvprintw(30,30,"%d",ch);

    	
    	
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

    			endwin();
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
						file_check_and_operatin(NULL);

						break;
					}
					case 2:puts(" 2"); break;
					case 3:puts(" 3"); break;
					case 4:puts(" 4"); break; 
				}
    			
    			
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