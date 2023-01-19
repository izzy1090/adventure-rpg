#include <stdlib.h>
#include <string.h>
// #include <stdbool.h>
#include <time.h>
#include <ncurses.h>

/*==================================================*

    Here lies all of  State Machine declarations

*==================================================*/

// Papa state machine: where all the big state machine containers live!
typedef enum { Exploration, Battle, Attack, GameOver } stateMachine;

typedef enum { Exploration_MovePlayer, Exploration_EnemyPatrol } stateMachine_Exploration;
typedef enum { MovePlayer_Forward, MovePlayer_Left, MovePlayer_Right, MovePlayer_Down } stateMachine_Exploration_MovePlayer;
typedef enum { EnemyPatrol_Scan, EnemyPatrol_Fight } stateMachine_Exploration_EnemyPatrol;
// These are just potential options for the game. We don't necessarily need to program all of these right now.
typedef enum { Menu_Attack, Menu_Magic, Menu_Defend, Menu_Items, Menu_Escape } stateMachine_Battle;
typedef enum { Attack_HitCheck, Attack_DamageCalc, Attack_KillCheck } stateMachine_Attack;
typedef enum { Attack_KillCheck_Loot} stateMachine_Attack_KillCheck;
typedef enum { GameOver_Win, GameOver_Lose } stateMachine_GameOver;
typedef enum { GameOver_WinCredits } stateMachine_GameOver_Win;
typedef enum { GameOver_LoseCredits } stateMachine_GameOver_Lose;

/*==================================================*

        The below is for the event call stack! 
        It's a linked list used to cycle out 
        messages and possibly actions too.

*==================================================*/

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

/*==================================================*

    Function prototypes and declarations required 
    for event call stack and UI.

*==================================================*/

void displayMenu();
void beginNCurses();
void endNCurses();
void clearAndMove(int row, int column);
void printOut (char *queuedMessages);
int enQueue(struct Queue* q, char *k);
void deQueue(struct Queue* q);

// Displays what available actions the player has to take.
void displayMenu() {
    mvprintw(0,0,"\'e\' - to attack\n");
    mvprintw(1,0,"\'q\' - to quit\n");
    clearAndMove(3, 0);
    return; 
}

// Begins nCurses mode as well as enables noecho mode and sets seed to 0 for random
void beginNCurses() {
    initscr();                   // Start curses mode
    noecho();
    srand(time(0));              // Set the seed for rand to 0
}

// Ends nCurses mode
void endNCurses() {
    endwin();            // End curses mode 
}

// Clears the window and moves the cursor
void clearAndMove(int row, int column) {
    clrtoeol();
    move(row, column);
}

// Allocates memory for a new node that temporary holds a node being passed through the call stack.
struct QNode* newNode(char *key) {
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->key = key; 
    temp->next = NULL;
    return temp; 
}
 
// A utility function to create an empty call stack
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q; 
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
        clearAndMove(0, 10);
        mvprintw(4, 4, "%s\n", messageToPrint);
}

/*==================================================*

        Below is everything needed for the 
        character creation and stat management.
        I might use a different way of organizing 
        compartmentalizing everything below later.

*==================================================*/

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
typedef enum {
    WARRIOR,
    RANGER,
    MAGE,
    GOD_NERD,
} Entity_Class;

// struct for creating new character stats
typedef struct {
    Entity_Stats stats;
    Entity_Class class;
    char name[20];
    char characterBio[50];
    char combat_menu_options;
} Entity;

Entity* newEntity(Entity_Class class, char name[50]);
void setName(Entity *Target, char name[50]);

