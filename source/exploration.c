#include "exploration.h"

int map[5][5] = { 
    {1, 2, 3, 4, 5}, 
    {10, 11, 12, 13, 14}, 
    {20, 21, 22, 23, 24}, 
    {30, 31, 32, 33, 34},
    {40, 41, 42, 43, 44}
};

Entity_Location playerEntity_Location = {.xPos = 0, .yPos = 0, .xMove = 1, .yMove = 1};

// we can find the max_width of a matrix by finding the sizeof a single column of elements
// and divide it to by the sizeof a single element to get an understanding of how many elements it will take 
// to fill up an entire column of elements.
int max_width = sizeof(map[0]) / sizeof(map[0][0]);
// similar to the above, max_height finds the sizeof the entire 2 dimensional array, 
// and divides it by the sizeof an entire row to find how many rows are present in the entire array 
int max_height = sizeof(map) / sizeof(map[0]);

// void goblinMovement(){
//     Entity *Goblin = enemyEntities(3);
//     Goblin->Entity_Location = map[3][2];
//     enemyPos = Goblin->Entity_Location;

//     Entity *Monster = enemyEntities(1);
//     Monster->location = enemyEntity_location.xPos + enemyEntity_location.yPos;

//     bool enemyFound = Jima->location == Monster->location;
//     if (enemyFound){
//         mvprintw(15, 10, "here!");
//     }

//     if (enemyPos == map[3][2]){
//        enemyPos = map[enemyCol][enemyRow--]; 
       
//     } else if (enemyPos == map[2][2]){
//         enemyPos = map[enemyRow][enemyCol++];
        
//     } else if (enemyPos == map[2][3]){
//         enemyPos = map[enemyRow++][enemyCol];
        
//     } else if (enemyPos == map[3][3]){
//         enemyPos = map[enemyRow][enemyCol--];
//     } else if (enemyPos == 0) {
//         enemyPos = map[3][2];
//     }
// }

void checkMapBounds(){
    bool lowerMapBound = (playerEntity_Location.xPos + playerEntity_Location.xMove) < 0;
    bool upperMapBound = (playerEntity_Location.xPos + playerEntity_Location.xMove) >= max_width;
    bool leftMapBound = (playerEntity_Location.yPos + playerEntity_Location.yMove) < 0;
    bool rightMapBound = (playerEntity_Location.yPos + playerEntity_Location.yMove) >= max_height;
    
    if (upperMapBound) {        
        playerEntity_Location.xPos += -playerEntity_Location.xMove;
    } else if (lowerMapBound){
        playerEntity_Location.xPos += playerEntity_Location.xMove;
    } else if (leftMapBound){
        playerEntity_Location.yPos += playerEntity_Location.yMove;
    } else if (rightMapBound) {
        playerEntity_Location.yPos += -playerEntity_Location.yMove;
    } 
}

/* Checks to see if the enemy and hero location match, if they do, 
return the battle state. */
stateMachine enemyCheck(int heroLocation){
    Entity_Location monsterEntity_location = {.xPos = 3, .yPos = 2, .xMove = 1, .yMove = 1};
    Entity *Monster = enemyEntities(1);
    Monster->location = monsterEntity_location.xPos + monsterEntity_location.yPos;

    Entity_Location flyingBansheeEntity_location = {.xPos = 3, .yPos = 3, .xMove = 1, .yMove = 1};
    Entity *FlyingBanshee = enemyEntities(1);
    FlyingBanshee->location = flyingBansheeEntity_location.xPos + flyingBansheeEntity_location.yPos;

    if (heroLocation == Monster->location){
        return Battle;
    } else if (heroLocation == FlyingBanshee->location){
        return Battle;
    }
    return Exploration;
}

/* Moves the player in the direction according to the passed-in state. movePlayer also 
checks if an enemy or world event is present. If either are, then a new state is returned. */
stateMachine movePlayer(stateMachine_Exploration_MovePlayer currentState){
    Entity *Jima = playerEntities(1);
    Jima->location = playerEntity_Location.xPos + playerEntity_Location.yPos;

    checkMapBounds();
    
    if (currentState == MovePlayer_Forward){
        mvprintw(13, 10, "Player location: [%d][%d]", playerEntity_Location.xPos, playerEntity_Location.yPos);
        nextState = enemyCheck(Jima->location);
        playerEntity_Location.xPos += playerEntity_Location.xMove;
    } if (currentState == MovePlayer_Right){
        mvprintw(13, 10, "Player location: [%d][%d]", playerEntity_Location.xPos, playerEntity_Location.yPos);
        nextState = enemyCheck(Jima->location);
        playerEntity_Location.yPos += playerEntity_Location.yMove;
    } if (currentState == MovePlayer_Down){
        mvprintw(13, 10, "Player location: [%d][%d]", playerEntity_Location.xPos, playerEntity_Location.yPos);
        nextState = enemyCheck(Jima->location);
        playerEntity_Location.xPos += -playerEntity_Location.xMove;
    } if (currentState == MovePlayer_Left){
        mvprintw(13, 10, "Player location: [%d][%d]", playerEntity_Location.xPos, playerEntity_Location.yPos);
        nextState = enemyCheck(Jima->location);
        playerEntity_Location.yPos += -playerEntity_Location.yMove;
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
        if (ch == KEY_LEFT){
            queuedMessage = movePlayerMessage(2);
            callStack(queuedMessage);
            currentState = movePlayer(MovePlayer_Left);
        } 
        if (ch == KEY_DOWN){
            queuedMessage = movePlayerMessage(3);
            callStack(queuedMessage);
            currentState = movePlayer(MovePlayer_Down);
        } 
        if (ch == KEY_RIGHT){
            queuedMessage = movePlayerMessage(4);
            callStack(queuedMessage);
            currentState = movePlayer(MovePlayer_Right);
        }
    }
    return currentState;
}