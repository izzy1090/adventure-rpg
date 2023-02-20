#include "exploration.h"

int map[5][5] = { 
    {1, 2, 3, 4, 5}, 
    {10, 11, 12, 13, 14}, 
    {20, 21, 22, 23, 24}, 
    {30, 31, 32, 33, 34},
    {40, 41, 42, 43, 44}
};

/* Player and party locations to start. This starts off as static locations for a singular map. 
This will need to scale as the project scales. */
Entity_Loc JimaLoc = {.xPos = 0, .yPos = 0, .move = 1};

// Enemies on the map locations - we might want to consider giving certain enemy types the ability to move multiple squares
Entity_Loc SmallMonsterLoc = {.xPos = 3, .yPos = 2, .move = 1};

/* We can find the maxWidth of a matrix by finding the sizeof a single column of elements
and divide it to by the sizeof a single element to get an understanding of how many elements it will take 
to fill up an entire column of elements. */
int maxWidth = sizeof(map[0]) / sizeof(map[0][0]);
/* Similar to the above, maxHeight finds the sizeof the entire 2 dimensional array, 
and divides it by the sizeof an entire row to find how many rows are present in the entire array. */
int maxHeight = sizeof(map) / sizeof(map[0]);

/* This checks the player's location to see if it ever exceeds the boundaries of the current map. 
The function can easily scale later on to include multiple maps. */
void checkMapBounds_Player(){
    bool lowerMapBound = (JimaLoc.xPos + JimaLoc.move) < 0;
    bool upperMapBound = (JimaLoc.xPos + JimaLoc.move) >= maxWidth;
    bool leftMapBound = (JimaLoc.yPos + JimaLoc.move) < 0;
    bool rightMapBound = (JimaLoc.yPos + JimaLoc.move) >= maxHeight;
    
    if (upperMapBound) {        
        JimaLoc.xPos += -JimaLoc.move;
    } else if (lowerMapBound){
        JimaLoc.xPos += JimaLoc.move;
    } else if (leftMapBound){
        JimaLoc.yPos += JimaLoc.move;
    } else if (rightMapBound) {
        JimaLoc.yPos += -JimaLoc.move;
    } 
}

/* This is currently a temporary way to handle the enemy path for a single enemy. When you invoke the function, 
it creates a static variable a single reference point on the map which is then used to check against one 
monster's location (the SmallMonster) to see where they are and move them around. This needs to scale to include 
different enemies and to rely on the initial enemy location, rather than the need to create a state location 
for each enemy on the map. */
void enemyPath(){
    Entity_Loc currentEnemyLoc = {.xPos = 3, .yPos = 2, .move = 1};
    bool initial = currentEnemyLoc.xPos == SmallMonsterLoc.xPos && currentEnemyLoc.yPos == SmallMonsterLoc.yPos;
    bool firstMove = currentEnemyLoc.xPos + 1 == SmallMonsterLoc.xPos && currentEnemyLoc.yPos == SmallMonsterLoc.yPos;
    bool secondMove = currentEnemyLoc.xPos + 1 == SmallMonsterLoc.xPos && currentEnemyLoc.yPos + 1 == SmallMonsterLoc.yPos;
    bool completeLoop = TRUE;

    if (initial){   
        currentEnemyLoc.xPos += currentEnemyLoc.move;
    } else if (firstMove){
        currentEnemyLoc.yPos += currentEnemyLoc.move;   
    } else if (secondMove){
        currentEnemyLoc.yPos += -currentEnemyLoc.move;
    } else if (firstMove && completeLoop){
        currentEnemyLoc.move += -currentEnemyLoc.move;
    }
    SmallMonsterLoc.xPos = currentEnemyLoc.xPos;
    SmallMonsterLoc.yPos = currentEnemyLoc.yPos;
}

/* Checks to see if the enemy and hero location match, if they do, 
return the battle state. */
stateMachine enemyCheck(int heroLocation){
    Entity *SmallMonster = enemyEntities(1);
    SmallMonster->location = SmallMonsterLoc.xPos + SmallMonsterLoc.yPos;

    if (heroLocation == SmallMonster->location){
        return Battle;
    } 
    return Exploration;
}

/* Moves the player in the direction according to the passed-in state. movePlayer also 
checks if an enemy or world event is present. If either are, then a new state is returned. */
stateMachine movePlayer(stateMachine_Exploration_MovePlayer currentState){
    Entity *Jima = playerEntities(1);
    Jima->location = JimaLoc.xPos + JimaLoc.yPos;

    checkMapBounds_Player();
    
    if (currentState == MovePlayer_Forward){
        // Below locations are for debugging purposes
        mvprintw(13, 10, "Player location: [%d][%d]", JimaLoc.xPos, JimaLoc.yPos);
        mvprintw(14, 10, "Enemies location: [%d][%d]", SmallMonsterLoc.xPos, SmallMonsterLoc.yPos);

        nextState = enemyCheck(Jima->location);
        JimaLoc.xPos += JimaLoc.move;
    } if (currentState == MovePlayer_Right){
        // Below locations are for debugging purposes
        mvprintw(13, 10, "Player location: [%d][%d]", JimaLoc.xPos, JimaLoc.yPos);
        mvprintw(14, 10, "Enemies location: [%d][%d]", SmallMonsterLoc.xPos, SmallMonsterLoc.yPos);

        nextState = enemyCheck(Jima->location);
        JimaLoc.yPos += JimaLoc.move;
    } if (currentState == MovePlayer_Down){
        // Below locations are for debugging purposes
        mvprintw(13, 10, "Player location: [%d][%d]", JimaLoc.xPos, JimaLoc.yPos);
        mvprintw(14, 10, "Enemies location: [%d][%d]", SmallMonsterLoc.xPos, SmallMonsterLoc.yPos);

        nextState = enemyCheck(Jima->location);
        JimaLoc.xPos += -JimaLoc.move;
    } if (currentState == MovePlayer_Left){
        // Below locations are for debugging purposes
        mvprintw(13, 10, "Player location: [%d][%d]", JimaLoc.xPos, JimaLoc.yPos);
        mvprintw(14, 10, "Enemies location: [%d][%d]", SmallMonsterLoc.xPos, SmallMonsterLoc.yPos);

        nextState = enemyCheck(Jima->location);
        JimaLoc.yPos += -JimaLoc.move;
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
        enemyPath();
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