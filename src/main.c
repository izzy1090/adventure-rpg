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
Sprite* figther = NULL;

// This is where you can declare which animations you want to init.
#define ANIM_STILL 0
#define ANIM_IDLE 1
#define ANIM_WALK 2
#define ANIM_UPPERCUT 3

int main (void) {  
    // init Sprite engine 
    SPR_init();
    // then set the palette type for the sprite as well as point to the sprite data and the transfer method
    PAL_setPalette(PAL2, animated_fighter.palette->data, DMA);
    figther = SPR_addSprite(&animated_fighter, 100, 50, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    Entity *SmallMonster = enemyEntities(1);

    while (gameStateInitialize){
        SPR_update();
        // you can set the animation cycle to whatever the sprite is
        // in this case if you look at the sprite sheet you can see that 
        // animation cell 1 is an idle animation
        SPR_setAnim(figther, ANIM_UPPERCUT);
        // if (initialGameState == Exploration){
        //     initExploration(initialGameState);
        // } 
        // if (nextState == Battle && enemyEnountered == EnemyEncounter_SmallMonster){
        //     initBattle(Battle, SmallMonster);
        // }

        SYS_doVBlankProcess();
    }
    return (0); 
}