//
//  blit.c
//  ViaLacteum
//
//  Created by Murilo Costa on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "blit.h"
#include <curses.h>
#include "defs.h"
#include "util.h"

extern int x_ofs;
extern int y_ofs;
extern int term_x;
extern int term_y;

extern WINDOW *term;

#define SET_COLOR_DRAW(fore, bg)                wattrset(stdscr, COLOR_PAIR(COLOR_##fore * COLORS + COLOR_##bg))

void blit_explosion_1(int x, int y)
{
/*
 .
#@#
 "
*/
	SET_COLOR(COL_DARKYELLOW);
	if (is_y_range(y-1))
	{
		mvwaddch(term,y-1,x,(chtype)'.');
	}
	if (is_y_range(y))
	{
		if (is_x_range(x-1)) mvwaddch(term,y,x-1,(chtype)'#');
		SET_COLOR(COL_DARKRED);
		mvwaddch(term,y,x,(chtype)'@');
		SET_COLOR(COL_DARKYELLOW);
		if (is_x_range(x+1)) mvwaddch(term,y,x+1,(chtype)'#');
	}
	if (is_y_range(y+1))
	{
		mvwaddch(term,y+1,x,(chtype)'"');
	}
	SET_COLOR(COL_BKG);
}

void clear_explosion_1(int x, int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y-1))
	{
		mvwaddch(term,y-1,x,(chtype)' ');
	}
	if (is_y_range(y))
	{
		if (is_x_range(x-1)) mvwaddch(term,y,x-1,(chtype)' ');
		mvwaddch(term,y,x,(chtype)' ');
		if (is_x_range(x+1)) mvwaddch(term,y,x+1,(chtype)' ');
	}
	if (is_y_range(y+1))
	{
		mvwaddch(term,y+1,x,(chtype)' ');
	}
}


void blit_explosion(int x, int y, int dim)
{
	switch (dim)
	{
        case 1:
            blit_explosion_1(x,y);
            break;
	}
}

void clear_explosion(int x, int y, int dim)
{
	switch (dim)
	{
        case 1:
            clear_explosion_1(x,y);
            break;
	}
}


void blit_the_grey(int x,int y)
{
/*
 The greys:
-----  
\\ //  
  _   
/ | \  
 / \  
*/
	if (is_y_range(y))
	{
		SET_COLOR(COL_RED);
		mvwprintw(term,y,x,"-----");
	}
	if (is_y_range(y+1))
	{
		SET_COLOR(COL_GRAY);
		mvwprintw(term,y+1,x,"\\\\ //");
	}
	if (is_y_range(y+2))
	{
		SET_COLOR(COL_GRAY);
		mvwprintw(term,y+2,x+2,"-");
	}
	if (is_y_range(y+3))
	{
		SET_COLOR(COL_GRAY);
		mvwprintw(term,y+3,x,"/ | \\");
	}
	if (is_y_range(y+4))
	{
		SET_COLOR(COL_GRAY);
		mvwprintw(term,y+4,x+1,"/ \\");
	}
    
	SET_COLOR(COL_BKG);
}

void clear_the_grey(int x, int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y)) mvwprintw(term,y,x,       "     ");
	if (is_y_range(y+1)) mvwprintw(term,y+1,x,   "     ");
	if (is_y_range(y+2)) mvwprintw(term,y+2,x+1, " ");
	if (is_y_range(y+3)) mvwprintw(term,y+3,x+1, "     ");
	if (is_y_range(y+4)) mvwprintw(term,y+4,x+1, "    ");
}

void blit_fire(int x,int y)
{    
	if (is_y_range(y))
	{
		SET_COLOR(COL_RED);
		mvwaddch(term,y,x,(chtype)'-');
		SET_COLOR(COL_BKG);
	}
}

void clear_fire(int x, int y)
{
	if (is_y_range(y))
	{
		SET_COLOR(COL_BKG);
		mvwaddch(term,y,x,(chtype)' ');
	}
}

