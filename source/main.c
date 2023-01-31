#include "input.h"
#include "attack.h"
#include "entity.h"
#include "window.h"
#include "defines.h"
#include "maps.h"
#include "exploration.h"

/*=====================================================*

    Currently the main block has declarations 
    and prototypes for the call stack. Everything 
    else lives in the attack and defines headers. 
    
    To compile for use with unix use 
    "gcc -c file.c -o file.o" to generate output 
    files as 'file.o'. You can then bundle together all
    the 'file.o' along with the -ncurses flag to 
    compile.

*=====================================================*/

int main (void) {

    Entity *FlyingBanshee = newEntity(BEAST, "Flying Banshee");
    Entity *Hero = newEntity(WARRIOR, "Jima");
    FlyingBanshee->location = 10;
    matrix[0][2] = FlyingBanshee->location;

    int ch;
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
        
            // mvprintw(10, 10, "Monster's Name: %s", FlyingBanshee->name);
            // mvprintw(11, 10, "Monster location value: [%d]", FlyingBanshee->location);
        
    }
    endNCurses();
    return 0; 
}