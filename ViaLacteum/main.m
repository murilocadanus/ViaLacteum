//
//  main.c
//  ViaLacteum
//
//  Created by Murilo Costa on 25/04/11.
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
#include "game.h"
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>


int x_ofs = 0;
int y_ofs = 0;
int term_x = 0;
int term_y = 0;

// The terminal
WINDOW *term; 
NSSound *music;

void init_screen()
{
	term = initscr(); /* Initialize terminal */
    
	start_color(); /* Initialize colors */
	init_pair(PC_WHITE,COLOR_WHITE,COLOR_BLACK);
	init_pair(PC_RED,COLOR_RED,COLOR_BLACK);
	init_pair(PC_GREEN,COLOR_GREEN,COLOR_BLACK);
	init_pair(PC_YELLOW,COLOR_YELLOW,COLOR_BLACK);
	init_pair(PC_BLUE,COLOR_BLUE,COLOR_BLACK);
	init_pair(PC_MAGENTA,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(PC_CYAN,COLOR_CYAN,COLOR_BLACK);
	SET_COLOR(COL_BKG);
    
	cbreak(); /* Disable line buffering and erase/kill characters */
	noecho(); /* Don't echo characters */
	nodelay(term,TRUE); /* Don't block while waiting for input */
    
	nonl(); /* Don't translate return into newline, only CR */
	intrflush(term,FALSE); /* Do not flush input at ^C */
	keypad(term,TRUE); /* Enable keypad */
    
	wrefresh(term);
}

void presentation()
{       
    blit_borders(COL_BLUE);
    int iteraction = 0;
    int animation = 20;
    
    while (wgetch(term) == ERR)
    {
        iteraction++;
        SET_COLOR(COL_GREEN);
        

        mvwprintw(term,7+y_ofs - animation,25+x_ofs, "                                                 ");
        mvwprintw(term,8+y_ofs - animation,25+x_ofs, "  _____       _                  _               ");
        mvwprintw(term,9+y_ofs - animation,25+x_ofs, " |_   _|     | |                | |              ");
        mvwprintw(term,10+y_ofs - animation,25+x_ofs,"   | |  _ __ | |_ _ __ _   _  __| | ___ _ __ ___ ");
        mvwprintw(term,11+y_ofs - animation,25+x_ofs,"   | | | '_ \\| __| '__| | | |/ _` |/ _ \\ '__/ __|");
        mvwprintw(term,12+y_ofs - animation,25+x_ofs,"  _| |_| | | | |_| |  | |_| | (_| |  __/ |  \\__ \\");
        mvwprintw(term,13+y_ofs - animation,25+x_ofs," |_____|_| |_|\\__|_|   \\__,_|\\__,_|\\___|_|  |___/");
        
        
        mvwprintw(term,15+y_ofs,27+x_ofs,  "");

        SET_COLOR(COL_WHITE);
        
        mvwprintw(term, LINES - 22 + animation, 1,  "         #iiiii# ");
        mvwprintw(term, LINES - 21 + animation, 1,  "       #iEKWWWKEi# ");
        mvwprintw(term, LINES - 20 + animation, 1,  "      iEKKKW#WKKKEi ");
        mvwprintw(term, LINES - 19 + animation, 1,  "     #EWWKKW#WKKWWE# ");
        mvwprintw(term, LINES - 18 + animation, 1,  "    #EWKEKWKKKWKEKWE# ");
        mvwprintw(term, LINES - 17 + animation, 1,  "    #EW EWKWWWKWE WE# ");
        mvwprintw(term, LINES - 16 + animation, 1,  "    #EK  EEKKKEE  KE# ");
        mvwprintw(term, LINES - 15 + animation, 1,  "    #EK   EEKEE   KE# ");
        mvwprintw(term, LINES - 14 + animation, 1,  "    #EK    WWW    KE# ");
        mvwprintw(term, LINES - 13 + animation, 1,  "     iK    EWE    Ki ");
        mvwprintw(term, LINES - 12 + animation, 1,  "     #EK   EWE   KE# ");
        mvwprintw(term, LINES - 11 + animation, 1,  "     #EWEE E#E EEWE# ");
        mvwprintw(term, LINES - 10 + animation, 1,  "      #KW#KKKKK#WK# ");
        mvwprintw(term, LINES - 9 + animation, 1,   "       iWWWKEKWWWi ");
        mvwprintw(term, LINES - 8 + animation, 1,   "        #KWKEKWK# ");
        mvwprintw(term, LINES - 7 + animation, 1,   "         #K---K# ");
        mvwprintw(term, LINES - 6 + animation, 1,   "          #KWK# ");
        mvwprintw(term, LINES - 5 + animation, 1,   "           #i# ");
        
        SET_COLOR(COL_RED);
        if (iteraction % 2)
            mvwprintw(term,22+y_ofs,28+x_ofs,    "          Press any key to start");
        else
            mvwprintw(term,22+y_ofs,28+x_ofs,    "                                ");
        SET_COLOR(COL_BKG);
    
        wmove(term,0,0);
		wrefresh(term);
        refresh();
        
        m_wait(GAME_DELAY + 400000);

        if (animation > 1)
            animation--;
    }
    
    wclear(term);
    
}

void show_credits()
{        
    blit_borders(COL_BLUE);
    int iteraction = 0;
    int animation = 20;
    
    while (wgetch(term) == ERR)
    {
        iteraction++;
        SET_COLOR(COL_GREEN);
        
        
        
        mvwprintw(term, LINES - 23 + animation, 18+x_ofs, "                                                  ");
        mvwprintw(term, LINES - 22 + animation, 18+x_ofs, "  _____       _                  _                ");
        mvwprintw(term, LINES - 21 + animation, 18+x_ofs, " |_   _|     | |                | |               ");
        mvwprintw(term, LINES - 20 + animation, 18+x_ofs, "   | |  _ __ | |_ _ __ _   _  __| | ___ _ __ ___  ");
        mvwprintw(term, LINES - 19 + animation, 18+x_ofs, "   | | | '_ \\| __| '__| | | |/ _` |/ _ \\ '__/ __| ");
        mvwprintw(term, LINES - 18 + animation, 18+x_ofs, "  _| |_| | | | |_| |  | |_| | (_| |  __/ |  \\__ \\ ");
        mvwprintw(term, LINES - 17 + animation, 18+x_ofs, " |_____|_| |_|\\__|_|   \\__,_|\\__,_|\\___|_|  |___/ ");
        
        mvwprintw(term, LINES - 16 + animation, 18+x_ofs,  "                                                     ");
        mvwprintw(term, LINES - 15 + animation, 18+x_ofs,  "                                                     ");
        mvwprintw(term, LINES - 14 + animation, 18+x_ofs,  "                                                     ");
        
        SET_COLOR(COL_WHITE);
        
        mvwprintw(term, LINES - 13 + animation, 28+x_ofs,  "       Developed by:     ");
        mvwprintw(term, LINES - 12 + animation, 28+x_ofs,  "                         ");        
        mvwprintw(term, LINES - 11 + animation, 28+x_ofs,  "       Marlus Costa      ");
        mvwprintw(term, LINES - 10 + animation, 28+x_ofs,  "            and          ");
        mvwprintw(term, LINES - 9 + animation, 28+x_ofs,   "       Murilo Costa      ");
        mvwprintw(term, LINES - 8 + animation, 28+x_ofs,   "                         ");        
        
        wmove(term,0,0);
		wrefresh(term);
        refresh();
        
        m_wait(GAME_DELAY + 400000);
        
        if (animation > 1)
            animation--;
    }
    
    wclear(term);
    
}

// Returns true if terminal is 80x25
int right_size()
{
	getmaxyx(term,term_y,term_x);
    
	x_ofs = (term_x-80)/2;
	y_ofs = (term_y-25)/2;
    
	return ((term_x>=80)&&(term_y>=25));
}

void load_menu()
{
    int option_menu = INICIO;
    while (true)
    {
        wclear(term);
        option_menu = menu(term, x_ofs, y_ofs);
        
        if (option_menu == NOVO_JOGO)
        {
            option_menu = game(term, x_ofs, y_ofs);
        }
        if (option_menu == SAIR)
        {
            quit_game(term);
            return;
        }
        if (option_menu == CREDITOS)
        {
            show_credits();
        }
    }
}

void load_main_music()
{
    music = [[NSSound alloc] initWithContentsOfFile:@"resources/Invasores.aif" byReference:YES];
    [music setLoops:YES];
    [music setVolume:0.5f];
    [music play];
}

void unload_main_music()
{
    [music stop];
}

int main()
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    unload_game_music();
    unload_game_over_music();
    load_main_music();
    
    srand((int)time(NULL));
	init_screen();
    
	if (!right_size())
	{
		endwin();
		fprintf(stderr,"Intruders runs in a terminal window with 80x25!\n");
		return -1;
	}
    
	presentation();
    load_menu();
    
    [pool drain];
	return 0;
}
