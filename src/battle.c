#include "battle.h"

// /* Dice roll function to determine probabilities. Helpful for hitPercentage, damageCalc, etc. 
// Pass in the maximum and minimum possibilities for a roll outcome. Also add an Entity stat to add to the roll
// or subtract from the roll to add more chance to the probabilities. */ 
// int system_DiceRoll(int maximum, int minimum, int add_to_roll, int subtract_from_roll) {
//     int dice_roll = random() % (maximum - minimum + 1) + minimum;
//     int adjusted_roll = dice_roll + add_to_roll - subtract_from_roll;
//     bool debug_showDiceRolls;
//     if (adjusted_roll > maximum) {
//         adjusted_roll = maximum; 
//     }
//     else if (adjusted_roll < minimum) {
//         adjusted_roll = minimum; 
//     }
//     return adjusted_roll; 
// }

// // Calculates how likely it is for an Attacker to hit an enemy. Pass in the Attacker and the target as args.
// float hitCalc(Entity *Attacker, Entity *Target) {
//     float hitPercentage = (Attacker->stats.dexterity) * (system_DiceRoll(6, 1, Attacker->stats.luck, Target->stats.dexterity));
//     return hitPercentage;
// }

// /* Checks if a hit was made or not. Pass in the Attacker, Target, and hitPercentage probability 
// (as a float) as args. to determine if a hit was made. */ 
// bool hitMiss(Entity *Attacker, Entity *Target, float hitPercentage) {    
//     bool trueFalse;
//     if ( hitPercentage >= 43.33 ) {
//         trueFalse = true;
//         return trueFalse; 
//     }
//     else {
//         trueFalse = false;
//         return trueFalse; 
//     }   
// }

// // Calculates how much damage is done. Pass in an Attacker and Target entity to calculate damage based on pre-defined stats.
// int damageCalc(Entity *Attacker, Entity *Target) {
//     int damage = (Attacker->stats.strength) * system_DiceRoll(6, 1, Attacker->stats.luck, Target->stats.physical_armor);
//     return damage;
// }

// // Applies damage on the Target Entity. Pass in the Target Entity to calculate damage amount based on pre-defined stats.
// int damageDealt(Entity *Target, int damage) {
//     Target->stats.currenthp = Target->stats.currenthp - damage;
//     return Target->stats.currenthp;
// }

// // // Function to declare the class bonus
// // int classBonus (Entity *Attacker, Entity *Target, int class ) {
// //     int classDamage;
// //     if (class == WARRIOR ){
// //         classDamage = 5; }
// //     else if (class == RANGER){
// //         classDamage = 3; }
// //     else if (class == MAGE){
// //         classDamage = 3; }
// //     return classDamage; 
// // }

// /*Test if Target Entity is dead and returns a bool to trigger end of the game over state. */ 
// bool areTheyDead(Entity *Target) {
//     bool deadStatus;
//     if (Target->stats.currenthp <= 0) {
//         deadStatus = true;
//     } else {
//         deadStatus = false;
//     } return deadStatus; 
// }

// // Parent state to control the flow of battle.
// void initBattle (stateMachine currentState, Entity *Enemy) {
//     Entity *Jima = playerEntities(1);
//     Entity *EncounteredEnemy = Enemy;

//     // for debugging purposes to show that a battle has been triggered 
//     // and the appropriate enemy was coupled with the player
//     mvprintw(16, 10, "%s", Jima->name);
//     mvprintw(17, 10, "%s", EncounteredEnemy->name);
    
//     // int ch;
//     // bool hitSuccess;
//     // int damageAmount;
//     // float hitPercentageFloat; 
//     // char *queuedMessage = NULL;

//     // battleMenu();
//     // while ( currentState == Battle){            
//     //     ch = input();
//     //     hitPercentageFloat = hitCalc(Jima, Villain);
//     //     hitSuccess = hitMiss(Jima, Villain, hitPercentageFloat);
//     //     if (hitSuccess) {
//     //         damageAmount = damageCalc(Jima, Villain);
//     //         damageDealt(Villain, damageAmount);
//     //         queuedMessage = hitOrMissMessages(1);
//     //         callStack(queuedMessage);
//     //         displayStats(Villain, 1);
//     //     }
//     //     else if (areTheyDead(Villain)){
//     //         queuedMessage = deadMessage(1);
//     //         displayStats(Villain, 0);
//     //         callStack(queuedMessage); 
//     //         currentState = GameOver;
//     //     }
//     //     else {
//     //         hitSuccess = false; 
//     //         queuedMessage = hitOrMissMessages(0); 
//     //         callStack(queuedMessage);
//     //         }
//     // }
    
// }