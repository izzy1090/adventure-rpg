#include "window.h"

// Begins nCurses mode as well as enables noecho mode and sets seed to 0 for random
void beginNCurses() {
    initscr();                   // Start curses mode
    noecho();
    srand(time(0));              // Set the seed for rand to 0
}

// Ends nCurses mode
void endNCurses() {
    endwin();                   // End curses mode 
}

// Clears the window and moves the cursor
void clearAndMove(int row, int column) {
    clrtoeol();
    move(row, column);
}