#include "exploration.h"

int map[4][4] = { 
    {0, 1, 2, 3}, 
    {10, 11, 12, 13}, 
    {20, 21, 22, 23}, 
    {30, 31, 32, 33}
};

int row = 0;
int col = 0;

stateMachine initExploration(stateMachine currentState) {
    Entity *Jima = playerEntities(1);
    Jima->location = map[row][col];

    // Enemies
    Entity *SmallMonster = enemyEntities(1);
    Entity *FlyingBanshee = enemyEntities(2);
    Entity *Goblin = enemyEntities(3);
    SmallMonster->location = map[2][1];
    FlyingBanshee->location = map[3][0];
    Goblin->location = map[0][3];
    
    int ch;
    char *queuedMessage = NULL;
    while (currentState == Exploration){
        ch = input();
        if (ch == KEY_UP){
                queuedMessage = movePlayerMessage(1);
                Jima->location = map[row++][col];
                mvprintw(10, 10, "This is Jima's location: %d", Jima->location);
                mvprintw(11, 10, "This is the monster's location: %d", SmallMonster->location);
                mvprintw(12, 10, "This is the Flying Banshee's location: %d", FlyingBanshee->location);
                mvprintw(13, 10, "This is the Goblin's location: %d", Goblin->location);
                callStack(queuedMessage);  
        } 
        if (ch == KEY_RIGHT){
                queuedMessage = movePlayerMessage(2);
                Jima->location = map[row][col++];
                mvprintw(10, 10, "This is Jima's location: %d", Jima->location);
                mvprintw(11, 10, "This is the monster's location: %d", SmallMonster->location);
                mvprintw(12, 10, "This is the Flying Banshee's location: %d", FlyingBanshee->location);
                mvprintw(13, 10, "This is the Goblin's location: %d", Goblin->location);
                callStack(queuedMessage);
        } 
        if (ch == KEY_DOWN){
            queuedMessage = movePlayerMessage(3);
            Jima->location = map[row--][col];
            mvprintw(10, 10, "This is Jima's location: %d", Jima->location);
            mvprintw(11, 10, "This is the monster's location: %d", SmallMonster->location);
            mvprintw(12, 10, "This is the Flying Banshee's location: %d", FlyingBanshee->location);
            mvprintw(13, 10, "This is the Goblin's location: %d", Goblin->location);
            callStack(queuedMessage);
        } 
        if (ch == KEY_LEFT){
            queuedMessage = movePlayerMessage(4);
            Jima->location = map[row][col--];
            mvprintw(10, 10, "This is Jima's location: %d", Jima->location);
            mvprintw(11, 10, "This is the monster's location: %d", SmallMonster->location);
            mvprintw(12, 10, "This is the Flying Banshee's location: %d", FlyingBanshee->location);
            mvprintw(13, 10, "This is the Goblin's location: %d", Goblin->location);
            callStack(queuedMessage);
        } 
        if (FlyingBanshee->location == Jima->location || SmallMonster->location == Jima->location || Jima->location == Goblin->location){
            currentState = Battle;
        }
    }
    return currentState;
}