#ifndef _ATTACK_H
#define _ATTACK_H

    #include "defines.h"
    #include "messages.h"
    #include "entity.h"

    int system_DiceRoll(int maximum, int minimum, int add_to_roll, int subtract_from_roll);
    bool hitMiss(Entity *Attacker, Entity *Target, float hitPercentage);
    float hitCalc(Entity *Attacker, Entity *Target);
    int damageCalc(Entity *Attacker, Entity *Target); 
    int dealDamage(Entity *Target, int damage);
    int classBonus(Entity *Attacker, Entity *Target, int class);
    int criticalHit(Entity *Attacker, Entity *Target);
    bool areTheyDead(Entity *Target);
    void displayStats(Entity *Target, int trigger);
    void initBattle (stateMachine currentState, Entity *Enemy);
    
#endif