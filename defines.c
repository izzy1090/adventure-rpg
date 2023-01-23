#include "defines.h"

/*==================================================*

            Character function declarations.

*==================================================*/

Entity* newEntity(Entity_Class class, char name[50]);
void setName(Entity *Target, char name[50]);

// Creates player and sets class to establish what stats they have.
Entity* newEntity(Entity_Class class, char name[50]) {
// allocate memory to player pointers.
Entity *tempEntity = malloc(sizeof(Entity));
setName(tempEntity, name);

// Assign stats based on the given class. 
switch(class){
    case WARRIOR:
        tempEntity->stats.currenthp = 60;
        tempEntity->stats.currentmp = 0;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        tempEntity->stats.physical_armor = 10;
        tempEntity->stats.magic_armor = 7;
        tempEntity->stats.strength = 15;
        tempEntity->stats.dexterity = 10;
        tempEntity->stats.wisdom = 3;
        tempEntity->stats.intelligence = 3;
        tempEntity->stats.luck = 5;
        tempEntity->class = WARRIOR;
        break;
    case RANGER:
        tempEntity->stats.currenthp = 35;
        tempEntity->stats.currentmp = 0;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        tempEntity->stats.physical_armor = 10;
        tempEntity->stats.magic_armor = 8;
        tempEntity->stats.strength = 7;
        tempEntity->stats.dexterity = 5;
        tempEntity->stats.wisdom = 5;
        tempEntity->stats.intelligence = 3;
        tempEntity->stats.luck = 5;
        tempEntity->class = RANGER;
        break;
    case MAGE:
        tempEntity->stats.currenthp = 20;
        tempEntity->stats.currentmp = 60;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        tempEntity->stats.physical_armor = 4;
        tempEntity->stats.magic_armor = 11;
        tempEntity->stats.strength = 3;
        tempEntity->stats.dexterity = 7;
        tempEntity->stats.wisdom = 10;
        tempEntity->stats.intelligence = 15;
        tempEntity->stats.luck = 7;
        tempEntity->class = MAGE;
        break;
    case GOD_NERD:
        tempEntity->stats.currenthp = 100;
        tempEntity->stats.currentmp = 100;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        tempEntity->stats.physical_armor = 100;
        tempEntity->stats.magic_armor = 100;
        tempEntity->stats.strength = 100;
        tempEntity->stats.dexterity = 100;
        tempEntity->stats.wisdom = 100;
        tempEntity->stats.intelligence = 100;
        tempEntity->stats.luck = 100;
        tempEntity->class = GOD_NERD;
default:
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        break;
    }
    return(tempEntity);     // return memory address of player.
}

// setName creates the name for our entity. Currently this function leaks memory   
// due to strcpy which is not stable, however when the game transitions over to  
// SGDK a different built-in function will be used. 
void setName(Entity *Target, char name[50]) {
    strcpy(Target->name, name);
    return; 
}

/*==================================================*

        Function declarations required 
        for the UI.

*==================================================*/

// Begins nCurses mode as well as enables noecho mode and sets seed to 0 for random
void beginNCurses() {
    initscr();                   // Start curses mode
    noecho();
    srand(time(0));              // Set the seed for rand to 0
}

// Ends nCurses mode
void endNCurses() {
    endwin();            // End curses mode 
}

// Clears the window and moves the cursor
void clearAndMove(int row, int column) {
    clrtoeol();
    move(row, column);
}