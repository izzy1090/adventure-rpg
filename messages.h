#ifndef _MESSAGES_H
#define _MESSAGES_H

    #include "defines.h"

    // An empty node to store a queue entry - for message counter
    struct QNode {
        char *key;
        struct QNode* next; 
    };

    // Used in conjunction with the createQueue() function to create a call stack
    // and creates a place to point our front and rear nodes. Currently used
    // for the messages.
    struct Queue {
        struct QNode *front, *rear; 
    };

    int enQueue(struct Queue* q, char *k);
    void deQueue(struct Queue* q);
    void printOut (char *queuedMessages);
    void callStack(char *queuedMessages);

    // Prototypes declarations necessary for the terminal log UI, menus and messages
    void beginNCurses();
    void endNCurses();
    void clearAndMove(int row, int column);

    void displayStats(Entity *Target, int trigger);
    void battleMenu();
    char* hitOrMissMessages(int trigger);
    char* deadMessage(int trigger);
    char* deadAndQuitMessage(int trigger);
    char* movePlayerMessages(int trigger); 

#endif