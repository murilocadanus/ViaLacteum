//
//  game.c
//  ViaLacteum
//
//  Created by Marlus Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game.h"

int score = 0;
int end_x;
int game_ended = 0;

const bitmask bitmask_player={0x38,0x7C,0xFE,0x7C,0x00};

// Player dying
// This will be >0 if the player is dying */
int exploding = 0; 

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

int move_player(WINDOW *term, int x_ofs, int y_ofs)
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
        
		clear_player(x+x_ofs,21+y_ofs);
        
		x+=xs;
        
		if ( (x<0) || (x>73) )
		{
			xs = 0;
			(x>0)?(x=73):(x=0);
		}
        
		blit_player(x+x_ofs,21+y_ofs);
        
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

void end_game(WINDOW *term, int x_ofs, int y_ofs)
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

int quit_game(WINDOW *term)
{
    wrefresh(term);
    endwin();
    
    printf("\nVoce fez %d pontos!\n", score);
  	printf("Obrigado por jogar\n");
	printf("-= I-N-V-A-S-O-R-E-S =-\n");
    return 0;
}

int game(WINDOW *term, int x_ofs, int y_ofs)
{
    init_zombies();
    init_waves();

    while (move_player(term, x_ofs, y_ofs))
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
		end_game(term, x_ofs, y_ofs);
	}
    
	// Flush input
	while (wgetch(term) != ERR);
    
	endwin();
    
	if (game_ended) final();
    
	printf("\nYou have made %d points!\n", score);
	printf("-= I-N-V-A-S-O-R-E-S =-\n");
    return 0;
}
