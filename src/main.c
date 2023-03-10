#include "defines.h"
#include "battle.h"
#include "entity.h"
#include "exploration.h"


/*=====================================================*
    
                SGDK BUILD IN PROGRESS
    
*=====================================================*/


stateMachine initialGameState = Exploration;
bool gameStateInitialize = 1;
// declare pointer for Sprite to occupy
Sprite* sonic = NULL;
int main (void) {  
    // init Sprite engine 
    SPR_init();
    // then set the palette type for the sprite as well as point to the sprite data and the transfer method
    PAL_setPalette(PAL2, sonic_sprite.palette->data, DMA);
    sonic = SPR_addSprite(&sonic_sprite, 0, 0, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    Entity *SmallMonster = enemyEntities(1);

    while (gameStateInitialize){
        SPR_update();
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