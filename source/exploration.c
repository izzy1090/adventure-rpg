#include "exploration.h"

int map[4][4] = { 
    {0, 1, 2, 3}, 
    {10, 11, 12, 13}, 
    {20, 21, 22, 23}, 
    {30, 31, 32, 33}
};

int row = 0;
int col = 0;

void initializeExploration() {
    gameState = Exploration;

    Entity *Jima = playerEntities(1);
    Jima->location = map[row][col];

    // Enemies
    Entity *SmallMonster = enemyEntities(1);
    Entity *FlyingBanshee = enemyEntities(2);
    SmallMonster->location = map[row][col+=3];
    FlyingBanshee->location = map[row+=1][col];
    
    int ch;
    char *queuedMessage = NULL;
    while (gameState == Exploration){
        ch = input();
        if (ch == KEY_UP){
                queuedMessage = movePlayerMessage(1);
                Jima->location = map[row++][col];
                mvprintw(10, 10, "This is Jima's location: %d", Jima->location);
                SmallMonster->location = map[row][col--];
                mvprintw(11, 10, "This is the monster's location: %d", SmallMonster->location);
                FlyingBanshee->location = map[row--][col];
                mvprintw(12, 10, "This is the monster's location: %d", FlyingBanshee->location);
                callStack(queuedMessage);  
        } 
        else if (ch == KEY_RIGHT){
                queuedMessage = movePlayerMessage(2);
                Jima->location = map[row][col++];
                mvprintw(10, 10, "This is Jima's location: %d", Jima->location);
                SmallMonster->location = map[row--][col--];
                mvprintw(11, 10, "This is the monster's location: %d", SmallMonster->location);
                mvprintw(12, 10, "This is the monster's location: %d", FlyingBanshee->location);
                callStack(queuedMessage);
        } 
        else if (ch == KEY_DOWN){
            queuedMessage = movePlayerMessage(3);
            Jima->location = map[row--][col];
            mvprintw(10, 10, "This is Jima's location: %d", Jima->location);
            SmallMonster->location = map[row++][col--];
            mvprintw(11, 10, "This is the monster's location: %d", SmallMonster->location);
            callStack(queuedMessage);
        } 
        else if (ch == KEY_LEFT){
            queuedMessage = movePlayerMessage(4);
            Jima->location = map[row][col--];
            mvprintw(10, 10, "This is Jima's location: %d", Jima->location);
            SmallMonster->location = map[row++][col++];
            mvprintw(11, 10, "This is the monster's location: %d", SmallMonster->location);
            callStack(queuedMessage);
        } 
        else if (ch == 'q'){
            gameState = Battle;
        }
    }
}