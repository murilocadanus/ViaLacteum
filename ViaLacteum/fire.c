//
//  fire.c
//  ViaLacteum
//
//  Created by Murilo Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "fire.h"
#include "blit.h"
#include "foe.h"

#include "defs.h"
#include <curses.h>
extern WINDOW *term;

extern int x_ofs;
extern int y_ofs;
extern foe all_foes[NUM_FOES];

fire all_fires[NUM_FIRES];

void new_fire(int x, int y, int side)
{
	int n=0;
	while ( (all_fires[n].y >= 0) && (++n<NUM_FIRES) ) ;
    
	if (n<=NUM_FIRES)
	{
		all_fires[n].x = x;
		all_fires[n].y = y;
        all_fires[n].side = side;
	}
}

void init_fires()
{
	int i;
	for (i=0;i<NUM_FIRES;i++)
	{
		all_fires[i].y = -1;
	}
}

void blit_fires()
{
	int i;
	for (i=0;i<NUM_FIRES;i++)
	{
		if (all_fires[i].y >= 0)
		{
			blit_fire(all_fires[i].x+x_ofs,all_fires[i].y+y_ofs);
		}
	}
}

void delete_fires()
{
	int i;
	for (i=0;i<NUM_FIRES;i++)
	{
		if (all_fires[i].y >= 0)
		{
			clear_fire(all_fires[i].x+x_ofs,all_fires[i].y+y_ofs);
		}
	}
}

void move_fires()
{
	int i;
	for (i=0;i<NUM_FIRES;i++)
	{
		if (all_fires[i].y >= 0)
		{
			int n;
                      
            if(all_fires[i].side)
                all_fires[i].x++;
            else
                all_fires[i].x--;
            
            SET_COLOR(COL_GRAY);
            mvwprintw(term, 24, 0, "%X fire", all_fires[i].x);
                        
			if (all_fires[i].x<0 || all_fires[i].x>80)
			{
				all_fires[i].y = -1;
			}
            else
			{
				while ((n = collide_foes(all_fires[i].x,all_fires[i].y))>=0)
				{
					blow_foe(n);
					all_fires[i].y = -1;
				}
			}
		}
	}
}

