#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>

/*==============================================*

        Here lies the function prototypes. 
        These should go in the ".h" files. 

*==============================================*/

// A linked list (LL) node to store a queue entry - for message counter
struct QNode {
    char *key;
    struct QNode* next; 
};
 
// The queue, front stores the front node of LL and rear
// stores the last node of LL - for message counter
struct Queue {
    struct QNode *front, *rear; 
};
 
// A utility function to create a new linked list node - specifically for message counter
struct QNode* newNode(char *k) {
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
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

// Class for stats
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

// Classes are enumerated. Warrior = 0; Ranger = 1; etc. 
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

/*==============================================*

        Here lies the function prototypes. 
        These should go in the ".h" files. 

*==============================================*/

void displayStats(Entity *Target, int trigger);
void setName(Entity *Target, char name[50]);
Entity* newEntity(class class, char name[50]);
void displayMenu();
int system_DiceRoll(int maximum, int minimum, int add_to_roll, int subtract_from_roll);
void clearAndMove(int row, int column);
void beginNcurses();
void endNcurses();
bool hitMiss(Entity *Attacker, Entity *Target, float hitPercentage);
float hitCalc(Entity *Attacker, Entity *Target);
int damageCalc(Entity *Attacker, Entity *Target); 
int damageDealt(Entity *Target, int damage);
int classBonus(Entity *Attacker, Entity *Target, int class);
int criticalHit(Entity *Attacker, Entity *Target);
bool areTheyDead(Entity *Target);
int gameController();
void printOut (char *queuedMessages);
char* hitOrMissMessages(int trigger);
char* deadMessage(int trigger);
char* deadAndQuitMessage(int trigger);
int enQueue(struct Queue* q, char *k);
void deQueue(struct Queue* q);

/*===================================================*

    Here lies the function declarations are below.
    These all are going to go in the ".c" files

*===================================================*/

// Creates player and sets class to establish what stats they have access to
Entity* newEntity(class class, char name[50]) {
// allocate memory to player pointers.
Entity *tempEntity = malloc(sizeof(Entity));
setName(tempEntity, name);

// Assign stats based on the given class. 
switch(class){
    case WARRIOR:
        tempEntity->characterStats.currenthp = 60;
        tempEntity->characterStats.currentmp = 0;
        tempEntity->characterStats.max_hp = 100;
        tempEntity->characterStats.max_mp = 100;
        tempEntity->characterStats.physical_armor = 10;
        tempEntity->characterStats.magic_armor = 7;
        tempEntity->characterStats.strength = 15;
        tempEntity->characterStats.dexterity = 10;
        tempEntity->characterStats.wisdom = 3;
        tempEntity->characterStats.intelligence = 3;
        tempEntity->characterStats.luck = 5;
        tempEntity->class = WARRIOR;
        break;
    case RANGER:
        tempEntity->characterStats.currenthp = 35;
        tempEntity->characterStats.currentmp = 0;
        tempEntity->characterStats.max_hp = 100;
        tempEntity->characterStats.max_mp = 100;
        tempEntity->characterStats.physical_armor = 10;
        tempEntity->characterStats.magic_armor = 8;
        tempEntity->characterStats.strength = 7;
        tempEntity->characterStats.dexterity = 5;
        tempEntity->characterStats.wisdom = 5;
        tempEntity->characterStats.intelligence = 3;
        tempEntity->characterStats.luck = 5;
        tempEntity->class = RANGER;
        break;
    case MAGE:
        tempEntity->characterStats.currenthp = 20;
        tempEntity->characterStats.currentmp = 60;
        tempEntity->characterStats.max_hp = 100;
        tempEntity->characterStats.max_mp = 100;
        tempEntity->characterStats.physical_armor = 4;
        tempEntity->characterStats.magic_armor = 11;
        tempEntity->characterStats.strength = 3;
        tempEntity->characterStats.dexterity = 7;
        tempEntity->characterStats.wisdom = 10;
        tempEntity->characterStats.intelligence = 15;
        tempEntity->characterStats.luck = 7;
        tempEntity->class = MAGE;
        break;
    case GOD_NERD:
        tempEntity->characterStats.currenthp = 100;
        tempEntity->characterStats.currentmp = 100;
        tempEntity->characterStats.max_hp = 100;
        tempEntity->characterStats.max_mp = 100;
        tempEntity->characterStats.physical_armor = 100;
        tempEntity->characterStats.magic_armor = 100;
        tempEntity->characterStats.strength = 100;
        tempEntity->characterStats.dexterity = 100;
        tempEntity->characterStats.wisdom = 100;
        tempEntity->characterStats.intelligence = 100;
        tempEntity->characterStats.luck = 100;
        tempEntity->class = GOD_NERD;
   default:
        tempEntity->characterStats.max_hp = 100;
        tempEntity->characterStats.max_mp = 100;
        break;
    }
    return(tempEntity);     // return memory address of player.
}

// when trigger is passed a 1, then show stats
    // else if trigger is passed a 0, don't show stats
void displayStats (Entity *Target, int trigger) {
    if (trigger == 1) {
        clearAndMove(10, 0);
        clearAndMove(11, 0);
        clearAndMove(12, 0);
        mvprintw(10,0,"\nName: %s\nHealth: %d\nMP: %d\n", Target->name, Target->characterStats.currenthp, Target->characterStats.currentmp); 
    } else if (trigger == 0) {
        clearAndMove(10, 0);
        clearAndMove(11, 0);
        clearAndMove(12, 0);
        clearAndMove(13, 0);
    } 
}

void setName(Entity *Target, char name[50]) {
    strcpy(Target->name, name);
    return; 
}

void displayMenu() {
    mvprintw(0,0,"\'e\' - to attack\n");
    mvprintw(1,0,"\'q\' - to quit\n");
    clearAndMove(3, 0);
    return; 
}

// Dice roll function to determine probabilities. Helpful for hitPercentage, damageCalc, etc.
int system_DiceRoll(int maximum, int minimum, int add_to_roll, int subtract_from_roll) {
    int dice_roll = random() % (maximum - minimum + 1) + minimum;
    int adjusted_roll = dice_roll + add_to_roll - subtract_from_roll;
    bool debug_showDiceRolls;
    if (adjusted_roll > maximum) {
        adjusted_roll = maximum; 
    }
    else if (adjusted_roll < minimum) {
        adjusted_roll = minimum; 
    }
    return adjusted_roll; 
}

// Function to begin nCurses, exit noEcho mode and initialize srand
void beginNcurses() {
    initscr();                   // Start curses mode
    noecho();
    srand(time(0));              // Set the seed for rand to 0
}

// Function to end nCurses
void endNcurses() {
    endwin();            // End curses mode 
}

// Function to clear and display messages using nCurses print function 
void clearAndMove(int row, int column) {
    clrtoeol();
    move(row, column);
}

// function to calculate how likely it is for an Attacker to hit an enemy
float hitCalc(Entity *Attacker, Entity *Target) {
    float hitPercentage = (Attacker->characterStats.dexterity) * (system_DiceRoll(6, 1, Attacker->characterStats.luck, Target->characterStats.dexterity));
    return hitPercentage;
}

// Function to check if a hit was made or not. Will also queue up messages
bool hitMiss(Entity *Attacker, Entity *Target, float hitPercentage) {    
    bool trueFalse;
    if ( hitPercentage >= 43.33 ) {
        trueFalse = true;
        return trueFalse; 
    }
    else {
        trueFalse = false;
        return trueFalse; 
    }   
}

// Function to calculate how much damage an attacker is doing
int damageCalc(Entity *Attacker, Entity *Target) {
    int damage = (Attacker->characterStats.strength) * system_DiceRoll(6, 1, Attacker->characterStats.luck, Target->characterStats.physical_armor);
    return damage;
}

// Function to calculate how much damage is dealt
int damageDealt(Entity *Target, int damage) {
    Target->characterStats.currenthp = Target->characterStats.currenthp - damage;
    return Target->characterStats.currenthp;
}

// Function to declare the class bonus
int classBonus (Entity *Attacker, Entity *Target, int class ) {
    int classDamage;
    if (class == WARRIOR ){
        classDamage = 5; }
    else if (class == RANGER){
        classDamage = 3; }
    else if (class == MAGE){
        classDamage = 3; }
    return classDamage; 
}

// Function to test if the target (character being attacked) is dead or not
// returns a bool to determine death
bool areTheyDead(Entity *Target) {
    bool deadStatus;
    if (Target->characterStats.currenthp <= 0) {
        deadStatus = true;
    } else {
        deadStatus = false;
    } return deadStatus; 
}

// Function to display that the enemy is dead, returns a string, enter 1 to initiate
char* deadMessage(int trigger) {
    char *dead = ""; 
    if (trigger == 1){
        dead = "They're dead!";
        return dead;
    } return dead;
}

// function to display message that the villain is dead and it's time to quit the program
char* deadAndQuitMessage(int trigger){
    char *timeToQuit = "";
    if (trigger == 1){
        timeToQuit = "Okay, they're dead! Stop beating a dead horse and press 'q' to quit please!";
        return timeToQuit;
    } return timeToQuit;
}

// Function to spit back hit or miss - use 1 for hit and 0 for miss
char* hitOrMissMessages(int trigger) {
    char *hit = "Hit!";  
    char *miss = "Miss!";
    if (trigger == 1){
        return hit; } 
    return miss;
}

// Function to print strings passed to it. Potentially need to incorporate a Entity* Target arg. so we can
// display characters names in strings
void printOut (char *queuedMessages){
    char *messageToPrint = queuedMessages;
        clearAndMove(0, 10);
        mvprintw(4, 4, "%s\n", messageToPrint);
}
 
// The function to add a key k to q
int enQueue(struct Queue* q, char *k) {
    // Create a new LL node
    struct QNode* temp = newNode(k);
 
    // If queue is empty, then new node is front and rear
    // both
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return 1;
    }
 
    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
    return 1;
}

// Function to remove a key from given queue q
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

// gameController function, much of the code below is tentative.
int gameController() {
    int ch;
    keypad(stdscr, TRUE);        // This allows keypad input
    while((ch = getch()) != KEY_ENTER){
        switch(ch){   
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;
            case KEY_DOWN:
                break;
            case KEY_UP:
                break;
            case 97: //a
                break;
            case 115: //s
                break;
            case 100: //d
                break;
            case 119: //w
                break;
            case 113: //q
                return (ch);
            case 101: //e
                return (ch);
            default:
                break;
        }
    } 
    return (ch); 
}