void blit_player_right(int x,int y)
{
/* This is the player in right position:
   __
   **
  -||-
 / || @-
  /  \
 /_   \_
*/
    
    if (is_y_range(y))
    {
        SET_COLOR(COL_DARKRED);
        mvwprintw(term,y,x+3,  "--");
    }
    
    if (is_y_range(y+1))
    {
        SET_COLOR(COL_DARKRED);
        mvwprintw(term,y+1,x+3,"**");
    }
    
    if (is_y_range(y+2))
    {
        SET_COLOR(COL_GRAY);
        mvwprintw(term,y+2,x+2,"-");
        SET_COLOR(COL_DARKCYAN);
        wprintw(term,"||");
        SET_COLOR(COL_GRAY);
        wprintw(term,"-");
    }
    
    if (is_y_range(y+3))
    {
        SET_COLOR(COL_DARKCYAN);
        mvwprintw(term,y+3,x+1,"/ ||");
        SET_COLOR(COL_RED);
        wprintw(term," @-");
    }
    
    if (is_y_range(y+4))
    {
        SET_COLOR(COL_DARKCYAN);
        mvwprintw(term,y+4,x+2,"/  \\");
    }
    
    if (is_y_range(y+5))
    {
        SET_COLOR(COL_RED);
        mvwprintw(term,y+5,x+1,"/_ ");
        SET_COLOR(COL_RED);
        wprintw(term,"  \\_");
    }
    SET_COLOR(COL_BKG);
}

void clear_player_right(int x,int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y))    mvwprintw(term,y,x+3,   "  ");
	if (is_y_range(y+1))  mvwprintw(term,y+1,x+3, "  ");
	if (is_y_range(y+2))  mvwprintw(term,y+2,x+2, "      ");
	if (is_y_range(y+3))  mvwprintw(term,y+3,x+1, "       ");
	if (is_y_range(y+4))  mvwprintw(term,y+4,x+2, "    ");
	if (is_y_range(y+5))  mvwprintw(term,y+5,x+1, "       ");
}

void blit_player_left(int x,int y)
{
/* This is the player in right position:
   __
   **
  -||-
-@ || \
  /  \
_/   _\
*/
    
    if (is_y_range(y))
    {
        SET_COLOR(COL_DARKRED);
        mvwprintw(term,y,x+3,  "--");
    }
    
    if (is_y_range(y+1))
    {
        SET_COLOR(COL_DARKRED);
        mvwprintw(term,y+1,x+3,"**");
    }
    
    if (is_y_range(y+2))
    {

        SET_COLOR(COL_RED);
        mvwprintw(term,y+2,x+2,"-");
        SET_COLOR(COL_DARKCYAN);
        wprintw(term,"||");
        SET_COLOR(COL_GRAY);
        wprintw(term,"-");
    }
    
    if (is_y_range(y+3))
    {
        SET_COLOR(COL_RED);
        mvwprintw(term,y+3,x,"-@");
        SET_COLOR(COL_DARKCYAN);
        wprintw(term," || \\");
    }
    
    if (is_y_range(y+4))
    {
        SET_COLOR(COL_DARKCYAN);
        mvwprintw(term,y+4,x+2,"/  \\");
    }
    
    if (is_y_range(y+5))
    {
        SET_COLOR(COL_GRAY);
        mvwprintw(term,y+5,x,"_/ ");
        SET_COLOR(COL_RED);
        wprintw(term,"  _\\");
    }
    SET_COLOR(COL_BKG);
}

void clear_player_left(int x,int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y))    mvwprintw(term,y,x+3,   "  ");
	if (is_y_range(y+1))  mvwprintw(term,y+1,x+3, "  ");
	if (is_y_range(y+2))  mvwprintw(term,y+2,x+2, "    ");
	if (is_y_range(y+3))  mvwprintw(term,y+3,x,   "       ");
	if (is_y_range(y+4))  mvwprintw(term,y+4,x+2, "    ");
	if (is_y_range(y+5))  mvwprintw(term,y+5,x,   "       ");
}


