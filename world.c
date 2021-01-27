#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "param.h"
#include "player.h"
#include "actions.h"

typedef void (*func)();
func fpointers[] = {action_still, action_move_l, action_move_r, action_move_u, action_move_d, action_dash_l,
                    action_dash_r, action_dash_u, action_dash_d, action_teleport_l, action_teleport_r,
                    action_teleport_u, action_teleport_d, action_splash, action_bomb};

/* !!!!!!!!!!!!!!!! MAP !!!!!!!!!!!!!!!!!!!!! */
uint8_t mapmem[MAP_SIZE * MAP_SIZE] = {0};

/*  PLAYERS */
t_player* players[MAX_PLAYERS] = {0};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_create_players(char* argv[])
{
    int i = 0;

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        players[i] = (t_player*) malloc(sizeof(t_player));
        player_init(players[i], i, argv[i+1]);
        world_paint_spot(players[i]->x, players[i]->y, players[i]->id);
    }
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_do_player_action(t_player *p_player)
{
    if(p_player->count!=0)
    {
        if(p_player->count==1){
            action_explosion(p_player->p_bomb);
        }

        p_player->count--;                
    }
    char a = p_player->get_action();
    if(p_player->credits >= 0)
    {
        fpointers[(int)a](p_player);
    }
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_paint_spot(uint32_t x, uint32_t y, uint32_t num)
{
    uint32_t pos = y * MAP_SIZE + x;
    mapmem[pos] = num;
}



/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_get_winner()
{
  
int tabPlayers[MAX_PLAYERS + 1] = {0};





    for(int y = 0; y < MAP_SIZE; y++)
    {
        for(int x=0; x<MAP_SIZE; x++)
        {
        tabPlayers[mapmem[y*MAP_SIZE+x]]++;
        }
    }
    
    

    int max = 1;
    for(int j = 1; j < MAX_PLAYERS; j++)
    {

        if(tabPlayers[j + 1] > tabPlayers[j])
        {
            max = j + 1;

        }
    }
    printf("Player %d wins !", max);
    
}
