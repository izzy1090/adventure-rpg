#include "battle.h"

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

void initializeBattle () {
    Entity *Jima = newEntity(WARRIOR, "Jima");
    Entity *Villain = enemyEntities(1);

    gameState = Battle;

    int ch;
    bool hitSuccess;
    int damageAmount;
    float hitPercentageFloat; 
    char *queuedMessage = NULL;

    battleMenu();
    while ( gameState == Battle){            
        ch = input();
        hitPercentageFloat = hitCalc(Jima, Villain);
        hitSuccess = hitMiss(Jima, Villain, hitPercentageFloat);
        if (hitSuccess) {
            damageAmount = damageCalc(Jima, Villain);
            damageDealt(Villain, damageAmount);
            queuedMessage = hitOrMissMessages(1);
            callStack(queuedMessage);
            displayStats(Villain, 1);
            if (areTheyDead(Villain)) {
                queuedMessage = deadMessage(1);
                displayStats(Villain, 0);
                callStack(queuedMessage); 
                }
            }
            else if (areTheyDead(Villain) && Villain->stats.currenthp <= 0 ){
                gameState = Exploration;
            }
        else {
            hitSuccess = false; 
            queuedMessage = hitOrMissMessages(0); 
            callStack(queuedMessage);
            }
    }
}