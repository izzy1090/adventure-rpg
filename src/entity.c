#include "entity.h"

/*============================================================*

    Function declarations required for Players / Enemies.

*============================================================*/

// Creates player and sets class to establish what stats they have.
Entity* newEntity(Entity_Class class, char *name) {
// allocate memory to player pointers.
Entity *tempEntity = MEM_alloc(sizeof(Entity));
setName(tempEntity, name);

// Assign stats based on the given class. 
switch(class){
    case WARRIOR:
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 05;
        tempEntity->stats.currenthp = tempEntity->stats.max_hp;
        tempEntity->stats.currentmp = tempEntity->stats.max_mp;
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
        tempEntity->stats.max_hp = 60;
        tempEntity->stats.max_mp = 30;
        tempEntity->stats.currenthp = tempEntity->stats.max_hp;
        tempEntity->stats.currentmp = tempEntity->stats.max_mp;
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
        tempEntity->stats.max_hp = 20;
        tempEntity->stats.max_mp = 60;
        tempEntity->stats.currenthp = tempEntity->stats.max_hp;
        tempEntity->stats.currentmp = tempEntity->stats.max_mp;
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
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        tempEntity->stats.currenthp = tempEntity->stats.max_hp;
        tempEntity->stats.currentmp = tempEntity->stats.max_mp;
        tempEntity->stats.physical_armor = 100;
        tempEntity->stats.magic_armor = 100;
        tempEntity->stats.strength = 100;
        tempEntity->stats.dexterity = 100;
        tempEntity->stats.wisdom = 100;
        tempEntity->stats.intelligence = 100;
        tempEntity->stats.luck = 100;
        tempEntity->class = GOD_NERD;
        break;
    }
    return(tempEntity); // return memory address of player.
}

/* Sets the name of the Entity to be whatever is passed into the name arg. */
void setName(Entity *Target, char *name) {
    /* 1st arg: where you want to pass string
       2nd arg: string you want to pass
       3rd arg: string's length */
    strncpy(Target->name, name, sizeof(Target->name));
    // need to add a terminating char as strncpy does not provide terminating characters
    Target->name[sizeof(Target->name) - 1] = '\0';
}

/* Use integers to trigger the creation and return of an Entity to play around with on a battlefield.
This allows us to manipulate data related to location, health, and other integer based stats.

1: Jima, 2: Brock, and 3: Sean The Mage */
Entity* playerEntities (u16 trigger){
    // You can create templates for new characters here
    Entity *Jima = newEntity(WARRIOR, "Jima");
    Entity *returnedPlayer = MEM_alloc(sizeof(Entity));
    switch(trigger){
        case 1: 
            returnedPlayer = Jima;
            break;
    }
    return (returnedPlayer);
}

/* Use integers to trigger the creation and return of an Entity to play around with on a battlefield.
This allows us to manipulate data related to location, health, and other integer based stats.

1: Small Monster, 2: Flying Banshee, and 3: Goblin */
Entity* enemyEntities(u16 trigger){
    Entity *SmallMonster = newEntity(RANGER, "Small Monster");

    Entity *returnedEnemy = 0;
    
    switch (trigger){
        case 1: 
            returnedEnemy = SmallMonster;
            break;
        }
    return (returnedEnemy);
}