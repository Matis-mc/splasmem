#include "player.h"
#include "param.h"

actions_init()
{
    return 0;
}

void action_still(t_player *player)
{
    player->credits--;
}
void action_bomb(t_player *player){    
    if(player->count == 0){
        player->p_bomb=malloc(sizeof(t_bomb));
        player->count = 5;
        bomb_init(player->p_bomb, player->x, player->y, player->id);
        player->credits -= 9;
        printf(" bomb id : %d \n",player->p_bomb->id);
        printf(" bomb x : %d \n",player->p_bomb->x);
        printf(" bomb y : %d \n",player->p_bomb->y);
        return;
    }else{
        return;
    }

}
void action_move_l(t_player *player)
{
    player->x--;
    if(player->x < 0)
    {
        player->x = MAP_SIZE - 1;
    }
    player->credits--;
}

void action_move_r(t_player *player)
{
    player->x++;
    if(player->x > MAP_SIZE)
    {
        player->x = 0;
    }
    player->credits--;
}

void action_move_u(t_player *player)
{
    player->y--;
    if(player->y == -1)
    {
        player->y = MAP_SIZE-1;
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
        if(player->x < 0)
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
        if(player->x > MAP_SIZE)
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
        if(player->y < 0)
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
        if(player->y > MAP_SIZE)
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
        if(player->x <0)
        {
            player->x = MAP_SIZE;
        }
    }
    player->credits -= 2;
}

void action_teleport_r(t_player *player)
{
    for(int i = 0; i < 8; i++)
    {
        player->x++;
        if(player->x > MAP_SIZE)
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
        if(player->y < 0)
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
        if(player->y > MAP_SIZE)
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

    }
    else if(player->x == 0 && player->y==MAP_SIZE){
        world_paint_spot(player->x+1, player->y-1, player->id);
        world_paint_spot(player->x, player->y-1, player->id);
        world_paint_spot(player->x+1, player->y, player->id);
        player->credits-=8;

    }
    else if(player->x == MAP_SIZE && player->y==0){
        world_paint_spot(player->x-1, player->y+1, player->id);
        world_paint_spot(player->x, player->y+1, player->id);
        world_paint_spot(player->x-1, player->y, player->id);
        player->credits-=8;

    }
    else if(player->x == MAP_SIZE && player->y==MAP_SIZE){
        world_paint_spot(player->x-1, player->y-1, player->id);
        world_paint_spot(player->x, player->y-1, player->id);
        world_paint_spot(player->x-1, player->y, player->id);
        player->credits-=8;

    }
    // cas des 4 bords
    else if(player->x==0){
        world_paint_spot(player->x+1, player->y+1, player->id);
        world_paint_spot(player->x+1, player->y, player->id);
        world_paint_spot(player->x+1, player->y-1, player->id);
        world_paint_spot(player->x, player->y+1, player->id);
        world_paint_spot(player->x, player->y-1, player->id); 
        player->credits-=8;
    }
    else if(player->x==MAP_SIZE){
        world_paint_spot(player->x, player->y+1, player->id);
        world_paint_spot(player->x, player->y-1, player->id);
        world_paint_spot(player->x-1, player->y+1, player->id);
        world_paint_spot(player->x-1, player->y, player->id);
        world_paint_spot(player->x-1, player->y-1, player->id);
        player->credits-=8; 
    }
    else if(player->y==0){
        world_paint_spot(player->x-1, player->y, player->id);
        world_paint_spot(player->x+1, player->y, player->id);
        world_paint_spot(player->x+1, player->y+1, player->id);
        world_paint_spot(player->x, player->y+1, player->id);
        world_paint_spot(player->x-1, player->y+1, player->id); 
        player->credits-=8;
    }
    else if(player->y==MAP_SIZE){
        world_paint_spot(player->x-1, player->y, player->id);
        world_paint_spot(player->x+1, player->y, player->id);
        world_paint_spot(player->x+1, player->y+1, player->id);
        world_paint_spot(player->x, player->y+1, player->id);
        world_paint_spot(player->x-1, player->y+1, player->id); 
        player->credits-=8;
        }
    else{
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
    
}


void action_explosion(t_bomb *p_bomb){
    printf("entre dans fonction explosion");
    if(p_bomb->x == 0 && p_bomb->y==0){
        world_paint_spot(p_bomb->x+1, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x+1, p_bomb->y, p_bomb->id);

    }
    else if(p_bomb->x == 0 && p_bomb->y==MAP_SIZE){
        world_paint_spot(p_bomb->x+1, p_bomb->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x+1, p_bomb->y, p_bomb->id);

    }
    else if(p_bomb->x == MAP_SIZE && p_bomb->y==0){
        world_paint_spot(p_bomb->x-1, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y, p_bomb->id);

    }
    else if(p_bomb->x == MAP_SIZE && p_bomb->y==MAP_SIZE){
        world_paint_spot(p_bomb->x-1, p_bomb->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y, p_bomb->id);

    }
    // cas des 4 bords
    else if(p_bomb->x==0){
        world_paint_spot(p_bomb->x+1, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x+1, p_bomb->y, p_bomb->id);
        world_paint_spot(p_bomb->x+1, p_bomb->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y-1, p_bomb->id); 
    }
    else if(p_bomb->x==MAP_SIZE){
        world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y-1, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y-1, p_bomb->id); 
    }
    else if(p_bomb->y==0){
        world_paint_spot(p_bomb->x-1, p_bomb->y, p_bomb->id);
        world_paint_spot(p_bomb->x+1, p_bomb->y, p_bomb->id);
        world_paint_spot(p_bomb->x+1, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->id);
        world_paint_spot(p_bomb->x-1, p_bomb->y+1, p_bomb->id); 
    }
    else{
    world_paint_spot(p_bomb->x+1, p_bomb->y+1, p_bomb->id);
    world_paint_spot(p_bomb->x+1, p_bomb->y, p_bomb->id);
    world_paint_spot(p_bomb->x+1, p_bomb->y-1, p_bomb->id);
    world_paint_spot(p_bomb->x, p_bomb->y+1, p_bomb->id);
    world_paint_spot(p_bomb->x, p_bomb->y, p_bomb->id);
    world_paint_spot(p_bomb->x, p_bomb->y-1, p_bomb->id);
    world_paint_spot(p_bomb->x-1, p_bomb->y+1, p_bomb->id);
    world_paint_spot(p_bomb->x-1, p_bomb->y, p_bomb->id);
    world_paint_spot(p_bomb->x-1, p_bomb->y-1, p_bomb->id);
    }
}