#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "param.h"
#include "world.h"
#include "actions.h"
#include "splash.h"

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */

void action_still(t_player *player);
void action_move_l(t_player *player);
void action_move_r(t_player *player);
void action_move_u(t_player *player);
void action_move_d(t_player *player);
void action_dash_l(t_player *player);
void action_dash_r(t_player *player);
void action_dash_u(t_player *player);
void action_dash_d(t_player *player);
void action_teleport_l(t_player *player);
void action_teleport_r(t_player *player);
void action_teleport_u(t_player *player);
void action_teleport_d(t_player *player);
void action_splash(t_player *player);
void action_bomb(t_player *player);

typedef void (*func)();
func fpointers[] = {action_still, action_move_l, action_move_r, action_move_u, action_move_d, action_dash_l,
                    action_dash_r, action_dash_u, action_dash_d, action_teleport_l, action_teleport_r,
                    action_teleport_u, action_teleport_d, action_splash, action_bomb};


void render_map()
{
    int i = 0;
    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    screenSurface = SDL_GetWindowSurface(window);

    for (i = 0; i < SPOT_NUM; i++)
    {
        rect.x = (i % MAP_SIZE) * SQUARE_SIZE;
        rect.y = (i / MAP_SIZE) * SQUARE_SIZE;
        SDL_FillRect(screenSurface, &rect, colors[mapmem[i]]);
    }
    SDL_UpdateWindowSurface(window);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void render_player()
{
    int i = 0;
    screenSurface = SDL_GetWindowSurface(window);
    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        rect.x = players[i]->x * SQUARE_SIZE;
        rect.y = players[i]->y * SQUARE_SIZE;
        SDL_FillRect(screenSurface, &rect, colors[i] - 0x00202020);
    }
    SDL_UpdateWindowSurface(window);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void main_loop()
{
    // int is_game_finish = 0;   vous pouvez l'utilisez
    while (!quitting)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quitting = 1;
            }
        }

        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if(players[i]->count!=0){
                if(players[i]->count==1){
                    action_explosion(players[i]->p_bomb);
                }else{
                    players[i]->count--;
                }
            }
            char a = players[i]->get_action();
            if(players[i]->credits >= 0)
            {
                fpointers[(int)a](players[i]);
                world_paint_spot(players[i]->x, players[i]->y, players[i]->id);
            }
        }

        render_map();

        render_player();
        SDL_Delay(100);
    }
}

void action_still(t_player *player)
{
    player->credits--;
}

void action_move_l(t_player *player)
{
    player->x--;
    if(player->x == 0)
    {
        player->x = MAP_SIZE;
    }
    player->credits--;
}

void action_move_r(t_player *player)
{
    player->x++;
    if(player->x == MAP_SIZE)
    {
        player->x = 0;
    }
    player->credits--;
}

void action_move_u(t_player *player)
{
    player->y++;
    if(player->y == 0)
    {
        player->y = MAP_SIZE - 1;
    }
    player->credits--;
}

void action_move_d(t_player *player)
{
    player->y++;
    if(player->y == MAP_SIZE)
    {
        player->y = 0;
    }
    player->credits--;
}

void action_dash_l(t_player *player)
{
    for(int i = 0; i < 8; i++)
    {
        player->x--;
        if(player->x == 0)
        {
            player->x = MAP_SIZE;
        }
        world_paint_spot(player->x, player->y, player->id);
    }
    player->credits -= 10;
}

void action_dash_r(t_player *player)
{
    for(int i = 0; i < 8; i++)
    {
        player->x++;
        if(player->x == MAP_SIZE)
        {
            player->x = 0;
        }
        world_paint_spot(player->x, player->y, player->id);
    }
    player->credits -= 10;
}

void action_dash_u(t_player *player)
{
    for(int i = 0; i < 8; i++)
    {
        player->y--;
        if(player->y == 0)
        {
            player->y = MAP_SIZE - 1;
        }
        world_paint_spot(player->x, player->y, player->id);
    }
    player->credits -= 10;
}

void action_dash_d(t_player *player)
{
    for(int i = 0; i < 8; i++)
    {
        player->y++;
        if(player->y == MAP_SIZE)
        {
            player->y = 1;
        }
        world_paint_spot(player->x, player->y, player->id);
    }
    player->credits -= 10;
}

void action_teleport_l(t_player *player)
{
    for(int i = 0; i < 8; i++)
    {
        player->x--;
        if(player->x ==0)
        {
            player->x = MAP_SIZE;
        }
        world_paint_spot(player->x, player->y, player->id);
    }
    player->credits -= 2;
}

void action_teleport_r(t_player *player)
{
    for(int i = 0; i < 8; i++)
    {
        player->x++;
        if(player->x == MAP_SIZE)
        {
            player->x = 0;
        }
    }
    player->credits -= 2;
}

void action_teleport_u(t_player *player)
{
    for(int i = 0; i < 8; i++)
    {
        player->y--;
        if(player->y == 0)
        {
            player->y = MAP_SIZE - 1;
        }
    }
    player->credits -= 2;
}

void action_teleport_d(t_player *player)
{
    for(int i = 0; i < 8; i++)
    {
        player->y++;
        if(player->y == MAP_SIZE)
        {
            player->y = 0;
        }
    }
    player->credits -= 2;
}

