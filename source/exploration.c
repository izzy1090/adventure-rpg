#include "exploration.h"

int map[4][4] = { 
    {0, 1, 2, 3}, 
    {10, 11, 12, 13}, 
    {20, 21, 22, 23}, 
    {30, 31, 32, 33}
};

int row = 0;
int col = 0;

/* Checks to see if the enemy and hero location passed-in are in the vicinity of each other. 
If they are, then return true, otherwise return false. */
bool enemyCheck(int heroLocation){
    Entity *SmallMonster = enemyEntities(1);
    SmallMonster->location = map[2][1];
    Entity *FlyingBanshee = enemyEntities(2);
    FlyingBanshee->location = map[3][0];
    Entity *Goblin = enemyEntities(3);
    Goblin->location = map[0][3];

    if (heroLocation == SmallMonster->location || heroLocation == FlyingBanshee->location || heroLocation == Goblin->location){
        return true;
    } else return false;

}

/* Moves the player in the direction according to the passed-in state. movePlayer also 
checks if an enemy or world event is present. If either are, then a new state is returned. */
stateMachine movePlayer(stateMachine_Exploration_MovePlayer currentState){
    Entity *Jima = playerEntities(1);
    Jima->location = map[0][0];

    bool enemyPresent = FALSE;

    if (currentState == MovePlayer_Forward){
        Jima->location = map[row++][col];
    } 
    else if (currentState == MovePlayer_Left){
        Jima->location = map[row][col--];
    } 
    else if (currentState == MovePlayer_Down){
        Jima->location = map[row--][col];
    } 
    else if (currentState == MovePlayer_Right){
        Jima->location = map[row][col++];
    } 
    // proves that the states are switching and the hero's location is changing
    mvprintw(10, 10, "%d", Jima->location);
    enemyPresent = enemyCheck(Jima->location);
    if (enemyPresent) {
        nextState = Battle;
    } 
    return nextState;
}

/* Looks for an input from the controller during the exploration state.
Each time the forward key is pressed the character moves in a direction which triggers 
additional states to see if there is an enemy or a world event is present. If either are 
present a new state is returned and the state is ended. */
stateMachine initExploration(stateMachine currentState) {
    char *queuedMessage = NULL;
    int ch;
    while (currentState == Exploration){
        ch = input();
        if (ch == KEY_UP){
            queuedMessage = movePlayerMessage(1);
            callStack(queuedMessage);
            currentState = movePlayer(MovePlayer_Forward);
        } 
        else if (ch == KEY_LEFT){
            queuedMessage = movePlayerMessage(2);
            callStack(queuedMessage);
            currentState = movePlayer(MovePlayer_Left);
        } else if (ch == KEY_DOWN){
            queuedMessage = movePlayerMessage(3);
            callStack(queuedMessage);
            currentState = movePlayer(MovePlayer_Down);
        } else if (ch == KEY_RIGHT){
            queuedMessage = movePlayerMessage(4);
            callStack(queuedMessage);
            currentState = movePlayer(MovePlayer_Right);
        }
    }
    return currentState;
}