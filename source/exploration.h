#ifndef _EXPLORATION_H
#define _EXPLORATION_H

    #include "defines.h"
    #include "entity.h"
    #include "input.h"
    #include "messages.h"
    #include "maps.h"

    void checkMapBounds_Player();
    void checkMapBounds_Enemy();
    void smallMonsterPath();
    int enemyLocation (char enemyName);
    stateMachine enemyCheck(int heroLocation);
    stateMachine movePlayer(stateMachine_Exploration_MovePlayer currentState);
    stateMachine initExploration(stateMachine currentState);
    
#endif