// Creates player and sets class to establish what stats they have.
Entity* newEntity(Entity_Class class, char name[50]) {
// allocate memory to player pointers.
Entity *tempEntity = malloc(sizeof(Entity));
setName(tempEntity, name);

// Assign stats based on the given class. 
switch(class){
    case WARRIOR:
        tempEntity->stats.currenthp = 60;
        tempEntity->stats.currentmp = 0;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        tempEntity->stats.physical_armor = 10;
        tempEntity->stats.magic_armor = 7;
        tempEntity->stats.strength = 15;
        tempEntity->stats.dexterity = 10;
        tempEntity->stats.wisdom = 3;
        tempEntity->stats.intelligence = 3;
        tempEntity->stats.luck = 5;
        tempEntity->class = WARRIOR;
        break;
    case RANGER:
        tempEntity->stats.currenthp = 35;
        tempEntity->stats.currentmp = 0;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        tempEntity->stats.physical_armor = 10;
        tempEntity->stats.magic_armor = 8;
        tempEntity->stats.strength = 7;
        tempEntity->stats.dexterity = 5;
        tempEntity->stats.wisdom = 5;
        tempEntity->stats.intelligence = 3;
        tempEntity->stats.luck = 5;
        tempEntity->class = RANGER;
        break;
    case MAGE:
        tempEntity->stats.currenthp = 20;
        tempEntity->stats.currentmp = 60;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        tempEntity->stats.physical_armor = 4;
        tempEntity->stats.magic_armor = 11;
        tempEntity->stats.strength = 3;
        tempEntity->stats.dexterity = 7;
        tempEntity->stats.wisdom = 10;
        tempEntity->stats.intelligence = 15;
        tempEntity->stats.luck = 7;
        tempEntity->class = MAGE;
        break;
    case GOD_NERD:
        tempEntity->stats.currenthp = 100;
        tempEntity->stats.currentmp = 100;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        tempEntity->stats.physical_armor = 100;
        tempEntity->stats.magic_armor = 100;
        tempEntity->stats.strength = 100;
        tempEntity->stats.dexterity = 100;
        tempEntity->stats.wisdom = 100;
        tempEntity->stats.intelligence = 100;
        tempEntity->stats.luck = 100;
        tempEntity->class = GOD_NERD;
   default:
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        break;
    }
    return(tempEntity);     // return memory address of player.
}

// setName creates the name for our entity. Currently this function leaks memory   
// due to strcpy which is not stable, however when the game transitions over to  
// SGDK a different built-in function will be used. 
void setName(Entity *Target, char name[50]) {
    strcpy(Target->name, name);
    return; 
}

/*==============================================*

        Here lies the function prototypes. 
        These should go in the ".h" files. 

*==============================================*/

void displayStats(Entity *Target, int trigger);
int system_DiceRoll(int maximum, int minimum, int add_to_roll, int subtract_from_roll);
bool hitMiss(Entity *Attacker, Entity *Target, float hitPercentage);
float hitCalc(Entity *Attacker, Entity *Target);
int damageCalc(Entity *Attacker, Entity *Target); 
int damageDealt(Entity *Target, int damage);
int classBonus(Entity *Attacker, Entity *Target, int class);
int criticalHit(Entity *Attacker, Entity *Target);
bool areTheyDead(Entity *Target);
int gameController();
char* hitOrMissMessages(int trigger);
char* deadMessage(int trigger);
char* deadAndQuitMessage(int trigger);


/*===================================================*

    Here lies the function declarations are below.
    These all are going to go in the ".c" files

*===================================================*/



// when trigger is passed a 1, then show stats
    // else if trigger is passed a 0, don't show stats
void displayStats (Entity *Target, int trigger) {
    if (trigger == 1) {
        clearAndMove(10, 0);
        clearAndMove(11, 0);
        clearAndMove(12, 0);
        mvprintw(10,0,"\nName: %s\nHealth: %d\nMP: %d\n", Target->name, Target->stats.currenthp, Target->stats.currentmp); 
    } else if (trigger == 0) {
        clearAndMove(10, 0);
        clearAndMove(11, 0);
        clearAndMove(12, 0);
        clearAndMove(13, 0);
    } 
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

// function to calculate how likely it is for an Attacker to hit an enemy
float hitCalc(Entity *Attacker, Entity *Target) {
    float hitPercentage = (Attacker->stats.dexterity) * (system_DiceRoll(6, 1, Attacker->stats.luck, Target->stats.dexterity));
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
    int damage = (Attacker->stats.strength) * system_DiceRoll(6, 1, Attacker->stats.luck, Target->stats.physical_armor);
    return damage;
}

// Function to calculate how much damage is dealt
int damageDealt(Entity *Target, int damage) {
    Target->stats.currenthp = Target->stats.currenthp - damage;
    return Target->stats.currenthp;
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
    if (Target->stats.currenthp <= 0) {
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