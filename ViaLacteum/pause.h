//
//  pause.h
//  ViaLacteum
//
//  Created by Marlus Costa on 28/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <menu.h>

#define ESCAPE_KEY 27
#define ENTER_KEY 13

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

int pause_game(WINDOW *term, int x_ofs, int y_ofs);
void print_in_middle_pause(WINDOW *win, int starty, int startx, int width, char *string, chtype color);