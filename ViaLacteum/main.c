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
#include "zombie.h"
#include "blit.h"
#include "waves.h"
#include "fire.h"

int score = 0;
int end_x;
int game_ended = 0;
int x_ofs = 0;
int y_ofs = 0;
int term_x = 0;
int term_y = 0;

const bitmask bitmask_player={0x38,0x7C,0xFE,0x7C,0x00};

// The terminal
WINDOW *term; 

// Player dying
// This will be >0 if the player is dying */
int exploding = 0; 

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
    
    SET_COLOR(COL_GREEN);
    mvwprintw(term,8+y_ofs,25+x_ofs,"-- -= I-N-V-A-S-O-R-E-S =- --");
    mvwprintw(term,11+y_ofs,27+x_ofs,  "");
    
    //init_color_pairs();
    SET_COLOR(COL_WHITE);
    mvwprintw(term, LINES - 22, 1 ,  "         #iiiii#     ");
    mvwprintw(term, LINES - 21, 1 ,  "       #iEKWWWKEi#       ");
    mvwprintw(term, LINES - 20, 1 ,  "      iEKKKW#WKKKEi      ");
    mvwprintw(term, LINES - 19, 1 ,  "     #EWWKKW#WKKWWE#     ");
    mvwprintw(term, LINES - 18, 1 ,  "    #EWKEKWKKKWKEKWE#    ");
    mvwprintw(term, LINES - 17, 1 ,  "    #EW EWKWWWKWE WE#    ");
    mvwprintw(term, LINES - 16, 1 ,  "    #EK  EEKKKEE  KE#    ");
    mvwprintw(term, LINES - 15, 1 ,  "    #EK   EEKEE   KE#    ");
    mvwprintw(term, LINES - 14, 1 ,  "    #EK    WWW    KE#    ");
    mvwprintw(term, LINES - 13, 1 ,  "     iK    EWE    Ki     ");
    mvwprintw(term, LINES - 12, 1 ,  "     #EK   EWE   KE#     ");
    mvwprintw(term, LINES - 11, 1 ,  "     #EWEE E#E EEWE#     ");
    mvwprintw(term, LINES - 10, 1 ,  "      #KW#KKKKK#WK#      ");
    mvwprintw(term, LINES - 9, 1 ,   "       iWWWKEKWWWi       ");
    mvwprintw(term, LINES - 8, 1 ,   "        #KWKEKWK#        ");
    mvwprintw(term, LINES - 7, 1 ,   "         #KWWWK#         ");
    mvwprintw(term, LINES - 6, 1 ,   "          #KWK#          ");
    mvwprintw(term, LINES - 5, 1 ,   "           #i#           ");
    
    SET_COLOR(COL_WHITE);
    mvwprintw(term, LINES - 22, 54 ,  "         #iiiii#     ");     
    mvwprintw(term, LINES - 21, 54 ,  "       #iEKWWWKEi#       ");
    mvwprintw(term, LINES - 20, 54 ,  "      iEKKKW#WKKKEi      ");
    mvwprintw(term, LINES - 19, 54 ,  "     #EWWKKW#WKKWWE#     ");
    mvwprintw(term, LINES - 18, 54 ,  "    #EWKEKWKKKWKEKWE#    ");
    mvwprintw(term, LINES - 17, 54 ,  "    #EW EWKWWWKWE WE#    ");
    mvwprintw(term, LINES - 16, 54 ,  "    #EK  EEKKKEE  KE#    ");
    mvwprintw(term, LINES - 15, 54 ,  "    #EK   EEKEE   KE#    ");
    mvwprintw(term, LINES - 14, 54 ,  "    #EK    WWW    KE#    ");
    mvwprintw(term, LINES - 13, 54 ,  "     iK    EWE    Ki     ");
    mvwprintw(term, LINES - 12, 54 ,  "     #EK   EWE   KE#     ");
    mvwprintw(term, LINES - 11, 54 ,  "     #EWEE E#E EEWE#     ");
    mvwprintw(term, LINES - 10, 54 ,  "      #KW#KKKKK#WK#      ");
    mvwprintw(term, LINES - 9, 54 ,   "       iWWWKEKWWWi       ");
    mvwprintw(term, LINES - 8, 54 ,   "        #KWKEKWK#        ");
    mvwprintw(term, LINES - 7, 54 ,   "         #KWWWK#         ");
    mvwprintw(term, LINES - 6, 54 ,   "          #KWK#          ");
    mvwprintw(term, LINES - 5, 54 ,   "           #i#           ");
    
    SET_COLOR(COL_RED);
    mvwprintw(term,22+y_ofs,28+x_ofs,    "Precione qualquer tecla");
    SET_COLOR(COL_BKG);
    
    while (wgetch(term) == ERR);
    
    wclear(term);
    
    
}

