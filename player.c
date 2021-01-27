#include <stdlib.h>
#include <SDL2/SDL.h>
#include <dlfcn.h>
#include "player.h"
#include "param.h"
#include <string.h>

int start_pos_x[] = {MAP_SIZE/4, MAP_SIZE/4, MAP_SIZE*3/4, MAP_SIZE*3/4};
int start_pos_y[] = {MAP_SIZE/4, MAP_SIZE*3/4, MAP_SIZE/4, MAP_SIZE*3/4};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void player_init(t_player* p_player, uint8_t num, char* argv)
{
    p_player->id = num + 1;
    p_player->color = 0;
    p_player->x = start_pos_x[num];
    p_player->y = start_pos_y[num];
    p_player->data = NULL;
    p_player->credits = P_CREDITS;
    p_player->count = 0;
    p_player->p_bomb = NULL;
    p_player->so_handle = dlopen(argv, RTLD_LAZY);
    if(p_player->so_handle == NULL)
        printf("problem");
    p_player->get_action = dlsym(p_player->so_handle, "get_action");
    if(p_player->get_action == NULL)
        printf("problem");
}

void bomb_init(t_bomb *p_bomb, uint32_t x, uint32_t y, uint32_t id){
    p_bomb->id = id;
    p_bomb->x=x;
    p_bomb->y=y;
}

