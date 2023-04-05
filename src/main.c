#include "defines.h"
#include "battle.h"
#include "entity.h"
#include "exploration.h"
#include "sprites.h"

/*=====================================================*
    
                SGDK BUILD IN PROGRESS
    
*=====================================================*/

stateMachine initialGameState = Exploration;
bool gameStateInitialize = 1;

int main (void) {  
    // Entity *SmallMonster = enemyEntities(1);

    while (gameStateInitialize){

        if (initialGameState == Exploration){
            initExploration(initialGameState);
        } 
        // if (nextState == Battle && enemyEnountered == EnemyEncounter_SmallMonster){
        //     initBattle(Battle, SmallMonster);
        // }
        
    }
    return (0); 
}