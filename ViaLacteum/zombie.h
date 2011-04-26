//
//  zombie.h
//  ViaLacteum
//
//  Created by Murilo Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _ZOMBIE_H
#define _ZOMBIE_H

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
} zombie;

#define NUM_ZOMBIES 10

// Zombie movement
void move_zombie_straight(void *);

// Initialize zombies
void init_zombies();

// Draws all zombies
void blit_zombies();

// Deletes all zombies
void delete_zombies();

// Makes all zombies move
void move_zombies();

// Blows zombie num and update score
void blow_zombie(int);

// Check collisions for zombies
int collide_zombies(int, int);

#endif //_ZOMBIE_H
