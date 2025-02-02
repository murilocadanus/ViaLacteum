//
//  defs.h
//  ViaLacteum
//
//  Created by Murilo Costa on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _DEFS_H
#define _DEFS_H

#ifndef NULL
#define NULL 0
#endif

#define MAXSPEED 3   /* Max speed of the ship */
#define GAME_DELAY 40000  /* Affects game speed */

#define KEY_ESC 033  /* Escape code */
#define KEY_ENTER_ 015  /* Enter code */

/********** Colors ***********/

#define PC_WHITE 1
#define PC_RED 2
#define PC_GREEN 3
#define PC_YELLOW 4
#define PC_BLUE 5
#define PC_MAGENTA 6
#define PC_CYAN 7

#define SET_COLOR(x) wcolor_set(term,((x)>10)?((x)-10):(x),NULL); ((x)>10)?wattron(term,A_BOLD):wattroff(term,A_BOLD);

#define COL_BLACK         0
#define COL_GRAY          1
#define COL_DARKRED       2
#define COL_DARKGREEN     3
#define COL_DARKYELLOW    4
#define COL_DARKBLUE      5
#define COL_DARKMAGENTA   6
#define COL_DARKCYAN      7
#define COL_WHITE        11
#define COL_RED          12
#define COL_GREEN        13
#define COL_YELLOW       14
#define COL_BLUE         15
#define COL_MAGENTA      16
#define COL_CYAN         17

#define COL_BKG          COL_BLUE

// MENU
#define INICIO 0
#define NOVO_JOGO 1
#define OPCOES 2
#define CREDITOS 3
#define SAIR 4
#define CONTINUAR_JOGO 5
#define MENU_PRINCIPAL 6


#endif //_DEFS_H
