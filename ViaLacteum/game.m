//
//  game.c
//  ViaLacteum
//
//  Created by Marlus Costa on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game.h"
#include "pause.h"
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

int score = 0;
int end_x;
int game_ended = 0;
int side = 1; // player side

const bitmask bitmask_player={0x38,0x7C,0xFE,0x7C,0x00};

// Player dying
// This will be >0 if the player is dying */
int exploding = 0; 
NSSound *gameMusic;
NSSound *shoot;

int collide_player(int x)
{
	int check_x,check_y;
	for (check_y=0; check_y<MAX_HEIGHT; check_y++)
	{
		for (check_x=0; check_x<8; check_x++)
		{
			if ( (bitmask_player[check_y] & (0x80 >> check_x)) != 0 )
			{
				if (collide_foes(x+check_x,21+check_y)>=0)
					return 1;
			}
		}
	}
	return 0;
}

int move_player(WINDOW *term, int x_ofs, int y_ofs)
{
	int c = 0; // character readen
	static int last_c = -1;
	static int x = 37; // player position
	static int xs = 0; // player speed
    
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
                    side = 0;
                    break;
                case KEY_RIGHT:
                    xs++;
                    side = 1;
                    break;
                case KEY_DOWN:
                    xs=0;
                    break;
                case ' ':
                case KEY_ENTER_:
                    shoot = [[NSSound alloc] initWithContentsOfFile:@"resources/Shoot.wav" byReference:YES];
                    [shoot setCurrentTime:0.0];
                    [shoot play];
                    new_fire(x+3,21, side);
                    break;
                case KEY_ESC:
                    c='P';
			}
		}
		last_c = c;
        
		// Check limits
		if (xs>MAXSPEED) xs=MAXSPEED;
		if (xs<-MAXSPEED) xs=-MAXSPEED;
        
        clear_player_right(x+x_ofs,18+y_ofs);
        clear_player_left(x+x_ofs,18+y_ofs);            
        
		x+=xs;
        
		if ( (x<0) || (x>72) )
		{
			xs = 0;
			(x>0)?(x=72):(x=0);
		}
        
        if(side)
            blit_player_right(x+x_ofs,18+y_ofs);
        else
            blit_player_left(x+x_ofs,18+y_ofs);
        
		// Check for collision with foes
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
                clear_player_right(x+x_ofs,21+y_ofs);
                clear_player_left(x+x_ofs,21+y_ofs);
                
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
    
    if (c == 'P')
    {
        pause_game_music();
        
        int pause_menu = pause_game(term, x_ofs, y_ofs);
        if (pause_menu == CONTINUAR_JOGO)
        {
            play_game_music();
            c = 'A';
        }
        else if (pause_menu == MENU_PRINCIPAL)
        {
            unload_game_music();
            c = 'V';
        }                
        else if (pause_menu == SAIR)
        {
            c = 'Q';
        }
        
    }
    
	return c;
}

void m_wait(long delay)
{
	usleep((int)delay);
}

void end_game(WINDOW *term, int x_ofs, int y_ofs)
{
	int y;
	for (y=21;y>-7;y--)
	{
        clear_player_right(end_x+x_ofs,y+y_ofs);
        clear_player_left(end_x+x_ofs,y+y_ofs);

        if(side)
            blit_player_right(end_x+x_ofs,y-1+y_ofs);
        else
            blit_player_left(end_x+x_ofs,y-1+y_ofs);
        
		wmove(term,0,0);
		wrefresh(term);
        
		m_wait(DELAY);
        
		delete_foes();
		delete_fires();
        
		move_fires();
		move_foes();
        
		blit_foes();
		blit_fires();
		blit_score(74+x_ofs,y_ofs,score);
		blit_borders(COL_RED);
	}
}

