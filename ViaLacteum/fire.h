//
//  fire.h
//  ViaLacteum
//
//  Created by Murilo Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _FIRE_H
#define _FIRE_H

typedef struct
{
	int x;
	int y;
    int side;
	void (*blit)(int,int);
	void (*clear)(int,int);
} fire;

#define NUM_FIRES 25

void new_fire(int, int, int);
void init_fires();
void blit_fires();
void delete_fires();
void move_fires();

#endif //_FIRE_H
