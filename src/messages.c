#include "messages.h"

// Create an empty linked list container with available nodes to manipulated
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)MEM_alloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q; 
}

// Allocates memory for a new node that temporary holds a node being passed through the call stack.
struct QNode* newNode(char *key) {
    struct QNode* temp = (struct QNode*)MEM_alloc(sizeof(struct QNode));
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

// Function to print strings passed in to it. Potentially need to  
// integrate Entity* Target arg. so we can display characters names in strings.
void printOut (char *queuedMessages){
    char *messageToPrint = queuedMessages;
        // VDP_drawText("%s\n", messageToPrint, 4, 4);
}

// Pass your queued message into the call stack where it will push it to the call stack,
// print the message, and then deallocate the memory. 
void callStack(char *queuedMessages){
    char* queuedMessage = queuedMessages;
    struct Queue* q = createQueue();
    enQueue(q, queuedMessage);
    printOut(queuedMessage);
    deQueue(q);
}

// when trigger is passed a 1, then show stats
// else if trigger is passed a 0, don't show stats
void displayStats (Entity *Target, int trigger) {
    if (trigger == 1) {
        // VDP_drawText("\nName: %s\nHealth: %d\nMP: %d\n", Target->name, Target->stats.currenthp, Target->stats.currentmp, 10, 0); 
    } 
}

// Displays what available actions the player has to take.
void battleMenu() {
    VDP_drawText("\'e\' - to attack\n", 0,0);
    VDP_drawText("\'q\' - to quit\n", 1,0);
}

// Function to spit back hit or miss - use 1 for hit and 0 for miss
char* hitOrMissMessages(int trigger) {
    char *hit = "Hit!";  
    char *miss = "Miss!";
    if (trigger == 1){
        return hit; } 
    return miss;
}

// Function to display that the enemy is dead, returns a string, enter 1 to initiate
char* deadMessage(int trigger) {
    char *dead = ""; 
    if (trigger == 1){
        dead = "They're dead!";
        return dead;
    } return dead;
}

/* Displays a message after the user moves the hero forward, backward, left or right. 
Use the following triggers to trigger your message:

Moving forward= 1, Moving left= 2, Moving backwards= 3, and Moving right= 4 */
char* movePlayerMessage(int trigger){
    char *moveMessage = 0;
    if (trigger == 1){
        moveMessage = "The hero has moved forward.";
        return moveMessage;
    } else if (trigger == 2){
        moveMessage = "The hero has moved to the left.";
        return moveMessage;
    } else if (trigger == 3) {
        moveMessage = "The hero has moved backwards.";
        return moveMessage;
    } else if (trigger == 4) {
        moveMessage = "The hero has moved to the right.";
        return moveMessage;
    } return moveMessage;
}