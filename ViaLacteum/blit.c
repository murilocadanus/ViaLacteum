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
extern WINDOW *term; /* our terminal */

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


void blit_zombie(int x,int y)
{
/*
 Little Zombie:
 
 W_W
 "
 */
	if (is_y_range(y))
	{
		SET_COLOR(COL_BLUE);
		mvwprintw(term,y,x,"W W");
		SET_COLOR(COL_WHITE);
		mvwaddch(term,y,x+1,(chtype)'_');
	}
	if (is_y_range(y+1))
	{
		SET_COLOR(COL_RED);
		mvwprintw(term,y+1,x+1,"\"");
	}
	SET_COLOR(COL_BKG);
}

void clear_zombie(int x, int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y)) mvwprintw(term,y,x,"   ");
	if (is_y_range(y+1)) mvwprintw(term,y+1,x+1," ");
}

void blit_fire(int x,int y)
{
	if (is_y_range(y))
	{
		SET_COLOR(COL_RED);
		mvwaddch(term,y,x,(chtype)'!');
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

void blit_player(int x,int y)
{
/* This is the player's ship:
  /^\
 | _ |
< /_\ >
 ^^^^^
*/
    
	if (is_y_range(y))
	{
		SET_COLOR(COL_GRAY);
		mvwprintw(term,y,x+2,  "/^\\");
	}
	
	if (is_y_range(y+1))
	{
		SET_COLOR(COL_GRAY);
		mvwprintw(term,y+1,x+1,"| ");
		SET_COLOR(COL_DARKCYAN);
		wprintw(term,"_");
		SET_COLOR(COL_GRAY);
		wprintw(term," |");
	}
    
	if (is_y_range(y+2))
	{
		SET_COLOR(COL_GRAY);
		mvwprintw(term,y+2,x,"< ");
		SET_COLOR(COL_DARKCYAN);
		wprintw(term,"/_\\");
		SET_COLOR(COL_GRAY);
		wprintw(term," >");
	}
    
	if (is_y_range(y+3))
	{
		SET_COLOR(COL_YELLOW);
		mvwprintw(term,y+3,x+1,"^");
		SET_COLOR(COL_RED);
		wprintw(term,"^^^");
		SET_COLOR(COL_YELLOW);
		wprintw(term,"^");
	}
    
	SET_COLOR(COL_BKG);
}

void clear_player(int x,int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y)) mvwprintw(term,y,x+2,    "   ");
	if (is_y_range(y+1)) mvwprintw(term,y+1,x+1, "     ");
	if (is_y_range(y+2)) mvwprintw(term,y+2,x,  "       ");
	if (is_y_range(y+3)) mvwprintw(term,y+3,x+1, "     ");
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
