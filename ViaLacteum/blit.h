//
//  blit.h
//  ViaLacteum
//
//  Created by Murilo Costa on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _BLIT_H
#define _BLIT_H

void blit_explosion_1(int x, int y);
void clear_explosion_1(int x, int y);

void blit_explosion(int x, int y, int dim);
void clear_explosion(int x, int y, int dim);

void blit_the_grey(int x,int y);
void clear_the_grey(int x, int y);

void blit_fire(int,int);
void clear_fire(int,int);

void blit_player_right(int x,int y);
void clear_player_right(int x,int y);

void blit_player_left(int x,int y);
void clear_player_left(int x,int y);

void blit_score(int x, int y, int score);

void blit_borders(int);

#endif //_BLIT_H