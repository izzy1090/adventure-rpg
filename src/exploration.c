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
it creates a static variable with the same coordinates as the monster's location. This is then used to check against one 
monster's location (the SmallMonster) to see where they are and move them around. This needs to scale to include 
different enemies and to rely on the initial enemy location, rather than the need to create a static location 
for each enemy on the map. */
void enemyMovement(){
    Entity_Loc referenceSmallMonsterLoc = {.xPos = 3, .yPos = 2, .move = 1};
    bool initial = referenceSmallMonsterLoc.xPos == SmallMonsterLoc.xPos && referenceSmallMonsterLoc.yPos == SmallMonsterLoc.yPos;
    bool firstMove = referenceSmallMonsterLoc.xPos + 1 == SmallMonsterLoc.xPos && referenceSmallMonsterLoc.yPos == SmallMonsterLoc.yPos;
    bool secondMove = referenceSmallMonsterLoc.xPos + 1 == SmallMonsterLoc.xPos && referenceSmallMonsterLoc.yPos + 1 == SmallMonsterLoc.yPos;
    bool completeLoop = 1;

    if (initial){   
        referenceSmallMonsterLoc.xPos += referenceSmallMonsterLoc.move;
    } else if (firstMove){
        referenceSmallMonsterLoc.yPos += referenceSmallMonsterLoc.move;   
    } else if (secondMove){
        referenceSmallMonsterLoc.yPos += -referenceSmallMonsterLoc.move;
    } else if (firstMove && completeLoop){
        referenceSmallMonsterLoc.move += -referenceSmallMonsterLoc.move;
    }
    SmallMonsterLoc.xPos = referenceSmallMonsterLoc.xPos;
    SmallMonsterLoc.yPos = referenceSmallMonsterLoc.yPos;
}

/* Moves the player in the direction according to the passed-in state. movePlayer also 
checks if an enemy or world event is present. If either are, then a new state is returned. */
void movePlayer(stateMachine_Exploration_MovePlayer currentState){
    checkMapBounds_Player();
    
    if (currentState == MovePlayer_Forward){        
        JimaLoc.xPos += JimaLoc.move;
    } if (currentState == MovePlayer_Right){
        JimaLoc.yPos += JimaLoc.move;
    } if (currentState == MovePlayer_Down){
        JimaLoc.xPos += -JimaLoc.move;
    } if (currentState == MovePlayer_Left){
        JimaLoc.yPos += -JimaLoc.move;
    } 
}

/* Checks to see if the enemy and hero location match, if they do, 
return the battle state. Will need to include other enemy locations in the future. */
void enemyCheck(int heroXLoc, int heroYLoc){
    if (heroXLoc == SmallMonsterLoc.xPos && heroYLoc == SmallMonsterLoc.yPos){
        nextState = Battle;
        enemyEnountered = EnemyEncounter_SmallMonster;
    } 
}

/* Looks for an input from the controller during the exploration state.
Each time the forward key is pressed the character moves in a direction which triggers 
additional states to see if there is an enemy or a world event is present. If either are 
present a new state is returned and the state is ended. */
void initExploration(stateMachine currentState) {
    // char *queuedMessage = 0;
    Entity *Jima = playerEntities(1);
    // int ch;
    while (currentState == Exploration){
        VDP_drawText(Jima->name, 10, 10);
        // ch = input();
        enemyMovement();
        // mvprintw(13, 10, "Player location: [%d][%d]", JimaLoc.xPos, JimaLoc.yPos);
        // mvprintw(14, 10, "Enemies location: [%d][%d]", SmallMonsterLoc.xPos, SmallMonsterLoc.yPos);

        enemyCheck(JimaLoc.xPos, JimaLoc.yPos);
        // This breaks the initExploration while loop after an enemy is found
        if (nextState == Battle){
            currentState = Battle;
        }
        // if (ch == KEY_UP){
        //     queuedMessage = movePlayerMessage(1);            
        //     callStack(queuedMessage);
        //     movePlayer(MovePlayer_Forward);
        // } 
        // if (ch == KEY_LEFT){
        //     queuedMessage = movePlayerMessage(2);
        //     callStack(queuedMessage);
        //     movePlayer(MovePlayer_Left);
        // } 
        // if (ch == KEY_DOWN){
        //     queuedMessage = movePlayerMessage(3);
        //     callStack(queuedMessage);
        //     movePlayer(MovePlayer_Down);
        // } 
        // if (ch == KEY_RIGHT){
        //     queuedMessage = movePlayerMessage(4);
        //     callStack(queuedMessage);
        //     movePlayer(MovePlayer_Right);
        // }
    }
    
}