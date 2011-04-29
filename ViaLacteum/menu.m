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
    mvprintw( LINES - 23, 1, " ___   __    _  __   __  _______  _______  _______  ______   _______  _______ ");
    mvprintw( LINES - 22, 1, "|   | |  |  | ||  | |  ||   _   ||       ||       ||    _ | |       ||       |");
    mvprintw( LINES - 21, 1, "|   | |   |_| ||  |_|  ||  |_|  ||  _____||   _   ||   | || |    ___||  _____|");
    mvprintw( LINES - 20, 1, "|   | |       ||       ||       || |_____ |  | |  ||   |_|| |   |___ | |_____ ");
    mvprintw( LINES - 19, 1, "|   | |  _    ||       ||       ||_____  ||  |_|  ||    __| |    ___||_____  |");
    mvprintw( LINES - 18, 1, "|   | | | |   | |     | |   _   | _____| ||       ||   |  | |   |___  _____| |");
    mvprintw( LINES - 17, 1, "|___| |_|  |__|  |___|  |__| |__||_______||_______||___|  | |_______||_______|");
    
    
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
    
	/* Create items */
    n_choices = 5;
    my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));    
    my_items[0] = new_item((char *)"Novo Jogo", (char *)"");
    my_items[1] = new_item((char *)"Opcoes ", (char *)"");
    my_items[2] = new_item((char *)"Creditos", (char *)"");
    my_items[3] = new_item((char *)"Sair", (char *)"");
    my_items[4] = new_item((char *)NULL, (char *)"");
    
	// Crate menu
	my_menu = new_menu((ITEM **)my_items);
    
	// Create the window to be associated with the menu
    my_menu_win = newwin(9, 40, 12, 20);
    keypad(my_menu_win, TRUE);
    
	// Set main window and sub window
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));
    
	// Set menu mark to the string " * "
    set_menu_mark(my_menu, " -> ");
    
	// Print a border around the main window and print a title
    box(my_menu_win, 0, 0);
	print_in_middle_menu_win_example(my_menu_win, 1, 0, 40, "Cuidado para nao ser abduzido!", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
    mvprintw(LINES - 3, 4, "Pressione <ENTER> para escolher a opcao desejada");
	mvprintw(LINES - 2, 4, "Use as setas para navegar");
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
                if (strcmp(item_name(current_item(my_menu)), "Novo Jogo") == 0)
                {
                    option_selected = NOVO_JOGO;
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

