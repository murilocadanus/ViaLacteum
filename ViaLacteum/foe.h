//
//  foe.h
//  ViaLacteum
//
//  Created by Murilo Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _FOE_H
#define _FOE_H

#define AT_NONE     -1
#define AT_LAST     -2
#define AT_XP        0
#define AT_GREY_FOE  1

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
void move_foe_straight_right(void *);

// Foe movement
void move_foe_straight_left(void *);


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
