#include "exploration.h"

void movePlayerLoop() {
    int ch;
    char *queuedMessage = NULL;
    while (1){
        ch = gameController();
        if (ch == KEY_UP){
            queuedMessage = movePlayerMessages(1);
            callStack(queuedMessage);
        } else if (ch == KEY_RIGHT){
            queuedMessage = movePlayerMessages(2);
            callStack(queuedMessage);
        } else if (ch == KEY_DOWN){
            queuedMessage = movePlayerMessages(3);
            callStack(queuedMessage);
        } else if (ch == KEY_LEFT){
            queuedMessage = movePlayerMessages(4);
            callStack(queuedMessage);
        } 
    }
}