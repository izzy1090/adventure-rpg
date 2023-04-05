#include "exploration.h"

#define LEVEL_1_HEIGHT 800
#define LEVEL_1_WIDTH 800
#define SCREEN_HEIGHT 224
#define SCREEN_WIDTH 320

// Empty pointer for Sprite
Sprite* littleGuy = NULL;

Map gameLoop_exploration_loadLevel(){
    PAL_setPalette(PAL0, level_1_palette.data, DMA);

    u16 tile_index;
    tile_index = TILE_USER_INDEX;
    VDP_loadTileSet(&level_1_tileset, tile_index, DMA);
    tile_index += level_1_tileset.numTile;

    Map *map;
    map = MAP_create(&level_1_map, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USER_INDEX));

    MAP_scrollTo(map, 0, 0);

    return *map;
}

// /* Player and party locations to start. This starts off as static locations for a singular map. 
// This will need to scale as the project scales. */
Entity_Loc JimaLoc = {.xPos = 0, .yPos = 0, .move = 1};

// // Enemies on the map locations - we might want to consider giving certain enemy types the ability to move multiple squares
Entity_Loc SmallMonsterLoc = {.xPos = 3, .yPos = 2, .move = 1};

// /* This checks the player's location to see if it ever exceeds the boundaries of the current map. 
// The function can easily scale later on to include multiple maps. */
// void checkMapBounds_player(){
//     bool lowerMapBound = (JimaLoc.yPos + JimaLoc.move) < 0;
//     bool upperMapBound = (JimaLoc.yPos + JimaLoc.move) >= MAP_HEIGHT;
//     bool leftMapBound = (JimaLoc.xPos + JimaLoc.move)  < 0;
//     bool rightMapBound = (JimaLoc.xPos + JimaLoc.move) >= MAP_WIDTH;
    
//     if (upperMapBound) {        
//         JimaLoc.yPos = 0;
//     } else if (lowerMapBound){
//         JimaLoc.yPos = MAP_HEIGHT - 1;
//     } else if (leftMapBound){
//         JimaLoc.xPos = MAP_WIDTH - 1;
//     } else if (rightMapBound) {
//         JimaLoc.xPos = 0;
//     } 
// }

// /* This is currently a temporary way to handle the enemy path for a single enemy. When you invoke the function, 
// it creates a static variable with the same coordinates as the monster's location. This is then used to check against one 
// monster's location (the SmallMonster) to see where they are and move them around. This needs to scale to include 
// different enemies and to rely on the initial enemy location, rather than the need to create a static location 
// for each enemy on the map. */
// void enemyMovement(){
//     Entity_Loc refSmallMonsterLoc = {.xPos = 3, .yPos = 2, .move = 1};
//     bool initial = refSmallMonsterLoc.xPos == SmallMonsterLoc.xPos & refSmallMonsterLoc.yPos == SmallMonsterLoc.yPos;
//     bool firstMove = refSmallMonsterLoc.xPos + 1 == SmallMonsterLoc.xPos & refSmallMonsterLoc.yPos == SmallMonsterLoc.yPos;
//     bool secondMove = refSmallMonsterLoc.xPos + 1 == SmallMonsterLoc.xPos & refSmallMonsterLoc.yPos + 1 == SmallMonsterLoc.yPos;
//     bool completeLoop = 1;

//     if (initial){   
//         refSmallMonsterLoc.yPos += refSmallMonsterLoc.move;
//     } else if (firstMove){
//         refSmallMonsterLoc.xPos += refSmallMonsterLoc.move;   
//     } else if (secondMove){
//         refSmallMonsterLoc.xPos += -refSmallMonsterLoc.move;
//     } else if (firstMove && completeLoop){
//         refSmallMonsterLoc.move += -refSmallMonsterLoc.move;
//     }
//     SmallMonsterLoc.yPos = refSmallMonsterLoc.yPos;
//     SmallMonsterLoc.xPos = refSmallMonsterLoc.xPos;
// }

// /* Checks to see if the enemy and hero location match, if they do, 
// return the battle state. Will need to include other enemy locations in the future. */
// void enemyCheck(u16 heroXLoc, u16 heroYLoc){
//     if (heroXLoc == SmallMonsterLoc.xPos && heroYLoc == SmallMonsterLoc.yPos){
//         nextState = Battle;
//         enemyEnountered = EnemyEncounter_SmallMonster;
//     } 
// }

