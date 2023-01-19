#include "test.h"
#include "time.h"

// tester function to see if invocations work
void helloWorld(){
    printf("Hello world!");
}

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
    // srand(time(0));              // Set the seed for rand to 0
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