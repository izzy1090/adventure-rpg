#ifndef _EXPLORATION_H
#define _EXPLORATION_H

    #include "defines.h"
    #include "entity.h"
    #include "messages.h"
    #include "sprites.h"

    void checkMapBounds_Player();
    void enemyMovement();
    void enemyCheck(u16 heroXLoc, u16 heroYLoc);
    void movePlayer(stateMachine_Exploration_MovePlayer currentState);
    void handleInputExploration();
    void initExploration(stateMachine currentState);
    
#endif