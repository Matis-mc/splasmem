#include "../actions.h"
#include <stdio.h>
#define MAX_PLAY_ACTION 5

char play_actions[] = {
    ACTION_STILL,
    ACTION_BOMB,
    ACTION_DASH_L,
    ACTION_MOVE_D,
    ACTION_MOVE_L

    
};

char get_action()
{
    static int i = 0;
    char ret_val = 0;

    ret_val = play_actions[i];
    i++;
    if (i >= MAX_PLAY_ACTION)
    {
        i = 0;
    } 
    return (ret_val);
}