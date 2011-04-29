//
//  zombie.c
//  ViaLacteum
//
//  Created by Murilo Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "foe.h"
#include "blit.h"
#include "util.h"
#include "waves.h"

extern int x_ofs;
extern int y_ofs;
extern int score;
extern int game_ended;

const bitmask bitmask_foe   = {0xE0,0x40,0x00,0x00,0x00};

foe all_foes[NUM_FOES];

// Straight right
void move_foe_straight_right(void *al_ptr)
{
	foe *fo;
	fo = (foe*)al_ptr;
    
	switch (fo->state)
	{
        case 0:
            fo->state=1;
            break;
        case 1:
            fo->x++;
            fo->state=0;
            break;
        case -1:
            fo->x++;
            break;
	}
	if ((fo->x)>80) fo->type=AT_NONE;
}

// Straight left
void move_foe_straight_left(void *al_ptr)
{
	foe *fo;
	fo = (foe*)al_ptr;
    
	switch (fo->state)
	{
        case 0:
            fo->state=1;
            break;
        case 1:
            fo->x--;
            fo->state=0;
            break;
        case -1:
            fo->x--;
            break;
	}
	if ((fo->x)<0) fo->type=AT_NONE;
}


void init_foes()
{
	int i;
	for (i=0;i<NUM_FOES;i++)
		all_foes[i].type=AT_NONE;
}

// Draws all foes
void blit_foes()
{
	int i;
	for (i=0;i<NUM_FOES;i++)
	{
		if (all_foes[i].type != AT_NONE)
		{
			all_foes[i].blit(all_foes[i].x+x_ofs,all_foes[i].y+y_ofs);
		}
	}
}

// Delete all foes
void delete_foes()
{
	int i;
	for (i=0;i<NUM_FOES;i++)
	{
		if (all_foes[i].type != AT_NONE)
		{
			all_foes[i].clear(all_foes[i].x+x_ofs,all_foes[i].y+y_ofs);
		}
	}
}

// Makes all foes move
void move_foes()
{
	int i;
	if (!create_foes())
	{
		game_ended = 1;
	}
	for (i=0;i<NUM_FOES;i++)
	{
		switch (all_foes[i].type)
		{
            case AT_GREY_FOE:
                all_foes[i].move((void*)&all_foes[i]);
                break;
            case AT_XP:
                switch (all_foes[i].state++)
			{
                case 0:
                    all_foes[i].blit = blit_explosion_1;
                    all_foes[i].clear = clear_explosion_1;
                    break;
                case 2:
                    all_foes[i].blit = blit_explosion_1;
                    all_foes[i].clear = clear_explosion_1;
                    break;
                case 4:
                    all_foes[i].blit = blit_explosion_1;
                    all_foes[i].clear = clear_explosion_1;
                    break;
                case 6:
                    all_foes[i].blit = blit_explosion_1;
                    all_foes[i].clear = clear_explosion_1;
                    all_foes[i].type = AT_LAST;
                    break;
			}
                break;
            case AT_LAST:
                all_foes[i].type = AT_NONE;
                break;
		}
	}
}


// Blows foe num and update score
void blow_foe(int num)
{
	int i;
	for (i=0;i<MAX_HEIGHT;i++)
		all_foes[num].collide[i]=0x00;
    
	switch (all_foes[num].type)
	{
        case AT_GREY_FOE:
            score+=200;
            all_foes[num].type  = AT_XP;
            all_foes[num].blit  = blit_explosion_1;
            all_foes[num].clear = clear_explosion_1;
            all_foes[num].state = 0;
            all_foes[num].x++;
            all_foes[num].y++;
            break;
	}
}

// Checks collision for all foes
int collide_foes(int x, int y)
{
	int i;
	for (i=0;i<NUM_FOES;i++)
	{
		if (all_foes[i].type!=AT_NONE)
		{
			int mask_x, mask_y;
			mask_x = x-all_foes[i].x;
			mask_y = y-all_foes[i].y;
                                   
			if ((mask_y>=0) && (mask_y<MAX_HEIGHT) && (mask_x>=0) && (mask_x<8))
			{
				if ( (all_foes[i].collide[mask_y] & (0x80 >> mask_x)) == 0 )
					return i;
			}
		}
	}
	return -1;
}