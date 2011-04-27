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

void blit_zombie(int x,int y);
void clear_zombie(int x, int y);

void blit_fire(int,int);
void clear_fire(int,int);

void blit_player(int x,int y);
void clear_player(int x,int y);

void blit_score(int x, int y, int score);

void blit_borders(int);

void blit_scene();

void init_color_pairs();

#endif //_BLIT_H