//______________________________________________________________________________
void action_splash(t_player *player){
    // cas des 4 coins
    if(player->x == 0 && player->y==0){
        world_paint_spot(player->x+1, player->y+1, player->id);
        world_paint_spot(player->x, player->y+1, player->id);
        world_paint_spot(player->x+1, player->y, player->id);
        player->credits-=8;
        return 0;

    }
    if(player->x == 0 && player->y==MAP_SIZE){
        world_paint_spot(player->x+1, player->y-1, player->id);
        world_paint_spot(player->x, player->y-1, player->id);
        world_paint_spot(player->x+1, player->y, player->id);
        player->credits-=8;
        return 0;

    }
    if(player->x == MAP_SIZE && player->y==0){
        world_paint_spot(player->x-1, player->y+1, player->id);
        world_paint_spot(player->x, player->y+1, player->id);
        world_paint_spot(player->x-1, player->y, player->id);
        player->credits-=8;
        return 0;

    }
    if(player->x == MAP_SIZE && player->y==MAP_SIZE){
        world_paint_spot(player->x-1, player->y-1, player->id);
        world_paint_spot(player->x, player->y-1, player->id);
        world_paint_spot(player->x-1, player->y, player->id);
        player->credits-=8;
        return 0;

    }
    // cas des 4 bords
    if(player->x==0){
        world_paint_spot(player->x+1, player->y+1, player->id);
        world_paint_spot(player->x+1, player->y, player->id);
        world_paint_spot(player->x+1, player->y-1, player->id);
        world_paint_spot(player->x, player->y+1, player->id);
        world_paint_spot(player->x, player->y-1, player->id); 
        player->credits-=8;
        return 0;       
    }
    if(player->x==MAP_SIZE){
        world_paint_spot(player->x, player->y+1, player->id);
        world_paint_spot(player->x, player->y-1, player->id);
        world_paint_spot(player->x-1, player->y+1, player->id);
        world_paint_spot(player->x-1, player->y, player->id);
        world_paint_spot(player->x-1, player->y-1, player->id);
        player->credits-=8; 
        return 0;
    }
    if(player->y==0){
        world_paint_spot(player->x-1, player->y, player->id);
        world_paint_spot(player->x+1, player->y, player->id);
        world_paint_spot(player->x+1, player->y+1, player->id);
        world_paint_spot(player->x, player->y+1, player->id);
        world_paint_spot(player->x-1, player->y+1, player->id); 
        player->credits-=8;
        return 0;
    }
    //cas sans problème
    world_paint_spot(player->x-1, player->y+1, player->id);
    world_paint_spot(player->x-1, player->y, player->id);
    world_paint_spot(player->x-1, player->y-1, player->id);
    world_paint_spot(player->x, player->y+1, player->id);
    world_paint_spot(player->x, player->y-1, player->id); 
    world_paint_spot(player->x+1, player->y+1, player->id);
    world_paint_spot(player->x+1, player->y, player->id);
    world_paint_spot(player->x+1, player->y-1, player->id);
    player->credits-=8;
    
}

void action_bomb(t_player *player){
    if(player->count==0){
        player->count=5;
        bomb_init(player->p_bomb, player->id, player->x, player->y);
        player->credits=player->credits - 9;
    }

}
void action_explosion(t_bomb* p_bomb){

    if(p_bomb->x == 0 && p_bomb->y==0){
        world_paint_spot(p_bomb->x+1, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x+1, p_bomb->y, p_bomb->id);
        return 0;

    }
    if(p_bomb->x == 0 && p_bomb->y==MAP_SIZE){
        world_paint_spot(p_bomb->x+1, p_bomb->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x+1, p_bomb->y, p_bomb->id);
        return 0;

    }
    if(p_bomb->x == MAP_SIZE && p_bomb->y==0){
        world_paint_spot(p_bomb->x-1, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y, p_bomb->id);
        return 0;

    }
    if(p_bomb->x == MAP_SIZE && p_bomb->y==MAP_SIZE){
        world_paint_spot(p_bomb->x-1, p_bomb->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y, p_bomb->id);
        return 0;

    }
    // cas des 4 bords
    if(p_bomb->x==0){
        world_paint_spot(p_bomb->x+1, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x+1, p_bomb->y, p_bomb->id);
        world_paint_spot(p_bomb->x+1, player->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y-1, p_bomb->id); 
        return 0;       
    }
    if(p_bomb->x==MAP_SIZE){
        world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y-1, p_bomb->id); 
        return 0;
    }
    if(p_bomb->y==0){
        world_paint_spot(p_bomb->x-1, p_bomb->y, p_bomb->id);
        world_paint_spot(p_bomb->x+1, p_bomb->y, p_bomb->id);
        world_paint_spot(p_bomb->x+1, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y+1, p_bomb->id); 
        return 0;
    }
    world_paint_spot(p_bomb->x+1, p_bomb->y+1, p_bomb->num);
    world_paint_spot(p_bomb->x+1, p_bomb->y, p_bomb->num);
    world_paint_spot(p_bomb->x+1, p_bomb->y-1, p_bomb->num);
    world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->num);
    world_paint_spot(p_bomb->x, p_bomb->y, p_bomb->num);
    world_paint_spot(p_bomb->x, p_bomb->y-1, p_bomb->num);
    world_paint_spot(p_bomb->x-1, p_bomb->y+1, p_bomb->num);
    world_paint_spot(p_bomb->x-1, p_bomb->y, p_bomb->num);
    world_paint_spot(p_bomb->x-1, p_bomb->y-1, p_bomb->num);
}
