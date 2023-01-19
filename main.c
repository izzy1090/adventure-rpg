#include "defines.h"

int main () {
    beginNcurses();
    while (1){
        refresh();
        mvprintw(10, 35, "Hello world!");
    }
    endNcurses();
    return 0;
}
