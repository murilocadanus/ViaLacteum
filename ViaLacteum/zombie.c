//
//  zombie.c
//  ViaLacteum
//
//  Created by Murilo Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "zombie.h"
#include "blit.h"
#include "util.h"
#include "waves.h"

extern int x_ofs;
extern int y_ofs;
extern int score;
extern int game_ended;

const bitmask bitmask_zombie   = {0xE0,0x40,0x00,0x00,0x00};

zombie all_zombies[NUM_ZOMBIES];

/* Straight down, half speed if state is initialized at 0, top speed if -1 */
void move_zombie_straight(void *al_ptr)
{
	zombie *zom;
	zom = (zombie*)al_ptr;
    
	switch (zom->state)
	{
        case 0:
            zom->state=1;
            break;
        case 1:
            zom->y++;
            zom->state=0;
            break;
        case -1:
            zom->y++;
            break;
	}
	if ((zom->y)>23) zom->type=AT_NONE;
}

void init_zombies()
{
	int i;
	for (i=0;i<NUM_ZOMBIES;i++)
		all_zombies[i].type=AT_NONE;
}

/* Draws all aliens */
void blit_zombies()
{
	int i;
	for (i=0;i<NUM_ZOMBIES;i++)
	{
		if (all_zombies[i].type != AT_NONE)
		{
			all_zombies[i].blit(all_zombies[i].x+x_ofs,all_zombies[i].y+y_ofs);
		}
	}
}


// Delete all zombies
void delete_zombies()
{
	int i;
	for (i=0;i<NUM_ZOMBIES;i++)
	{
		if (all_zombies[i].type != AT_NONE)
		{
			all_zombies[i].clear(all_zombies[i].x+x_ofs,all_zombies[i].y+y_ofs);
		}
	}
}


/* Makes all aliens move */
void move_zombies()
{
	int i;
	if (!create_zombies())
	{
		game_ended = 1;
	}
	for (i=0;i<NUM_ZOMBIES;i++)
	{
		switch (all_zombies[i].type)
		{
            case AT_BIG:
            case AT_TINY:
            case AT_BALL:
            case AT_SLIME:
            case AT_LITTLE:
                all_zombies[i].move((void*)&all_zombies[i]);
                break;
            case AT_BIG_EXP:
                switch (all_zombies[i].state++)
			{
                case 0:
                    all_zombies[i].blit = blit_explosion_1;
                    all_zombies[i].clear = clear_explosion_1;
                    break;
                case 2:
                    all_zombies[i].blit = blit_explosion_1;
                    all_zombies[i].clear = clear_explosion_1;
                    break;
                case 4:
                    all_zombies[i].blit = blit_explosion_1;
                    all_zombies[i].clear = clear_explosion_1;
                    break;
                case 6:
                    all_zombies[i].blit = blit_explosion_1;
                    all_zombies[i].clear = clear_explosion_1;
                    break;
                case 8:
                    all_zombies[i].blit = blit_explosion_1;
                    all_zombies[i].clear = clear_explosion_1;
                    all_zombies[i].type = AT_LAST;
                    break;
			}
                break;
            case AT_LIT_EXP:
                switch (all_zombies[i].state++)
			{
                case 0:
                    all_zombies[i].blit = blit_explosion_1;
                    all_zombies[i].clear = clear_explosion_1;
                    break;
                case 2:
                    all_zombies[i].blit = blit_explosion_1;
                    all_zombies[i].clear = clear_explosion_1;
                    break;
                case 4:
                    all_zombies[i].blit = blit_explosion_1;
                    all_zombies[i].clear = clear_explosion_1;
                    break;
                case 6:
                    all_zombies[i].blit = blit_explosion_1;
                    all_zombies[i].clear = clear_explosion_1;
                    all_zombies[i].type = AT_LAST;
                    break;
			}
                break;
            case AT_LAST:
                all_zombies[i].type = AT_NONE;
                break;
		}
	}
}


// Blows zombie num and update score
void blow_zombie(int num)
{
	int i;
	for (i=0;i<MAX_HEIGHT;i++)
		all_zombies[num].collide[i]=0x00;
    
	switch (all_zombies[num].type)
	{
        case AT_BALL:
            score+=200;
            all_zombies[num].type  = AT_LIT_EXP;
            all_zombies[num].blit  = blit_explosion_1;
            all_zombies[num].clear = clear_explosion_1;
            all_zombies[num].state = 0;
            all_zombies[num].x++;
            all_zombies[num].y++;
            break;
	}
}

// Checks collision for all zombies
int collide_zombies(int x, int y)
{
	int i;
	for (i=0;i<NUM_ZOMBIES;i++)
	{
		if (all_zombies[i].type!=AT_NONE)
		{
			int mask_x, mask_y;
			mask_x = x-all_zombies[i].x;
			mask_y = y-all_zombies[i].y;
			if ((mask_y>=0) && (mask_y<MAX_HEIGHT) && (mask_x>=0) && (mask_x<8))
			{
				if ( (all_zombies[i].collide[mask_y] & (0x80 >> mask_x)) != 0 )
					return i;
			}
		}
	}
	return -1;
}