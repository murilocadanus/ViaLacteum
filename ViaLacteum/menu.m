#include "menu.h"
#include "game.h"
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

int menu(WINDOW *term, int x_ofs, int y_ofs)
{	       
    int option_selected = 0;
    
    ITEM **my_items;
	int c;				
	MENU *my_menu;
    WINDOW *my_menu_win;
    int n_choices, i;
	
	/* Initialize curses */
	initscr();
	start_color();
    cbreak();
    noecho();
    
    SET_COLOR(COL_GREEN);
    mvprintw( LINES - 23, 1, " ___  __    _  _________  ______   __   __  ______   _______  ______   _______ ");
    mvprintw( LINES - 22, 1, "|   ||  |  | | |       | |    _ | |  | |  ||      \\ |       ||    _ | |       |");
    mvprintw( LINES - 21, 1, "|   ||   |_| |   |   |   |   | || |  | |  ||   _   ||    ___||   | || |  _____|");
    mvprintw( LINES - 20, 1, "|   ||       |   |   |   |   |_|| |  | |  ||  | |  ||   |___ |   |_|| | |_____ ");
    mvprintw( LINES - 19, 1, "|   ||  _    |   |   |   |    __| |  |_|  ||  |_|  ||    ___||    __| |_____  |");
    mvprintw( LINES - 18, 1, "|   || | |   |   |   |   |   |  | |       ||       ||   |___ |   |  |  _____| |");
    mvprintw( LINES - 17, 1, "|___||_|  |__|   |___|   |___|  | |_______||______/ |_______||___|  | |_______|");
    
    
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
    
	/* Create items */
    n_choices = 4;
    my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));    
    my_items[0] = new_item((char *)"New game", (char *)"");
    my_items[1] = new_item((char *)"Credits", (char *)"");
    my_items[2] = new_item((char *)"Quit", (char *)"");
    my_items[3] = new_item((char *)NULL, (char *)"");
    
	// Crate menu
	my_menu = new_menu((ITEM **)my_items);
    
	// Create the window to be associated with the menu
    my_menu_win = newwin(8, 40, 12, 20);
    keypad(my_menu_win, TRUE);
    
	// Set main window and sub window
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 5, 38, 3, 1));
    
	// Set menu mark to the string " * "
    set_menu_mark(my_menu, " -> ");
    
	// Print a border around the main window and print a title
    box(my_menu_win, 0, 0);
	print_in_middle_menu_win_example(my_menu_win, 1, 0, 40, "Watch your surroundings!", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
    mvprintw(LINES - 3, 4, "Press <ENTER> to select a menu option");
	mvprintw(LINES - 2, 4, "Use the arrows key to navigate");
	refresh();
    
    // Open the sounds
    NSSound *change = [[NSSound alloc] initWithContentsOfFile:@"resources/Change.aif" byReference:YES];
    NSSound *select = [[NSSound alloc] initWithContentsOfFile:@"resources/Select.aif" byReference:YES];
    
	// Post the menu
	post_menu(my_menu);
	wrefresh(my_menu_win);
    
	while(!option_selected)
	{   
        c = wgetch(my_menu_win);
        
        switch(c)
        {	
            case KEY_DOWN:
                [change setCurrentTime:0.0];
                [change play];
				menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
			case KEY_UP:
                [change setCurrentTime:0.0];
                [change play];
				menu_driver(my_menu, REQ_UP_ITEM);
                break;
			case ENTER_KEY: // Enter
                [select setCurrentTime:0.0];
                [select play];
                if (strcmp(item_name(current_item(my_menu)), "New game") == 0)
                {
                    option_selected = NOVO_JOGO;
                }
                else if (strcmp(item_name(current_item(my_menu)), "Credits") == 0)
                {
                    option_selected = CREDITOS;
                }
                else if (strcmp(item_name(current_item(my_menu)), "Quit") == 0)
                {
                    option_selected = SAIR;
                }
                
				break;
		}
        wrefresh(my_menu_win);
        refresh();
	}
    
    wclear(term);
    
	/* Unpost and free all the memory taken up */
    unpost_menu(my_menu);
    free_menu(my_menu);
    for(i = 0; i < n_choices; ++i)
        free_item(my_items[i]);
	endwin();
    
    return option_selected;
}

void print_in_middle_menu_win_example(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;
    
	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;
    
	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

