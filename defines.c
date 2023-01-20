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
        for UI.

*==================================================*/

// Displays what available actions the player has to take.
void displayMenu() {
    mvprintw(0,0,"\'e\' - to attack\n");
    mvprintw(1,0,"\'q\' - to quit\n");
    clearAndMove(3, 0);
    return; 
}

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

// Function to print strings passed in to it. Potentially need to  
// integrate Entity* Target arg. so we can display characters names in strings.
void printOut (char *queuedMessages){
    char *messageToPrint = queuedMessages;
        clearAndMove(0, 10);
        mvprintw(4, 4, "%s\n", messageToPrint);
}



/*==================================================*

        Misc. function declarations

*==================================================*/


// Function to display that the enemy is dead, returns a string, enter 1 to initiate
char* deadMessage(int trigger) {
    char *dead = ""; 
    if (trigger == 1){
        dead = "They're dead!";
        return dead;
    } return dead;
}

// function to display message that the villain is dead and it's time to quit the program
char* deadAndQuitMessage(int trigger){
    char *timeToQuit = "";
    if (trigger == 1){
        timeToQuit = "Okay, they're dead! Stop beating a dead horse and press 'q' to quit please!";
        return timeToQuit;
    } return timeToQuit;
}

// gameController function, much of the code below is tentative.
int gameController() {
    int ch;
    keypad(stdscr, TRUE);        // This allows keypad input
    while((ch = getch()) != KEY_ENTER){
        switch(ch){   
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;
            case KEY_DOWN:
                break;
            case KEY_UP:
                break;
            case 97: //a
                break;
            case 115: //s
                break;
            case 100: //d
                break;
            case 119: //w
                break;
            case 113: //q
                return (ch);
            case 101: //e
                return (ch);
            default:
                break;
        }
    } 
    return (ch); 
}