#include "defines.h"
#include "attack.h"

// stateMachine gameState = Exploration;
// stateMachine_Title titleState = Title_TitleScreen;
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

bool stateInitialize = TRUE;

int main () {
    
    Entity *Hero = newEntity(WARRIOR, "Jima");

    beginNCurses();
    char *queuedMessage = "hey";
    struct Queue* q = createQueue();

    refresh();
    while (1){
        clearAndMove(10, 10);
        displayMenu();
    }
    
    endNCurses();
    return 0;
}
