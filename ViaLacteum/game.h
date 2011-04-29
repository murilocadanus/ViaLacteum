//
//  game.h
//  ViaLacteum
//
//  Created by Marlus Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "defs.h"
#include "foe.h"
#include "blit.h"
#include "waves.h"
#include "fire.h"
#include "menu.h"

int collide_player(int x);
int move_player(WINDOW *term, int x_ofs, int y_ofs);
void m_wait(long delay);
void end_game(WINDOW *term, int x_ofs, int y_ofs);
int game(WINDOW *term, int x_ofs, int y_ofs);
void final();
int quit_game();
void game_over(WINDOW *term, int x_ofs, int y_ofs);
int show_dialogs();
void load_game_music();
void unload_game_music();
void play_game_music();
void pause_game_music();