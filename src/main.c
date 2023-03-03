#include <genesis.h>
#include "defines.h"
#include "input.h"
#include "battle.h"
#include "entity.h"
#include "exploration.h"

/*=====================================================*
    
                SGDK BUILD IN PROGRESS
    
*=====================================================*/

stateMachine initialGameState = Exploration;
bool gameStateInitialize = true;

int main (void) {   
    Entity *SmallMonster = enemyEntities(1);
    while (gameStateInitialize){
        if (initialGameState == Exploration){
            initExploration(initialGameState);
        } 
        // if (nextState == Battle && enemyEnountered == EnemyEncounter_SmallMonster){
        //         initBattle(Battle, SmallMonster);
        // }
        // if (nextState == GameOver) {
        //     VDP_drawText("You're now in the game over state!", 14, 10);
        // }
    }
    return (0); 
}