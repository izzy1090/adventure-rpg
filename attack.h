#ifndef _ATTACK_H
#define _ATTACK_H

    #include "defines.h"
    #include "input.h"

    void displayStats(Entity *Target, int trigger);
    void battleMenu();
    int system_DiceRoll(int maximum, int minimum, int add_to_roll, int subtract_from_roll);
    bool hitMiss(Entity *Attacker, Entity *Target, float hitPercentage);
    float hitCalc(Entity *Attacker, Entity *Target);
    int damageCalc(Entity *Attacker, Entity *Target); 
    int damageDealt(Entity *Target, int damage);
    int criticalHit(Entity *Attacker, Entity *Target);
    bool areTheyDead(Entity *Target);
    char* hitOrMissMessages(int trigger);
    char* deadMessage(int trigger);
    char* deadAndQuitMessage(int trigger);
    int classBonus(Entity *Attacker, Entity *Target, int class);
    void initializeBattle();

#endif