Entity_Loc SpriteLoc = {.xPos = 100, .yPos = 50, .move = 3, .walking = 0, .stop = 0};

void updateSpriteAnim(){
    if (SpriteLoc.stop){
        SPR_setAnimAndFrame(littleGuy, NULL, 0);
    } else SPR_setPosition(littleGuy, SpriteLoc.xPos, SpriteLoc.yPos);
}

/* Moves the player in the direction according to the passed-in state. movePlayer also 
checks if an enemy or world event is present. If either are, then a new state is returned. */
void moveSpriteLoc(stateMachine_Exploration_MovePlayer currentState){
    u32 currentTime = getTick();
    u32 frameTime = 25;
    u32 walkFrameIndex = (currentTime / frameTime) % 4;
    SpriteLoc.walking = 1;
    SpriteLoc.stop = 0;
    if (currentState == MovePlayer_Forward){ 
        SPR_setAnimAndFrame(littleGuy, ANIM_WALK_BACK, walkFrameIndex);
        SpriteLoc.yPos += -SpriteLoc.move;
    } if (currentState == MovePlayer_Right){
        SPR_setAnimAndFrame(littleGuy, ANIM_WALK_RIGHT, walkFrameIndex);
        SpriteLoc.xPos += SpriteLoc.move;
    } if (currentState == MovePlayer_Down){
        SPR_setAnimAndFrame(littleGuy, ANIM_WALK_FORWARD, walkFrameIndex);
        SpriteLoc.yPos += SpriteLoc.move;
    } if (currentState == MovePlayer_Left){
        SPR_setAnimAndFrame(littleGuy, ANIM_WALK_LEFT, walkFrameIndex);
        SpriteLoc.xPos += -SpriteLoc.move;
    } 
    // checkMapBounds_Player();
}

/* Necessary DEBOUNCE_DELAY and prevButtonPressTime var to check against 
so inputs can't be retriggered until 100 ms have passed before the next input. */
#define DEBOUNCE_DELAY 10
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
        moveSpriteLoc(MovePlayer_Forward);
        // set the prev to curr. to check aginst future button presses
        prevButtonPressTime = currButtonPressTime;
    }
    if ((joypad_state & BUTTON_RIGHT) && (currButtonPressTime - prevButtonPressTime >= DEBOUNCE_DELAY)){
        moveSpriteLoc(MovePlayer_Right);
        prevButtonPressTime = currButtonPressTime;
    }
    if ((joypad_state & BUTTON_LEFT) && (currButtonPressTime - prevButtonPressTime >= DEBOUNCE_DELAY)){
        moveSpriteLoc(MovePlayer_Left);
        prevButtonPressTime = currButtonPressTime;
    }
    if ((joypad_state & BUTTON_DOWN) && (currButtonPressTime - prevButtonPressTime >= DEBOUNCE_DELAY)){
        moveSpriteLoc(MovePlayer_Down);
        prevButtonPressTime = currButtonPressTime;
    }
}

void checkPlayerLocation () {
    s16 lastLocX = SPR_getPositionX(littleGuy);
    s16 lastLocY = SPR_getPositionY(littleGuy);

    if (SpriteLoc.xPos == lastLocX && SpriteLoc.yPos == lastLocY){
        SpriteLoc.stop = 1;
        SpriteLoc.walking = 0;
    }
}

/* Looks for an input from the controller during the exploration state.
Each time the forward key is pressed the character moves in a direction which triggers 
additional states to see if there is an enemy or a world event is present. If either are 
present a new state is returned and the state is ended. */
void initExploration(stateMachine currentState) {
    Map map = gameLoop_exploration_loadLevel();
    JOY_init();
    JOY_setEventHandler(handleInputExploration);
    // init Sprite engine
    SPR_init();
    // set palette type for sprite, point to its data and declare transfer method
    PAL_setPalette(PAL2, small_guy.palette->data, DMA);
    // add the sprite to the screen
    littleGuy = SPR_addSprite(&small_guy, 100, 50, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    while (currentState == Exploration){
        checkPlayerLocation();
        updateSpriteAnim();
        JOY_update();
        handleInputExploration();
        SPR_update();
        // make sure to update the sprite and screen for each loop
        SYS_doVBlankProcess();
        
        // This breaks the initExploration while loop after an enemy is found
        if (nextState == Battle){
            currentState = Battle;
            break;
        }
    }
}