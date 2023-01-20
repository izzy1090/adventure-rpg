#include "defines.h"
#include "attack.h"

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

// A node to store a queue entry - for message counter
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

// A utility function to create an empty call stack
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q; 
}

int enQueue(struct Queue* q, char *k);
void deQueue(struct Queue* q);

int main (void) {
    beginNCurses();

    // Global Declarations
    Entity *Hero = newEntity(WARRIOR, "Jima");
    Entity *Villain = newEntity(RANGER, "Small Monster");

    int ch;

    bool hitMissVar;
    int damageVar;
    float hitPercentageFloat; 
    char *queuedMessage = NULL;
    struct Queue* q = createQueue();

    displayMenu();
    refresh();
        // prompts player to press 'q' to quit the program
        while ( ch != 'q'){            
            ch = gameController();
            hitPercentageFloat = hitCalc(Hero, Villain);
            hitMissVar = hitMiss(Hero, Villain, hitPercentageFloat);
            if (hitMissVar) {
                damageVar = damageCalc(Hero, Villain);
                damageDealt(Villain, damageVar);

                queuedMessage = hitOrMissMessages(1);
                enQueue(q, queuedMessage);
                displayStats(Villain, 1);
                if (areTheyDead(Villain)) {
                    queuedMessage = deadMessage(1);
                    displayStats(Villain, 0);
                    enQueue(q, queuedMessage); 
                    }
                }
                else if (areTheyDead(Villain) && Villain->stats.currenthp <= 0 ){
                    queuedMessage = deadAndQuitMessage(1);
                    enQueue(q, queuedMessage);
                }
            else {
                hitMissVar = false; 
                queuedMessage = hitOrMissMessages(0); 
                enQueue(q, queuedMessage);
                }

            printOut(queuedMessage);
            deQueue(q);
        }
    endNCurses();
    return 0; 
}

// Allocates memory for a new node that temporary holds a node being passed through the call stack.
    struct QNode* newNode(char *key) {
        struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
        temp->key = key; 
        temp->next = NULL;
        return temp; 
}

// Allocates memory for a new node and inserts it to the front of the call stack.
int enQueue(struct Queue* q, char *key) {
    // Create a new LL node
    struct QNode* temp = newNode(key);

    // If queue is empty, then new node is moved to the head,
    // because it's empty the tail and head are the same.
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return 1;
    }

    // otherwise add a new node to the back and point the tail to null.
    q->rear->next = temp;
    q->rear = temp;
    return 1;
}

// Deallocates memory required for the current node in the call stack.
void deQueue(struct Queue* q) {
    // If queue is empty, return NULL.
    if (q->front == NULL){
        return; }

    // Store previous front and move front one node ahead
    struct QNode* temp = q->front;

    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL){
        q->rear = NULL;
    free(temp); } 
}