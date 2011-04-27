//
//  Waves.c
//  ViaLacteum
//
//  Created by Murilo Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "waves.h"
#include "foe.h"
#include "blit.h"
#include "util.h"
#include "defs.h"

#ifdef DEBUG_LEV
#include <curses.h>
extern WINDOW *term;
#endif

extern int score;

extern foe all_foes[NUM_FOES];

extern const bitmask bitmask_zombie;

/* Bytes (actual):
 1,2 - Moment of appearence
 3 - array number
 4 - type of alien
 5 - x
 6 - y
 7 - state
 8 - movement function
 9 - alien necessary to appear (-1=none)
 
 Next version could be:
 1,2 - Moment of appearence
 3   - array number
 4   - type of alien
 5   - min x
 6   - max x
 7   - min y
 8   - max y
 9   - possible state 1
 10  - possible state 2
 11  - movement function
 12  - alien necessary to appear (-1=none)
 */

#define FRAME_SIZE     9

#define MOVE_STRAIGHT  1
#define MOVE_OSCILLATE 2
#define MOVE_DIAGONAL  3
#define MOVE_SERPENT   4

char wave_1[] = {
    0x00,0x00, 0, AT_LITTLE, 39,-5, 0, MOVE_STRAIGHT, -1
};

char wave_2[] = {
    0x00,0x00, 0, AT_LITTLE, 39,-5, 0, MOVE_STRAIGHT, -1
};

char wave_3[] = {
    0x00,0x00, 0, AT_LITTLE, 39,-5, 0, MOVE_STRAIGHT, -1
};

char wave_4[] = {
    0x00,0x00, 0, AT_LITTLE, 39,-5, 0, MOVE_STRAIGHT, -1
};


char *wave;

void init_waves()
{
#ifndef RANDOM_WAVES
    // Sequential algorithm
	wave=wave_1;
#else
    // Random algorithm
	switch (rrand(1,4))
	{
        case 1:
            wave = wave_1;
            break;
        case 2:
            wave = wave_2;
            break;
        case 3:
            wave = wave_3;
            break;
        case 4:
            wave = wave_4;
            break;
	}
#endif
}

char *next_wave(const char *actual)
{
	char *next=wave_1;

    // Sequential algorithm
	if (actual == wave_1) next = wave_2;
	else if (actual == wave_2) next = wave_3;
	else if (actual == wave_3) next = wave_4;
	else if (actual == wave_4) next = NULL;
	else next = wave_1;
    
	return next;
}

int create_zombies()
{
	static unsigned short int moment=0;
	static int lev_count=0;
	static int ended=0;
    
	if (ended)
	{
#ifdef DEBUG_LEV
		mvwprintw(term,24,0,"%X over   ",moment++);
		return 1;
#else
        /*** Loop ***/
		ended = 0;
		lev_count = 0;
		moment = 0;
		if (wave == NULL)
		{
			return 0;
		}
		else
		{
			wave = next_wave(wave);
		}
#endif
	}
    
    while( moment == ( ((unsigned char)wave[lev_count]<<8) | (unsigned char)wave[lev_count+1] ) )
    {
        if ( (wave[lev_count+8] < 0) ||
            ((all_foes[(int)wave[lev_count+8]].type != AT_NONE) &&
             (all_foes[(int)wave[lev_count+8]].type != AT_BIG_EXP) &&
             (all_foes[(int)wave[lev_count+8]].type != AT_LIT_EXP) &&
             (all_foes[(int)wave[lev_count+8]].type != AT_LAST)) )
        {
            int ar_num;
            int n;
            
            ar_num = wave[lev_count+2];
            
            all_foes[ar_num].type = wave[lev_count+3];
            
            switch (all_foes[ar_num].type)
            {
                case AT_LITTLE:
                    all_foes[ar_num].blit = blit_zombie;
                    all_foes[ar_num].clear = clear_zombie;
                    for (n=0;n<MAX_HEIGHT;n++)
                        all_foes[ar_num].collide[n] = bitmask_zombie[n];
                break;
                case AT_NONE:
                    ended = 1;
                break;
            }
            
            all_foes[ar_num].x = wave[lev_count+4];
            all_foes[ar_num].y = wave[lev_count+5];
            all_foes[ar_num].state = wave[lev_count+6];
            switch (wave[lev_count+7])
            {
                case MOVE_STRAIGHT:
                    all_foes[ar_num].move = move_foe_straight;
                    break;
            }
            all_foes[ar_num].type = wave[lev_count+3];
        }
        
        lev_count += FRAME_SIZE;
    }
	moment++;
    
#ifdef DEBUG_LEV
	mvwprintw(term,24,0,"%X   ",moment);
#endif
    
	return 1;
}