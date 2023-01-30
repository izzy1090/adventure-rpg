#ifndef _ATTACK_H
#define _ATTACK_H

    #include "defines.h"
    #include "messages.h"
    #include "input.h"
    #include "entity.h"

    int system_DiceRoll(int maximum, int minimum, int add_to_roll, int subtract_from_roll);
    bool hitMiss(Entity *Attacker, Entity *Target, float hitPercentage);
    float hitCalc(Entity *Attacker, Entity *Target);
    int damageCalc(Entity *Attacker, Entity *Target); 
    int damageDealt(Entity *Target, int damage);
    int criticalHit(Entity *Attacker, Entity *Target);
    bool areTheyDead(Entity *Target);
    int classBonus(Entity *Attacker, Entity *Target, int class);

#endif