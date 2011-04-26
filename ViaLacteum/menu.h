//
//  menu.h
//  ViaLacteum
//
//  Created by Marlus Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include <curses.h>
#include <menu.h>

//#define ESCAPE_KEY 27
//#define ENTER_KEY 13

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

void print_in_middle_menu_win_example(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
int menu(WINDOW *term);