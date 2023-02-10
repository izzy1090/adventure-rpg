#ifndef _EXPLORATION_H
#define _EXPLORATION_H

    #include "defines.h"
    #include "entity.h"
    #include "input.h"
    #include "messages.h"
    #include "maps.h"

    bool enemyCheck(int heroLocation);
    stateMachine movePlayer(stateMachine_Exploration_MovePlayer currentState);
    stateMachine initExploration(stateMachine currentState);
    
#endif