#include "input.h"
#include "attack.h"
#include "entity.h"
#include "window.h"
#include "defines.h"
#include "maps.h"
#include "exploration.h"

/*=====================================================*
    
    To compile for use with unix use 
    "gcc -c file.c -o file.o" to generate output 
    files as 'file.o'. You can then bundle together all
    the 'file.o' along with the -ncurses flag to 
    compile.

*=====================================================*/

int main (void) {
    // Entity declarations will live somewhere else
    // the below is temporary for development purposes
    Entity *FlyingBanshee = newEntity(BEAST, "Flying Banshee");
    Entity *Hero = newEntity(WARRIOR, "Jima");
    FlyingBanshee->location = 10;
    matrix[0][2] = FlyingBanshee->location;
    matrix[0][0] = Hero->location;

    beginNCurses();
    
    while(1){
        refresh();

        if (gameState == Exploration){
            explorationState();
            clearAndMove(12, 12);
            gameState = Battle;
        } else if (gameState == Battle){
            clearAndMove(12, 12);
            mvprintw(10, 10, "You're now in the battle state.");
        }
    }
    endNCurses();
    return 0; 
}