void final()
{
	printf("\n    Congratulations!\n");
	printf("    You have defeated Xzarna, the Queen of the Zorxians!\n\n");
    
	printf("    With their queen gone all the zorxian space ships fled, desperately\n");
	printf("    seeking to save themselves, and the earth attack failed.\n");
	printf("    2 years later the zorxian race was completely defeated, and the\n");
	printf("    human race completed its expansion in all the solar system.\n");
	printf("    The starpilot who killed Xzarna was decorated, and his bravery is\n");
	printf("    recorded in every history book.\n");
	printf("\n                               *** THE END ***\n");
}

// Returns true if terminal is 80x25
int right_size()
{
	getmaxyx(term,term_y,term_x);
    
	x_ofs = (term_x-80)/2;
	y_ofs = (term_y-25)/2;
    
	return ((term_x>=80)&&(term_y>=25));
}

int collide_player(int x)
{
	/* This collision algorithm is probably faster but must be completed */
    /*	int i;
     int rel_x,rel_y;
     for (i=0;i<NUMALIENS;i++)
     {
     if (all_aliens[i].type!=AT_NONE)
     {
     rel_x=x-all_aliens[i].x;
     rel_y=21-all_aliens[i].y;
     // ...... 
     }
     }
     return 0; */
    
	/* For now I will use this... it can be good anyway */
	int check_x,check_y;
	for (check_y=0; check_y<MAX_HEIGHT; check_y++)
	{
		for (check_x=0; check_x<8; check_x++)
		{
			if ( (bitmask_player[check_y] & (0x80 >> check_x)) != 0 )
			{
				if (collide_zombies(x+check_x,21+check_y)>=0)
					return 1;
			}
		}
	}
	return 0;
}

int move_player()
{
	int c = 0; /* character readen */
	static int last_c=-1;
	static int x = 37; /* ship position */
	static int xs = 0; /* ship speed */
    
	if (game_ended)
	{
		end_x = x; // Publish player x position
		return 0;
	}
    
	if (exploding == 0)
	{
		c = wgetch(term);
		if (c != last_c)
		{
			switch(c)
			{
                case ERR:
                    /* No key pressed */
                    break;
                case KEY_LEFT:
                    xs--;
                    break;
                case KEY_RIGHT:
                    xs++;
                    break;
                case KEY_DOWN:
                    xs=0;
                    break;
                case ' ':
                case KEY_ENTER_:
                    new_fire(x+3,21);
                    break;
                case 's':
                case KEY_BACKSPACE:
                case 'p':
                case 'P':
                    if (pause()<0)
                    {
                        c='Q';
                    }
                    break;
                case KEY_ESC:
                    c='Q';
			}
		}
		last_c = c;
        
		/* Check limits */
		if (xs>MAXSPEED) xs=MAXSPEED;
		if (xs<-MAXSPEED) xs=-MAXSPEED;
        
		clear_player(x+x_ofs,18+y_ofs);
        
		x+=xs;
        
		if ( (x<0) || (x>73) )
		{
			xs = 0;
			(x>0)?(x=73):(x=0);
		}
        
		blit_player(x+x_ofs,18+y_ofs);
        
		// Check for collision with zombies
		if (collide_player(x))
		{
			exploding = 1;
		}
	}
	else
	{
		switch (exploding++)
		{
            case 1:
                clear_player(x+x_ofs,21+y_ofs);
                blit_explosion(x+3+x_ofs,22+y_ofs,3);
                break;
            case 2:
                clear_explosion(x+3+x_ofs,22+y_ofs,3);
                blit_explosion(x+3+x_ofs,22+y_ofs,3);
                break;
            case 3:
                clear_explosion(x+3+x_ofs,22+y_ofs,3);
                blit_explosion(x+3+x_ofs,22+y_ofs,4);
                break;
            case 4:
                clear_explosion(x+3+x_ofs,22+y_ofs,4);
                blit_explosion(x+3+x_ofs,22+y_ofs,4);
                break;
            case 5:
                clear_explosion(x+3+x_ofs,22+y_ofs,4);
                blit_explosion(x+3+x_ofs,22+y_ofs,3);
                break;
            case 6:
                clear_explosion(x+3+x_ofs,22+y_ofs,3);
                blit_explosion(x+3+x_ofs,22+y_ofs,3);
                break;
            case 7:
                clear_explosion(x+3+x_ofs,22+y_ofs,3);
                blit_explosion(x+3+x_ofs,22+y_ofs,2);
                break;
            case 8:
                clear_explosion(x+3+x_ofs,22+y_ofs,2);
                blit_explosion(x+3+x_ofs,22+y_ofs,2);
                break;
            case 9:
                clear_explosion(x+3+x_ofs,22+y_ofs,2);
                blit_explosion(x+3+x_ofs,22+y_ofs,1);
                break;
            case 10:
                clear_explosion(x+3+x_ofs,22+y_ofs,1);
                blit_explosion(x+3+x_ofs,22+y_ofs,1);
                break;
            case 11:
                clear_explosion(x+3+x_ofs,22+y_ofs,1);
                c='Q';
                break;
		}
	}
    
	wmove(term,0,0);
	wrefresh(term);
    
	return (c!='Q');
}

