#include "defines.h"
#include "input.h"
#include "battle.h"
#include "entity.h"
#include "window.h"
#include "exploration.h"

// stateMachine_Exploration explorationState = Exploration_LoadLevel;
// stateMachine_Exploration_Menu explorationMenuState = Exploration_Menu_Main;
// stateMachine_Exploration_Menu_Items explorationMenuItemsState = Exploration_Menu_Items_Main;
// stateMachine_Battle battleState = Battle_LoadLevel;
// stateMachine_Battle_Menu battleMenuState = Battle_Menu_Main;
// stateMachine_Battle_Menu_Attack battleMenuAttackState = Battle_Menu_Attack_SelectTarget;
// stateMachine_Attack attackState = Attack_LoadLevel;
// stateMachine_Attack_KillCheck attackKillCheckState = Attack_KillCheck_Check;
// stateMachine_GameOver gameOverState = Gameover_Lose;
// stateMachine_GameOver_Win gameOverWinState = Gameover_Win_Animation;
// stateMachine_GameOver_Lose gameOverLoseState = Gameover_Lose_Animation;
// stateMachine_MainMenu mainMenuState = MainMenu_Display;

/*=====================================================*
    
    To compile for use with unix use 
    "gcc -c file.c -o file.o" to generate output 
    files as 'file.o'. You can then bundle together all
    the 'file.o' along with the -ncurses flag to 
    compile.

*=====================================================*/

stateMachine initialGameState = Exploration;
bool gameStateInitialize = TRUE;

int main (void) {   
    Entity *SmallMonster = enemyEntities(1);
    beginNCurses();
    refresh();
    while (gameStateInitialize){
        if (initialGameState == Exploration){
            initExploration(initialGameState);
        } 
        if (nextState == Battle && enemyEnountered == EnemyEncounter_SmallMonster){
                initBattle(Battle, SmallMonster);
        }
        if (nextState == GameOver) {
            mvprintw(10, 10, "You're now in the game over state!");
        }
        // gameStateInitialize = false; 
    }
    endNCurses();
    return 0; 
}