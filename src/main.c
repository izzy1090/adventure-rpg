#include "defines.h"
#include "battle.h"
#include "entity.h"
#include "exploration.h"


/*=====================================================*
    
                SGDK BUILD IN PROGRESS
    
*=====================================================*/

stateMachine initialGameState = Exploration;
bool gameStateInitialize = 1;
Sprite *sonic = NULL;
int main (void) {   
    SPR_init();
    Entity *SmallMonster = enemyEntities(1);

    while (gameStateInitialize){

        if (initialGameState == Exploration){
            initExploration(initialGameState);
        } 
        if (nextState == Battle && enemyEnountered == EnemyEncounter_SmallMonster){
            initBattle(Battle, SmallMonster);
        }

        SYS_doVBlankProcess();
    }
    return (0); 
}