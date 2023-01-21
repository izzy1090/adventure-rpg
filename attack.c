#include "defines.h"
#include "attack.h"

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

// Displays what available actions the player has to take.
void battleMenu() {
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

// function to display message that the villain is dead and it's time to quit the program
char* deadAndQuitMessage(int trigger){
    char *timeToQuit = "";
    if (trigger == 1){
        timeToQuit = "Okay, they're dead! Stop beating a dead horse and press 'q' to quit please!";
        return timeToQuit;
    } return timeToQuit;
}


// Create an empty linked list container which is used 
// to insert nodes at the front or back of the queue.

// This function declaration will live
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q; 
}

// This is the current game loop that's invoked when the battle state is active. 
// This is temporary and needs to be reorganized according to how we want our
// state machine switches to flow.
void initializeBattle(){
    // Need to figure out where these entities are going to live
    Entity *Hero = newEntity(WARRIOR, "Jima");
    Entity *Villain = newEntity(RANGER, "Small Monster");

    int ch;
    bool hitMissVar;
    int damageVar;
    float hitPercentageFloat; 
    char *queuedMessage = NULL;
    struct Queue* q = createQueue();

    battleMenu();
    while (ch != 'q'){
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
}