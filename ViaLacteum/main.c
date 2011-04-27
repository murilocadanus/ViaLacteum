//
//  main.c
//  ViaLacteum
//
//  Created by Murilo Costa on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "defs.h"
#include "zombie.h"
#include "blit.h"
#include "waves.h"
#include "fire.h"
#include "menu.h"

int x_ofs = 0;
int y_ofs = 0;
int term_x = 0;
int term_y = 0;

// The terminal
WINDOW *term; 

void init_screen()
{
	term = initscr(); /* Initialize terminal */
    
	start_color(); /* Initialize colors */
	init_pair(PC_WHITE,COLOR_WHITE,COLOR_BLACK);
	init_pair(PC_RED,COLOR_RED,COLOR_BLACK);
	init_pair(PC_GREEN,COLOR_GREEN,COLOR_BLACK);
	init_pair(PC_YELLOW,COLOR_YELLOW,COLOR_BLACK);
	init_pair(PC_BLUE,COLOR_BLUE,COLOR_BLACK);
	init_pair(PC_MAGENTA,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(PC_CYAN,COLOR_CYAN,COLOR_BLACK);
	SET_COLOR(COL_BKG);
    
	cbreak(); /* Disable line buffering and erase/kill characters */
	noecho(); /* Don't echo characters */
	nodelay(term,TRUE); /* Don't block while waiting for input */
    
	nonl(); /* Don't translate return into newline, only CR */
	intrflush(term,FALSE); /* Do not flush input at ^C */
	keypad(term,TRUE); /* Enable keypad */
    
	wrefresh(term);
}

void presentation()
{       
    blit_borders(COL_BLUE);
    
    SET_COLOR(COL_GREEN);
    mvwprintw(term,8+y_ofs,25+x_ofs,"-- -= I-N-V-A-S-O-R-E-S =- --");
    mvwprintw(term,11+y_ofs,27+x_ofs,  "");
    
    //init_color_pairs();
    SET_COLOR(COL_WHITE);
    mvwprintw(term, LINES - 22, 1 ,  "         #iiiii#     ");
    mvwprintw(term, LINES - 21, 1 ,  "       #iEKWWWKEi#       ");
    mvwprintw(term, LINES - 20, 1 ,  "      iEKKKW#WKKKEi      ");
    mvwprintw(term, LINES - 19, 1 ,  "     #EWWKKW#WKKWWE#     ");
    mvwprintw(term, LINES - 18, 1 ,  "    #EWKEKWKKKWKEKWE#    ");
    mvwprintw(term, LINES - 17, 1 ,  "    #EW EWKWWWKWE WE#    ");
    mvwprintw(term, LINES - 16, 1 ,  "    #EK  EEKKKEE  KE#    ");
    mvwprintw(term, LINES - 15, 1 ,  "    #EK   EEKEE   KE#    ");
    mvwprintw(term, LINES - 14, 1 ,  "    #EK    WWW    KE#    ");
    mvwprintw(term, LINES - 13, 1 ,  "     iK    EWE    Ki     ");
    mvwprintw(term, LINES - 12, 1 ,  "     #EK   EWE   KE#     ");
    mvwprintw(term, LINES - 11, 1 ,  "     #EWEE E#E EEWE#     ");
    mvwprintw(term, LINES - 10, 1 ,  "      #KW#KKKKK#WK#      ");
    mvwprintw(term, LINES - 9, 1 ,   "       iWWWKEKWWWi       ");
    mvwprintw(term, LINES - 8, 1 ,   "        #KWKEKWK#        ");
    mvwprintw(term, LINES - 7, 1 ,   "         #KWWWK#         ");
    mvwprintw(term, LINES - 6, 1 ,   "          #KWK#          ");
    mvwprintw(term, LINES - 5, 1 ,   "           #i#           ");
    
    SET_COLOR(COL_WHITE);
    mvwprintw(term, LINES - 22, 54 ,  "         #iiiii#     ");     
    mvwprintw(term, LINES - 21, 54 ,  "       #iEKWWWKEi#       ");
    mvwprintw(term, LINES - 20, 54 ,  "      iEKKKW#WKKKEi      ");
    mvwprintw(term, LINES - 19, 54 ,  "     #EWWKKW#WKKWWE#     ");
    mvwprintw(term, LINES - 18, 54 ,  "    #EWKEKWKKKWKEKWE#    ");
    mvwprintw(term, LINES - 17, 54 ,  "    #EW EWKWWWKWE WE#    ");
    mvwprintw(term, LINES - 16, 54 ,  "    #EK  EEKKKEE  KE#    ");
    mvwprintw(term, LINES - 15, 54 ,  "    #EK   EEKEE   KE#    ");
    mvwprintw(term, LINES - 14, 54 ,  "    #EK    WWW    KE#    ");
    mvwprintw(term, LINES - 13, 54 ,  "     iK    EWE    Ki     ");
    mvwprintw(term, LINES - 12, 54 ,  "     #EK   EWE   KE#     ");
    mvwprintw(term, LINES - 11, 54 ,  "     #EWEE E#E EEWE#     ");
    mvwprintw(term, LINES - 10, 54 ,  "      #KW#KKKKK#WK#      ");
    mvwprintw(term, LINES - 9, 54 ,   "       iWWWKEKWWWi       ");
    mvwprintw(term, LINES - 8, 54 ,   "        #KWKEKWK#        ");
    mvwprintw(term, LINES - 7, 54 ,   "         #KWWWK#         ");
    mvwprintw(term, LINES - 6, 54 ,   "          #KWK#          ");
    mvwprintw(term, LINES - 5, 54 ,   "           #i#           ");
    
    SET_COLOR(COL_RED);
    mvwprintw(term,22+y_ofs,28+x_ofs,    "Precione qualquer tecla");
    SET_COLOR(COL_BKG);
    
    while (wgetch(term) == ERR);
    
    wclear(term);
    
    
}

// Returns true if terminal is 80x25
int right_size()
{
	getmaxyx(term,term_y,term_x);
    
	x_ofs = (term_x-80)/2;
	y_ofs = (term_y-25)/2;
    
	return ((term_x>=80)&&(term_y>=25));
}

int main()
{
    srand((int)time(NULL));
	init_screen();
    
	if (!right_size())
	{
		endwin();
		fprintf(stderr,"Vialacteum must be run in an 80x25 terminal!\n");
		return -1;
	}
    
	presentation();
    int option_menu = menu(term, x_ofs, y_ofs);
    
    if (option_menu == NOVO_JOGO)
        game(term, x_ofs, y_ofs);
    else if (option_menu == SAIR)
        quit_game(term);
        
	return 0;
}