void blit_score(int x, int y, int score)
{
	SET_COLOR(COL_WHITE);
	mvwprintw(term,y,x,"%d",score);
	SET_COLOR(COL_BKG);
}

void blit_borders(int color)
{
	int i;
	SET_COLOR(color);
	if (y_ofs-1 >= 0)
	{
		for (i=x_ofs;i<80+x_ofs;i++)
			mvwaddch(term,y_ofs-1,i,(chtype)'-');
	}
	if (y_ofs+25 < term_y)
	{
		for (i=x_ofs;i<80+x_ofs;i++)
			mvwaddch(term,y_ofs+25,i,(chtype)'-');
	}
    
	if (x_ofs-1 >= 0)
	{
		for (i=y_ofs;i<25+y_ofs;i++)
			mvwaddch(term,i,x_ofs-1,(chtype)'|');
	}
	if (x_ofs+80 < term_x)
	{
		for (i=y_ofs;i<25+y_ofs;i++)
			mvwaddch(term,i,x_ofs+80,(chtype)'|');
	}
    
	if ((x_ofs-1 >= 0) && (y_ofs-1 >= 0))
		mvwaddch(term,y_ofs-1,x_ofs-1,(chtype)'+');
	if ((x_ofs-1 >= 0) && (y_ofs+25 < term_y))
		mvwaddch(term,y_ofs+25,x_ofs-1,(chtype)'+');
	if ((x_ofs+80 < term_x) && (y_ofs-1 >= 0))
		mvwaddch(term,y_ofs-1,x_ofs+80,(chtype)'+');
	if ((x_ofs+80 < term_x) && (y_ofs+25 < term_y))
		mvwaddch(term,y_ofs+25,x_ofs+80,(chtype)'+');
    
	SET_COLOR(COL_BKG);
}

void blit_scene()
{
    //init_color_pairs();
    
    SET_COLOR(COL_GREEN);
    mvwprintw(term,1,0,   "_______________________________________________________________________________");
    mvwprintw(term,2,0,   "...............................................................................");
    mvwprintw(term,3,0,   "                                                                               ");
    mvwprintw(term,4,0,   "                                                                               ");
    mvwprintw(term,5,0,   "                                                                               ");
    mvwprintw(term,6,0,   "                                             ----------------                  ");  
    mvwprintw(term,7,0,   "                                             |       |      |                  ");  
    mvwprintw(term,8,0,   "                                             |       |      |                  ");
    mvwprintw(term,9,0,   "                                             |       |      |                  ");
    mvwprintw(term,10,0,  "                                             |-------|------|                  ");
    mvwprintw(term,11,0,  "                                             |       |      |                  ");
    mvwprintw(term,12,0,  "                                             |       |      |                  ");
    mvwprintw(term,13,0,  "||                                           |       |      |                  ");
    mvwprintw(term,14,0,  "||                                           ----------------                  ");
    mvwprintw(term,15,0,  "||                                                                             ");
    mvwprintw(term,16,0,  "||               ||                                                            ");                    
    mvwprintw(term,17,0,  "||/----/         ||                                                            ");                    
    mvwprintw(term,18,0,  "||---------------||                                                            ");                    
    mvwprintw(term,19,0,  "||...............||                                                            ");                    
    mvwprintw(term,20,0,  "||...............||                                                            ");                    
    mvwprintw(term,21,0,  "||---------------||                                                            ");                   
    mvwprintw(term,22,0,  "...............................................................................");
    mvwprintw(term,23,0,  "_______________________________________________________________________________");    
       
}

