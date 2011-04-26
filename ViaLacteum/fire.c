//
//  fire.c
//  ViaLacteum
//
//  Created by Murilo Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "fire.h"
#include "blit.h"
#include "zombie.h"


extern int x_ofs;
extern int y_ofs;
extern zombie all_zombies[NUM_ZOMBIES];

fire all_fires[NUM_FIRES];

void new_fire(int x, int y)
{
	int n=0;
	while ( (all_fires[n].x >= 0) && (++n<NUM_FIRES) ) ;
    
	if (n<=NUM_FIRES)
	{
		all_fires[n].x = x;
		all_fires[n].y = y;
	}
}

void init_fires()
{
	int i;
	for (i=0;i<NUM_FIRES;i++)
	{
		all_fires[i].x = -1;
	}
}

void blit_fires()
{
	int i;
	for (i=0;i<NUM_FIRES;i++)
	{
		if (all_fires[i].x >= 0)
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
		if (all_fires[i].x >= 0)
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
		if (all_fires[i].x >= 0)
		{
			int n;
			all_fires[i].y--;
			if (all_fires[i].y<0)
			{
				all_fires[i].x = -1;
			}
			else
			{
				while ((n = collide_zombies(all_fires[i].x,all_fires[i].y))>=0)
				{
					blow_zombie(n);
					all_fires[i].x = -1;
				}
			}
		}
	}
}