void m_wait(long delay)
{
    /*
     // This is an algorithm I've tested to uniform speed on every CPU, but
     // gettimeofday resolution isn't very high and I got also very strange
     // and not uniform results...
     
     static struct timeval last={0,0};
     struct timeval now;
     long diff;
     
     if (gettimeofday(&now,NULL)<0)
     {
     // Error in gettimeofday... using old algorithm
     diff=0;
     }
     else
     {
     fprintf(stderr,"%lu . %lu - ",now.tv_sec,now.tv_usec);
     if (last.tv_sec==0) last=now;
     diff=(now.tv_sec-last.tv_sec)*1000000 + (now.tv_usec-last.tv_usec);
     last=now;
     }
     
     fprintf(stderr,"diff: %d, waiting %lu\n",diff,(delay-diff>0)?delay-diff:0);
     if (delay-diff>0)
     usleep(delay-diff);
     
     return;
     */
	usleep((int)delay);
}

void end_game()
{
	int y;
	for (y=21;y>-7;y--)
	{
		clear_player(end_x+x_ofs,y+y_ofs);
		blit_player(end_x+x_ofs,y-1+y_ofs);
        
		wmove(term,0,0);
		wrefresh(term);
        
		m_wait(DELAY);
        
		delete_zombies();
		delete_fires();
        
		move_fires();
		move_zombies();
        
		blit_zombies();
		blit_fires();
		blit_score(74+x_ofs,y_ofs,score);
		blit_borders(COL_RED);
	}
}

int main()
{
    srand((int)time(NULL));
	init_screen();
    
	if (!right_size())
	{
		endwin();
		fprintf(stderr,"Vialacteum must be run in an 80x25 terminal!\n");
		return -1;
	}
    
	presentation();
    init_zombies();
    init_waves();
    
    while (move_player())
	{
		m_wait(DELAY);
        
		delete_zombies();
		delete_fires();
        
		// move functions also performs collision check
		move_fires();
		move_zombies();
        
		blit_zombies();
		blit_fires();
		blit_score(74+x_ofs,y_ofs,score);
		blit_borders(COL_GREEN);
	}
    
	if (game_ended)
	{
		end_game();
	}
    
	// Flush input
	while (wgetch(term) != ERR);
    
	endwin();
    
	if (game_ended) final();
    
	printf("\nYou have made %d points!\n", score);
	printf("-= V-I-A-L-A-C-T-E-U-M =-\n");
    
	return 0;
}