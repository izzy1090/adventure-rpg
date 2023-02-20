#include "exploration.h"

int map[5][5] = { 
    {1, 2, 3, 4, 5}, 
    {10, 11, 12, 13, 14}, 
    {20, 21, 22, 23, 24}, 
    {30, 31, 32, 33, 34},
    {40, 41, 42, 43, 44}
};

// Player and party locations
Entity_Location JimaLocation = {.xPos = 0, .yPos = 0, .xMove = 1, .yMove = 1};

// Enemies on the map locations - we might want to consider giving certain enemy types the ability to move multiple squares
Entity_Location SmallMonsterLocation = {.xPos = 3, .yPos = 2, .xMove = 1, .yMove = 1};
Entity_Location FlyingBansheeLocation = {.xPos = 3, .yPos = 3, .xMove = 1, .yMove = 1};
Entity_Location GoblinLocation = {.xPos = 4, .yPos = 0, .xMove = 1, .yMove = 1};

// we can find the max_width of a matrix by finding the sizeof a single column of elements
// and divide it to by the sizeof a single element to get an understanding of how many elements it will take 
// to fill up an entire column of elements.
int max_width = sizeof(map[0]) / sizeof(map[0][0]);
// similar to the above, max_height finds the sizeof the entire 2 dimensional array, 
// and divides it by the sizeof an entire row to find how many rows are present in the entire array 
int max_height = sizeof(map) / sizeof(map[0]);

void checkMapBounds_Player(){
    bool lowerMapBound = (JimaLocation.xPos + JimaLocation.xMove) < 0;
    bool upperMapBound = (JimaLocation.xPos + JimaLocation.xMove) >= max_width;
    bool leftMapBound = (JimaLocation.yPos + JimaLocation.yMove) < 0;
    bool rightMapBound = (JimaLocation.yPos + JimaLocation.yMove) >= max_height;
    
    if (upperMapBound) {        
        JimaLocation.xPos += -JimaLocation.xMove;
    } else if (lowerMapBound){
        JimaLocation.xPos += JimaLocation.xMove;
    } else if (leftMapBound){
        JimaLocation.yPos += JimaLocation.yMove;
    } else if (rightMapBound) {
        JimaLocation.yPos += -JimaLocation.yMove;
    } 
}

// void checkMapBounds_Enemy(){
//     bool lowerMapBound = ((SmallMonsterLocation.xPos + SmallMonsterLocation.xMove) < 0) 
//     || ((FlyingBansheeLocation.xPos + FlyingBansheeLocation.xMove) < 0)
//     || ((GoblinLocation.xPos + GoblinLocation.xMove) < 0);

//     bool upperMapBound = ((SmallMonsterLocation.xPos + SmallMonsterLocation.xMove) >= max_width)
//     || ((FlyingBansheeLocation.xPos + FlyingBansheeLocation.xMove) >= max_width)
//     || ((GoblinLocation.xPos + GoblinLocation.xMove) >= max_width);

//     bool leftMapBound = ((SmallMonsterLocation.yPos + SmallMonsterLocation.yMove) < 0)
//     || ((FlyingBansheeLocation.yPos + FlyingBansheeLocation.yMove) < 0)
//     || ((GoblinLocation.yPos + GoblinLocation.yMove) < 0);

//     bool rightMapBound = ((SmallMonsterLocation.yPos + SmallMonsterLocation.yMove) >= max_height)
//     || ((FlyingBansheeLocation.yPos + FlyingBansheeLocation.yMove) >= max_height)
//     || ((GoblinLocation.yPos + GoblinLocation.yMove) >= max_height);

//     if (upperMapBound) {        
//         JimaLocation.xPos += -JimaLocation.xMove;
//     } else if (lowerMapBound){
//         JimaLocation.xPos += JimaLocation.xMove;
//     } else if (leftMapBound){
//         JimaLocation.yPos += JimaLocation.yMove;
//     } else if (rightMapBound) {
//         JimaLocation.yPos += -JimaLocation.yMove;
//     } 
// }

