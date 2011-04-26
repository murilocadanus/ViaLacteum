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

extern int x_ofs;
extern int y_ofs;
extern int term_x;
extern int term_y;
extern WINDOW *term; /* our terminal */

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