void game_over(WINDOW *term, int x_ofs, int y_ofs)
{
	int y;
    
    // Faz a levitacao
	for (y=21;y>-7;y--)
	{
        blit_scene();
        clear_player_right(end_x+x_ofs,y+y_ofs);
        clear_player_left(end_x+x_ofs,y+y_ofs);
        
        if(side)
            blit_player_right(end_x+x_ofs,y-1+y_ofs);
        else
            blit_player_left(end_x+x_ofs,y-1+y_ofs);
        
		wmove(term,0,0);
		wrefresh(term);
        
		m_wait(DELAY);
        
		//delete_foes();
		delete_fires();
        
		move_fires();
		//move_foes();
        
		//blit_foes();
		blit_fires();
		blit_score(74+x_ofs,y_ofs,score);
		//blit_borders(COL_RED);
	}
    
    wclear(term);
    // Mostra o inimigo
    SET_COLOR(COL_WHITE);
    
    int j = 0;
    for (j=0; j<18; j++)
    {    
        mvwprintw(term, 2, 28 ,    "        GAME OVER       ");             
        
        mvwprintw(term, 4, 28 ,    "         #iiiii#     ");     
        mvwprintw(term, 5, 28 ,    "       #iEKWWWKEi#       ");
        mvwprintw(term, 6, 28 ,    "      iEKKKW#WKKKEi      ");
        mvwprintw(term, 7, 28 ,    "     #EWWKKW#WKKWWE#     ");
        mvwprintw(term, 8, 28 ,    "    #EWKEKWKKKWKEKWE#    ");
        mvwprintw(term, 9, 28 ,    "    #EW EWKWWWKWE WE#    ");
        mvwprintw(term, 10, 28 ,    "    #EK  EEKKKEE  KE#    ");
        mvwprintw(term, 11, 28 ,    "    #EK   EEKEE   KE#    ");
        mvwprintw(term, 12, 28 ,    "    #EK    WWW    KE#    ");
        mvwprintw(term, 13, 28 ,   "     iK    EWE    Ki     ");
        mvwprintw(term, 14, 28 ,   "     #EK   EWE   KE#     ");
        mvwprintw(term, 15, 28 ,   "     #EWEE E#E EEWE#     ");
        mvwprintw(term, 16, 28 ,   "      #KW#KKKKK#WK#      ");
        mvwprintw(term, 17, 28 ,   "       iWWWKEKWWWi       ");
        mvwprintw(term, 18, 28 ,   "        #KWKEKWK#        ");
        if (j % 2)
            mvwprintw(term, 19, 28 ,   "         #KW WK#         ");
        else
            mvwprintw(term, 19, 28 ,   "         #KWWWK#         ");
        mvwprintw(term, 20, 28 ,   "          #KWK#          ");
        mvwprintw(term, 21, 28 ,   "           #i#           "); 
        
        
        if (j % 2)
            mvwprintw(term, 23, 32 ,   "Você foi abduzido...");
        else
            mvwprintw(term, 23, 28 ,   "");
        
        wmove(term,0,0);
		wrefresh(term);
        refresh();
        
		m_wait(DELAY + 400000);
        wclear(term);
    }
}

void final()
{
	printf("\n    Parabens voce sobreviveu!\n");
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

int show_dialogs()
{
    mvprintw(LINES - 1, 4, "Cuidado com os cinzentos.");
    
    return 0;
}

void load_game_music()
{
    gameMusic = [[NSSound alloc] initWithContentsOfFile:@"resources/Gameplay.wav" byReference:YES];
    [gameMusic setCurrentTime:0.0];
    [gameMusic play];
}

void unload_game_music()
{
    [gameMusic stop];
}

void pause_game_music()
{
    [gameMusic pause];
}

void play_game_music()
{
    [gameMusic play];
}

int game(WINDOW *term, int x_ofs, int y_ofs)
{   
    unload_main_music();
    load_game_music();
    
    init_foes();
    init_waves();
    show_dialogs();
    blit_scene();
    
    char input_result = ' ';
    
    while ((input_result = move_player(term, x_ofs, y_ofs)))
    {        
        blit_scene();
        
        m_wait(DELAY);

        delete_foes();
        delete_fires();

        // move functions also performs collision check
        move_fires();
        move_foes();

        blit_foes();
        blit_fires();
        blit_score(74+x_ofs,y_ofs,score);
        blit_borders(COL_GREEN);
        
        if (input_result == 'Q') // Sair do jogo
            break;
        else if (input_result == 'V') // Voltar para o menu
            break;
        
    }    
    
    // TODO ALTERAR O GAME OVER
    if (input_result == 'V')
    {
        load_menu();
        
        // Utilizar para o game over
        //game_over(term, 37, y_ofs);
        //main();
    }
    
	if (game_ended)
	{
		end_game(term, x_ofs, y_ofs);
	}
    
	// Flush input
	while (wgetch(term) != ERR);
    
	endwin();
    
	if (game_ended) final();
    
	return quit_game(term);
}
