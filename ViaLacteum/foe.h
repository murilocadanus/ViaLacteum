//
//  foe.h
//  ViaLacteum
//
//  Created by Murilo Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _FOE_H
#define _FOE_H

#define AT_NONE    -1
#define AT_LAST    -2
#define AT_LITTLE   0
#define AT_BIG      1
#define AT_BALL     2
#define AT_SLIME    3
#define AT_TINY     4
#define AT_BIG_EXP  8
#define AT_LIT_EXP  7

#define MAX_HEIGHT 5

typedef char bitmask[MAX_HEIGHT];

typedef struct
{
	int x;
	int y;
	int type; // See #defines up there
	void (*blit)(int,int);
	void (*clear)(int,int);
	void (*move)(void *);
	short int state;
	bitmask collide;
} foe;

#define NUM_FOES 10

// Foe movement
void move_foe_straight(void *);

// Initialize foes
void init_foes();

// Draws all foes
void blit_foes();

// Deletes all foes
void delete_foes();

// Makes all foes move
void move_foes();

// Blows foe num and update score
void blow_foe(int);

// Check collisions for foes
int collide_foes(int, int);

#endif //_FOE_H
