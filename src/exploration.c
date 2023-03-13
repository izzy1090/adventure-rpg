#include "exploration.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

// Empty pointer for Sprite
Sprite* fighter = NULL; 

int map[MAP_WIDTH][MAP_HEIGHT] = { 
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 
};

/* Player and party locations to start. This starts off as static locations for a singular map. 
This will need to scale as the project scales. */
Entity_Loc JimaLoc = {.xPos = 0, .yPos = 0, .move = 1};

// Enemies on the map locations - we might want to consider giving certain enemy types the ability to move multiple squares
Entity_Loc SmallMonsterLoc = {.xPos = 3, .yPos = 2, .move = 1};

/* This checks the player's location to see if it ever exceeds the boundaries of the current map. 
The function can easily scale later on to include multiple maps. */
void checkMapBounds_Player(){
    bool lowerMapBound = (JimaLoc.yPos + JimaLoc.move) < 0;
    bool upperMapBound = (JimaLoc.yPos + JimaLoc.move) >= MAP_HEIGHT;
    bool leftMapBound = (JimaLoc.xPos + JimaLoc.move)  < 0;
    bool rightMapBound = (JimaLoc.xPos + JimaLoc.move) >= MAP_WIDTH;
    
    if (upperMapBound) {        
        JimaLoc.yPos = 0;
    } else if (lowerMapBound){
        JimaLoc.yPos = MAP_HEIGHT - 1;
    } else if (leftMapBound){
        JimaLoc.xPos = MAP_WIDTH - 1;
    } else if (rightMapBound) {
        JimaLoc.xPos = 0;
    } 
}

/* This is currently a temporary way to handle the enemy path for a single enemy. When you invoke the function, 
it creates a static variable with the same coordinates as the monster's location. This is then used to check against one 
monster's location (the SmallMonster) to see where they are and move them around. This needs to scale to include 
different enemies and to rely on the initial enemy location, rather than the need to create a static location 
for each enemy on the map. */
void enemyMovement(){
    
    Entity_Loc refSmallMonsterLoc = {.xPos = 3, .yPos = 2, .move = 1};
    bool initial = refSmallMonsterLoc.xPos == SmallMonsterLoc.xPos & refSmallMonsterLoc.yPos == SmallMonsterLoc.yPos;
    bool firstMove = refSmallMonsterLoc.xPos + 1 == SmallMonsterLoc.xPos & refSmallMonsterLoc.yPos == SmallMonsterLoc.yPos;
    bool secondMove = refSmallMonsterLoc.xPos + 1 == SmallMonsterLoc.xPos & refSmallMonsterLoc.yPos + 1 == SmallMonsterLoc.yPos;
    bool completeLoop = 1;

    if (initial){   
        refSmallMonsterLoc.yPos += refSmallMonsterLoc.move;
    } else if (firstMove){
        refSmallMonsterLoc.xPos += refSmallMonsterLoc.move;   
    } else if (secondMove){
        refSmallMonsterLoc.xPos += -refSmallMonsterLoc.move;
    } else if (firstMove && completeLoop){
        refSmallMonsterLoc.move += -refSmallMonsterLoc.move;
    }
    SmallMonsterLoc.yPos = refSmallMonsterLoc.yPos;
    SmallMonsterLoc.xPos = refSmallMonsterLoc.xPos;
}

/* Moves the player in the direction according to the passed-in state. movePlayer also 
checks if an enemy or world event is present. If either are, then a new state is returned. */
void movePlayer(stateMachine_Exploration_MovePlayer currentState){
    if (currentState == MovePlayer_Forward){  
        SPR_setAnim(fighter, ANIM_WALK);      
        JimaLoc.yPos += JimaLoc.move;
    } else if (currentState == MovePlayer_Right){
        JimaLoc.xPos += JimaLoc.move;
    } else if (currentState == MovePlayer_Down){
        JimaLoc.yPos += -JimaLoc.move;
    } else if (currentState == MovePlayer_Left){
        JimaLoc.xPos += -JimaLoc.move;
    } 
    checkMapBounds_Player();
}