void smallMonsterPath(){
    Entity_Location currentEnemyLoc = {.xPos = 3, .yPos = 2, .xMove = 1, .yMove = 1};
    bool initial = currentEnemyLoc.xPos == SmallMonsterLocation.xPos && currentEnemyLoc.yPos == SmallMonsterLocation.yPos;
    bool firstMove = currentEnemyLoc.xPos + 1 == SmallMonsterLocation.xPos && currentEnemyLoc.yPos == SmallMonsterLocation.yPos;
    bool secondMove = currentEnemyLoc.xPos + 1 == SmallMonsterLocation.xPos && currentEnemyLoc.yPos + 1 == SmallMonsterLocation.yPos;
    bool completeLoop = TRUE;

    if (initial){   
        currentEnemyLoc.xPos += currentEnemyLoc.xMove;
    } else if (firstMove){
        currentEnemyLoc.yPos += currentEnemyLoc.yMove;   
    } else if (secondMove){
        currentEnemyLoc.yPos += -currentEnemyLoc.yMove;
    } else if (firstMove && completeLoop){
        currentEnemyLoc.xMove += -currentEnemyLoc.xMove;
    }
    SmallMonsterLocation.xPos = currentEnemyLoc.xPos;
    SmallMonsterLocation.yPos = currentEnemyLoc.yPos;
}

// // simple utility function to return back the enemies location as an integer
// int enemyLocation (char enemyName){
//     Entity *SmallMonster = enemyEntities(1);
//     Entity *FlyingBanshee = enemyEntities(2);
//     Entity *Goblin = enemyEntities(3);

//     if (enemyName == SmallMonster->name){
//         return SmallMonster->location;
//     } else if (enemyName == FlyingBanshee->name){
//         return FlyingBanshee->location;
//     } else if (enemyName == Goblin->location){
//         return Goblin->location;
//     }
// }

/* Checks to see if the enemy and hero location match, if they do, 
return the battle state. */
stateMachine enemyCheck(int heroLocation){
    Entity *SmallMonster = enemyEntities(1);
    SmallMonster->location = SmallMonsterLocation.xPos + SmallMonsterLocation.yPos;
    // Entity *FlyingBanshee = enemyEntities(2);
    // FlyingBanshee->location = FlyingBansheeLocation.xPos + FlyingBansheeLocation.yPos;
    // Entity *Goblin = enemyEntities(3);
    // Goblin->location = GoblinLocation.xPos + GoblinLocation.yPos;
    if (heroLocation == SmallMonster->location){
        return Battle;
    } 
    // else if (heroLocation == FlyingBanshee->location){
    //     return Battle;
    // } else if (heroLocation == Goblin->location){
    //     return Battle;
    // }
    return Exploration;
}

/* Moves the player in the direction according to the passed-in state. movePlayer also 
checks if an enemy or world event is present. If either are, then a new state is returned. */
stateMachine movePlayer(stateMachine_Exploration_MovePlayer currentState){
    Entity *Jima = playerEntities(1);
    Jima->location = JimaLocation.xPos + JimaLocation.yPos;

    checkMapBounds_Player();
    
    if (currentState == MovePlayer_Forward){
        // Below locations are for debugging purposes
        mvprintw(13, 10, "Player location: [%d][%d]", JimaLocation.xPos, JimaLocation.yPos);
        mvprintw(14, 10, "Enemies location: [%d][%d]", SmallMonsterLocation.xPos, SmallMonsterLocation.yPos);

        nextState = enemyCheck(Jima->location);
        JimaLocation.xPos += JimaLocation.xMove;
    } if (currentState == MovePlayer_Right){
        // Below locations are for debugging purposes
        mvprintw(13, 10, "Player location: [%d][%d]", JimaLocation.xPos, JimaLocation.yPos);
        mvprintw(14, 10, "Enemies location: [%d][%d]", SmallMonsterLocation.xPos, SmallMonsterLocation.yPos);

        nextState = enemyCheck(Jima->location);
        JimaLocation.yPos += JimaLocation.yMove;
    } if (currentState == MovePlayer_Down){
        // Below locations are for debugging purposes
        mvprintw(13, 10, "Player location: [%d][%d]", JimaLocation.xPos, JimaLocation.yPos);
        mvprintw(14, 10, "Enemies location: [%d][%d]", SmallMonsterLocation.xPos, SmallMonsterLocation.yPos);

        nextState = enemyCheck(Jima->location);
        JimaLocation.xPos += -JimaLocation.xMove;
    } if (currentState == MovePlayer_Left){
        // Below locations are for debugging purposes
        mvprintw(13, 10, "Player location: [%d][%d]", JimaLocation.xPos, JimaLocation.yPos);
        mvprintw(14, 10, "Enemies location: [%d][%d]", SmallMonsterLocation.xPos, SmallMonsterLocation.yPos);

        nextState = enemyCheck(Jima->location);
        JimaLocation.yPos += -JimaLocation.yMove;
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
        smallMonsterPath();
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