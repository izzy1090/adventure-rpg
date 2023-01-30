#include "input.h"
#include "attack.h"
#include "entity.h"
#include "window.h"
#include "defines.h"
#include "maps.h"

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

stateMachine gameState = Exploration;
bool stateInitialize = TRUE;



int main (void) {

    Entity *FlyingBanshee = newEntity(BEAST, "Flying Banshee");
    Entity *Hero = newEntity(WARRIOR, "Jima");
    FlyingBanshee->location = 10;
    matrix[0][2] = FlyingBanshee->location;

    int x;
    beginNCurses();
    
    while(x != 1){
        refresh();
        if (gameState == Exploration){
            mvprintw(10, 10, "Monster's Name: %s", FlyingBanshee->name);
            mvprintw(11, 10, "Monster location value: [%d]", FlyingBanshee->location);
        }
    }
    endNCurses();
    return 0; 
}