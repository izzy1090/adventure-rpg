#include "exploration.h"

int map[4][4] = { 
    {0, 1, 2, 3}, {10, 11, 12, 13}, {20, 21, 22, 23}, {30, 31, 32, 33}
};

void explorationState() {
    Entity *Hero = newEntity(WARRIOR, "Jima");
    
    Hero->location = map[row][col];

    int ch;
    char *queuedMessage = NULL;
    while (gameState == Exploration){
        ch = input();
        if (ch == KEY_UP){
            queuedMessage = movePlayerMessages(1);
            Hero->location = map[row+=1][col];
            mvprintw(10, 10, "%d", Hero->location);
            callStack(queuedMessage);
        } else if (ch == KEY_RIGHT){
            queuedMessage = movePlayerMessages(2);
            Hero->location = map[row][col+=1];
            mvprintw(10, 10, "%d", Hero->location);
            callStack(queuedMessage);
        } else if (ch == KEY_DOWN){
            queuedMessage = movePlayerMessages(3);
            if (Hero->location == map[0][0]){
                mvprintw(10, 10, "%d", Hero->location);
                return;
            } else {
                Hero->location = map[row-=1][col];
                mvprintw(10, 10, "%d", Hero->location);
                callStack(queuedMessage);
            }
        } else if (ch == KEY_LEFT){
            queuedMessage = movePlayerMessages(4);
            if (Hero->location == map[0][0]){
                mvprintw(10, 10, "%d", Hero->location);
                return;
            } else {
                Hero->location = map[row][col-=1];
                mvprintw(10, 10, "%d", Hero->location);
                callStack(queuedMessage);
            }
        } else if (ch == 'q'){
            clearAndMove(11, 11);
            gameState = Battle;
        }
    }
}