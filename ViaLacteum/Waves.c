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
#include <stdio.h>

extern int score;

extern foe all_foes[NUM_FOES];

extern const bitmask bitmask_foe;

/* Bytes (actual):
 1,2 - Moment of appearence
 3 - array number
 4 - type of alien
 5 - x
 6 - y
 7 - state
 8 - movement function
 9 - alien necessary to appear (-1=none)
 */

#define FRAME_SIZE     9

#define MOVE_STRAIGHT_RIGHT 1
#define MOVE_STRAIGHT_LEFT  2

char wave_1[] = {    
    0x00,0x00, 0, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x00,0x04, 1, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x00,0x08, 2, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x00,0x0C, 3, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x00,0x10, 4, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    
    0x00,0xB0, 5, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x00,0xB2, 6, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x00,0xB4, 7, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x00,0xB6, 8, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x00,0xB8, 9, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    
    0x01,0x60, 0, AT_NONE, 0, 0, 0, MOVE_STRAIGHT_LEFT,  -1    
};

char wave_2[] = {    
    0x00,0x00, 0, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x00,0x04, 1, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x00,0x08, 2, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x00,0x0C, 3, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x00,0x10, 4, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
        
    0x01,0x10, 5, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x01,0x14, 6, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x01,0x18, 7, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x01,0x1C, 8, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x01,0x20, 9, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    
    0x01,0x60, 0, AT_NONE, 0, 0, 0, MOVE_STRAIGHT_LEFT,  -1    
};

char wave_3[] = {    
    0x00,0x00, 0, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x00,0x04, 1, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x00,0x08, 2, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x00,0x0C, 3, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x00,0x10, 4, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
        
    0x01,0x10, 5, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x01,0x14, 6, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x01,0x18, 7, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x01,0x1C, 8, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x01,0x20, 9, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    
    0x01,0x60, 0, AT_NONE, 0, 0, 0, MOVE_STRAIGHT_LEFT,  -1    
};

char wave_4[] = {    
    0x00,0x00, 0, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x00,0x04, 1, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x00,0x08, 2, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x00,0x0C, 3, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x00,0x10, 4, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
        
    0x01,0x10, 5, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x01,0x14, 6, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x01,0x18, 7, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    0x01,0x1C, 8, AT_GREY_FOE, 80, 19, 0, MOVE_STRAIGHT_LEFT, -1,
    0x01,0x20, 9, AT_GREY_FOE, 0, 19, 0, MOVE_STRAIGHT_RIGHT, -1,
    
    0x01,0x60, 0, AT_NONE, 0, 0, 0, MOVE_STRAIGHT_LEFT,  -1    
};
char *wave;
int wave_num;

void init_waves()
{
	wave = wave_1;
    wave_num = 1;
}

char *next_wave(const char *actual)
{
	char *next = wave_1;

    // Sequential algorithm
	if (actual == wave_1)
    {
        printf("Wave: 2 - Sala de estar");
        next = wave_2;
        wave_num = 2;
    }
	else if (actual == wave_2)
    {
        printf("Wave: 3 - Garagem");
        next = wave_3;
        wave_num = 3;
    }
	else if (actual == wave_3)
    {
        printf("Wave: 4 - Cozinha");
        next = wave_4;
        wave_num = 4;
    }
	else if (actual == wave_4) next = NULL;
	else next = wave_1;   
    
	return next;
}

int create_foes()
{
	static unsigned short int moment=0;
	static int lev_count=0;
	static int ended=0;
    
	if (ended)
	{
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

	}
    
    if(wave != NULL)
    {
        while( moment == ( ((unsigned char)wave[lev_count]<<8) | (unsigned char)wave[lev_count+1] ) )
        {
            if ( (wave[lev_count+8] < 0) ||
                ((all_foes[(int)wave[lev_count+8]].type != AT_NONE) &&
                 (all_foes[(int)wave[lev_count+8]].type != AT_LAST)) )
            {
                int ar_num;
                int n;
                
                ar_num = wave[lev_count+2];
                
                all_foes[ar_num].type = wave[lev_count+3];
                                
                switch (all_foes[ar_num].type)
                {
                    case AT_GREY_FOE:
                        all_foes[ar_num].blit = blit_the_grey;
                        all_foes[ar_num].clear = clear_the_grey;

                        for (n=0;n<MAX_HEIGHT;n++)
                            all_foes[ar_num].collide[n] = bitmask_foe[n];
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
                    case MOVE_STRAIGHT_RIGHT:
                        all_foes[ar_num].move = move_foe_straight_right;
                    break;
                    case MOVE_STRAIGHT_LEFT:
                        all_foes[ar_num].move = move_foe_straight_left;
                    break;
                }
                all_foes[ar_num].type = wave[lev_count+3];
            }
            
            lev_count += FRAME_SIZE;
        }
    }
	moment++;
    
	return 1;
}

int get_wave_num()
{
    return wave_num;
}