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

int score = 0;
int game_ended = 0;
int x_ofs = 0;
int y_ofs = 0;
int term_x = 0;
int term_y = 0;


WINDOW *term; /* our terminal */

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
	int x,y;
    
	blit_borders(COL_BLUE);
    
	SET_COLOR(COL_GREEN);
	mvwprintw(term,8+y_ofs,25+x_ofs,"-- -= V-I-A-L-A-C-T-E-U-M =- --");
	mvwprintw(term,11+y_ofs,27+x_ofs,  "");
	SET_COLOR(COL_WHITE);
	mvwprintw(term,22+y_ofs,29+x_ofs,    "Press any key to start");
	SET_COLOR(COL_BKG);
    
	while (wgetch(term) == ERR);
    
	wclear(term);
}

void final()
{
	printf("\n    Congratulations!\n");
	printf("    You have defeated Xzarna, the Queen of the Zorxians!\n\n");
    
	printf("    With their queen gone all the zorxian space ships fled, desperately\n");
	printf("    seeking to save themselves, and the earth attack failed.\n");
	printf("    2 years later the zorxian race was completely defeated, and the\n");
	printf("    human race completed its expansion in all the solar system.\n");
	printf("    The starpilot who killed Xzarna was decorated, and his bravery is\n");
	printf("    recorded in every history book.\n");
	printf("\n                               *** THE END ***\n");
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
    
	/* Flush input */
	while (wgetch(term) != ERR)
		;
    
	endwin();
    
	if (game_ended) final();
    
	printf("\nYou have made %d points!\n", score);
	printf("-= V-I-A-L-A-C-T-E-U-M =-\n");
    
	return 0;}

// Returns true if terminal is 80x25
int right_size()
{
	getmaxyx(term,term_y,term_x);
    
	x_ofs = (term_x-80)/2;
	y_ofs = (term_y-25)/2;
    
	return ((term_x>=80)&&(term_y>=25));
}
