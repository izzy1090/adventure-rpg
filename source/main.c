#include "input.h"
#include "exploration.h"
#include "attack.h"
#include "entity.h"
#include "window.h"

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
    beginNCurses();
    refresh();
    while(1){
        if (gameState == Exploration){
            
        }
    }
    endNCurses();
    return 0; 
}