void blit_scene2()
{
    //init_color_pairs();
    
    SET_COLOR(COL_GREEN);
    mvwprintw(term,1,0,   "_______________________________________________________________________________");
    mvwprintw(term,2,0,   "...............................................................................");
    mvwprintw(term,3,0,   "                                                                               ");
    mvwprintw(term,4,0,   "                                                                               ");
    mvwprintw(term,5,0,   "                                 __________________                            ");
    mvwprintw(term,6,0,   "                                |                  |                           ");  
    mvwprintw(term,7,0,   "                                |     __    _      |                           ");  
    mvwprintw(term,8,0,   "                                |    |__|  / \\     |                          ");
    mvwprintw(term,9,0,   "                                |    _    /   \\    |                          ");
    mvwprintw(term,10,0,  "                                |   / \\  /     \\   |                         ");
    mvwprintw(term,11,0,  "                                |  /   \\/       \\  |                         ");
    mvwprintw(term,12,0,  "                /--\\            | /     \\        \\ |                        ");
    mvwprintw(term,13,0,  "               /    \\           |/_______\\________\\|                        ");
    mvwprintw(term,14,0,  "              |______|                                                         ");
    mvwprintw(term,15,0,  "                 ||                                                            ");
    mvwprintw(term,16,0,  "                 ||             ______________________                         ");                    
    mvwprintw(term,17,0,  "                 ||          _ /                      \\ _                     ");                    
    mvwprintw(term,18,0,  "                 ||         | |   o       o        o   | |                     ");                    
    mvwprintw(term,19,0,  "                 ||         \\ \\________________________/ /                   ");                    
    mvwprintw(term,20,0,  "                 ||          | |______|_______|_______| |                      ");                    
    mvwprintw(term,21,0,  "                 ||          |                          |                      ");                   
    mvwprintw(term,22,0,  ".............................|..........................|......................");
    mvwprintw(term,23,0,  "_______________________________________________________________________________");    
    
}

void blit_scene3()
{
    //init_color_pairs();
    
    SET_COLOR(COL_GREEN);
    mvwprintw(term,1,0,   "_______________________________________________________________________________");
    mvwprintw(term,2,0,   "...............................................................................");
    mvwprintw(term,3,0,   "                                                                               ");
    mvwprintw(term,4,0,   "                                                                               ");
    mvwprintw(term,5,0,   "                                                                               ");
    mvwprintw(term,6,0,   "                                                                               ");  
    mvwprintw(term,7,0,   "                  ___________________________________________                  ");  
    mvwprintw(term,8,0,   "                 |___________________________________________|                 ");
    mvwprintw(term,9,0,   "                 ||                                         ||                 ");
    mvwprintw(term,10,0,  "                 ||                                         ||                 ");
    mvwprintw(term,11,0,  "                 ||                                         ||                 ");
    mvwprintw(term,12,0,  "                 ||                                         ||                 ");
    mvwprintw(term,13,0,  "                 ||           ___________________           ||                 ");
    mvwprintw(term,14,0,  "                 ||         //                   \\         ||                 ");
    mvwprintw(term,15,0,  "                 ||       / /                     \ \       ||                 ");
    mvwprintw(term,16,0,  "                 ||      /_/_______________________\_\      ||                 ");                    
    mvwprintw(term,17,0,  "                 ||    / |___||  ||||| W |||||  |___| \    ||                 ");                    
    mvwprintw(term,18,0,  "                 ||   /---------------------------------\   ||                 ");                    
    mvwprintw(term,19,0,  "                 ||   '---------------------------------'   ||                 ");                    
    mvwprintw(term,20,0,  "                 ||    |\_____________________________/|    ||                 ");                    
    mvwprintw(term,21,0,  "                 ||    |  |                         |  |    ||                 ");                   
    mvwprintw(term,22,0,  ".......................|__|.........................|__|........................");
    mvwprintw(term,23,0,  "_______________________________________________________________________________");    
    
}


void init_color_pairs() {
    short f, b;
    for( f = 0; f < COLORS; ++f )
        for( b = 0; b < COLORS; ++b )
            init_pair( f * COLORS + b, f, b );
}
