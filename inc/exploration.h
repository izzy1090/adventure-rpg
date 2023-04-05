#ifndef _EXPLORATION_H
#define _EXPLORATION_H

    #include "defines.h"
    #include "entity.h"
    #include "messages.h"
    #include "sprites.h"

    Map gameLoop_exploration_loadLevel();
    // void checkMapBounds_player();
    // void enemyMovement();
    // void enemyCheck(u16 heroXLoc, u16 heroYLoc);
    void moveSpriteLoc(stateMachine_Exploration_MovePlayer currentState);
    void handleInputExploration();
    void initExploration(stateMachine currentState);
    void updateSpriteAnim();
    void checkPlayerLocation();
    
#endif