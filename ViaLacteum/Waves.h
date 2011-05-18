//
//  waves.h
//  ViaLacteum
//
//  Created by Murilo Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef _WAVES_H
#define _WAVES_H

#define MAX_LEVEL_SIZE 100

void init_waves();

// Returns 0 if the game is over
int create_foes();

// Returns current wave number
int get_wave_num();

#endif //_WAVES_H