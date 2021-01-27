#ifndef __ACTIONS__
#define __ACTIONS__

#include "player.h"

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

enum action
{
    ACTION_STILL,
    ACTION_MOVE_L,
    ACTION_MOVE_R,
    ACTION_MOVE_U,
    ACTION_MOVE_D,
    ACTION_DASH_L,
    ACTION_DASH_R,
    ACTION_DASH_U,
    ACTION_DASH_D,
    ACTION_TELEPORT_L,
    ACTION_TELEPORT_R,
    ACTION_TELEPORT_U,
    ACTION_TELEPORT_D,
    ACTION_SPLASH,
    ACTION_BOMB,
    ACTION_NUMBER
};
void action_explosion(t_bomb *p_bomb);
void actions_do(t_player *p_player, enum action act_id);
void actions_init();
#endif
