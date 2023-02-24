#ifndef _EXPLORATION_H
#define _EXPLORATION_H

    #include "defines.h"
    #include "entity.h"
    #include "input.h"
    #include "messages.h"
    #include "maps.h"

    void checkMapBounds_Player();
    void enemyMovement();
    void enemyCheck(int heroXLoc, int heroYLoc);
    void movePlayer(stateMachine_Exploration_MovePlayer currentState);
    void initExploration(stateMachine currentState);
    
#endif