/* Checks to see if the enemy and hero location match, if they do, 
return the battle state. Will need to include other enemy locations in the future. */
void enemyCheck(u16 heroXLoc, u16 heroYLoc){
    if (heroXLoc == SmallMonsterLoc.xPos && heroYLoc == SmallMonsterLoc.yPos){
        nextState = Battle;
        enemyEnountered = EnemyEncounter_SmallMonster;
    } 
}

/* Necessary DEBOUNCE_DELAY and prevButtonPressTime var to check against 
so inputs can't be retriggered until 100 ms have passed before the next input. */
#define DEBOUNCE_DELAY 100
u32 prevButtonPressTime = 0; 

/* Input handler used to handle the controller inputs during the exploration state. */
void handleInputExploration(){   
    // Creates a joypad state and assigns it to the 1st player controller port
    u16 joypad_state = JOY_readJoypad(JOY_1);
    // Gets the currentTime after the button is pressed
    u32 currButtonPressTime = getTick();
    /* Below conditions check which input is entered and if current frame
    is 100 ms longer than when the last button press was registered. */
    if ((joypad_state & BUTTON_UP) && (currButtonPressTime - prevButtonPressTime >= DEBOUNCE_DELAY)){       
        movePlayer(MovePlayer_Forward);
        // set the prev to curr. to check aginst future button presses
        prevButtonPressTime = currButtonPressTime;
    }
    if ((joypad_state & BUTTON_RIGHT) && (currButtonPressTime - prevButtonPressTime >= DEBOUNCE_DELAY)){
        movePlayer(MovePlayer_Right);
        prevButtonPressTime = currButtonPressTime;
    }
    if ((joypad_state & BUTTON_LEFT) && (currButtonPressTime - prevButtonPressTime >= DEBOUNCE_DELAY)){
        movePlayer(MovePlayer_Left);
        prevButtonPressTime = currButtonPressTime;
    }
    if ((joypad_state & BUTTON_DOWN) && (currButtonPressTime - prevButtonPressTime >= DEBOUNCE_DELAY)){
        movePlayer(MovePlayer_Down);
        prevButtonPressTime = currButtonPressTime;
    }
}

// /* For development purposes only! This displays the player's position as they move around the screen. */
// void updateScreen();
// void updateScreen(){
//     // chars necessary to convert integers to strings so SGDK can render them on the screen
//     // might possibly convert this into a helper function to prevent having to write this code each time
//     char playerCoords[40];
//     // sprintf is a built in method from SGDK 
//     // This takes the integers from the third arg and combines it with the 2nd arg to store it
//     // at the variable passed into the 1st arg. It operates in a similar way as printf, but is 
//     // designed specifically for integer to string conversion for SGDK
//     sprintf(playerCoords, "Player X: %d, Player Y: %d", JimaLoc.xPos, JimaLoc.yPos);
//     VDP_drawText(playerCoords, 5, 11);
// }

/* Looks for an input from the controller during the exploration state.
Each time the forward key is pressed the character moves in a direction which triggers 
additional states to see if there is an enemy or a world event is present. If either are 
present a new state is returned and the state is ended. */
void initExploration(stateMachine currentState) {
    JOY_init();
    JOY_setEventHandler(handleInputExploration);
    // init Sprite engine
    SPR_init();
    // set palette type for sprite, point to its data and declare transfer method
    PAL_setPalette(PAL2, animated_fighter.palette->data, DMA);
    // add the sprite to the screen
    fighter = SPR_addSprite(&animated_fighter, 100, 50, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    while (currentState == Exploration){
        JOY_update();
        handleInputExploration();
        // make sure to update the sprite for each loop
        SPR_update();
        enemyMovement();
        enemyCheck(JimaLoc.xPos, JimaLoc.yPos);
        // This breaks the initExploration while loop after an enemy is found
        if (nextState == Battle){
            currentState = Battle;
            break;
        }
        SYS_doVBlankProcess();
    }
}