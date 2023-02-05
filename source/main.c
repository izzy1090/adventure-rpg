#include "defines.h"
#include "input.h"
#include "battle.h"
#include "entity.h"
#include "window.h"
#include "exploration.h"

/*=====================================================*
    
    To compile for use with unix use 
    "gcc -c file.c -o file.o" to generate output 
    files as 'file.o'. You can then bundle together all
    the 'file.o' along with the -ncurses flag to 
    compile.

*=====================================================*/

int main (void) {
    beginNCurses();
    while (1){
        if (gameState == Exploration){
            initializeExploration();
        } 
        if (gameState == Battle){
            initializeBattle();
        } 
    }
    endNCurses();
    return 0; 
}