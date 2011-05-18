#include "pause.h"
#include "game.h"
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include <string.h>

int pause_game(WINDOW *term, int x_ofs, int y_ofs)
{	       
    int option_selected = 0;
    
    ITEM **my_items;
	int c;				
	MENU *my_menu;
    WINDOW *my_menu_win;
    int n_choices, i;
	
	/* Initialize curses */
	//initscr();
	//start_color();
    //cbreak();
    //noecho();
    
    
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
    
	/* Create items */
    n_choices = 4;
    my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));    
    my_items[0] = new_item((char *)"Continuar Jogo", (char *)"");
    my_items[1] = new_item((char *)"Menu Principal", (char *)"");    
    my_items[2] = new_item((char *)"Sair", (char *)"");
    my_items[3] = new_item((char *)NULL, (char *)"");
    
	// Crate menu
	my_menu = new_menu((ITEM **)my_items);
    
	// Create the window to be associated with the menu
    my_menu_win = newwin(8, 40, 8, 20);
    keypad(my_menu_win, TRUE);
    
	// Set main window and sub window
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 5, 38, 3, 1));
    
	// Set menu mark to the string " * "
    set_menu_mark(my_menu, " -> ");
    
	// Print a border around the main window and print a title
    box(my_menu_win, 0, 0);
	print_in_middle_pause(my_menu_win, 1, 0, 40, "Jogo em pausa", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
	refresh();
    
    // Open the sounds
    NSSound *change = [[NSSound alloc] initWithContentsOfFile:@"resources/Change.wav" byReference:YES];
    NSSound *select = [[NSSound alloc] initWithContentsOfFile:@"resources/Select.wav" byReference:YES];
    
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
                
                if (strcmp(item_name(current_item(my_menu)), "Continuar Jogo") == 0)
                {
                    option_selected = CONTINUAR_JOGO;
                }
                else if (strcmp(item_name(current_item(my_menu)), "Menu Principal") == 0)
                {
                    option_selected = MENU_PRINCIPAL;
                }                
                else if (strcmp(item_name(current_item(my_menu)), "Sair") == 0)
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

void print_in_middle_pause(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
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

