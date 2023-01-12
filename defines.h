#ifndef _DEFINES_
#define _DEFINES_
#include <stdlib.h>

// Used to create a node with a pointer for the 'key' and another for the 'next'
struct QNode {
    char *key;
    struct QNode* next; 
};
 
// Struct to store the pointers for the 'front' and 'rear' nodes of the call stack
struct Queue {
    struct QNode *front, *rear; 
};
 
// A utility function to create new nodes
struct QNode* newNode(char *k) {
    // allocate memory for the node
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    // then point the newly created node to the next key
        // and set the next node to null 
    temp->key = k; 
    temp->next = NULL;
    return temp; 
}
 
// A utility function to create an empty queue stack 
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q; 
}

// struct to store the stats used when creating new entities
typedef struct {
    int currenthp;
    int max_hp;
    int currentmp;
    int max_mp;
    int level;
    int physical_armor;
    int magic_armor;
    int strength;
    int dexterity;
    int wisdom;
    int intelligence;
    int luck;
} Entity_Stats;

// Available classes  
typedef enum ClassEnum {
    WARRIOR,
    RANGER,
    MAGE,
    GOD_NERD,
} class;

// struct for creating new character stats
typedef struct {
    Entity_Stats characterStats;
    class class;
    char name[20];
    char characterBio[50];
    char combat_menu_options;
} Entity;

#endif