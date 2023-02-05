#include "entity.h"

/*==================================================*

            Character function declarations.

*==================================================*/

void setName(Entity *Target, char name[50]);

// Creates player and sets class to establish what stats they have.
Entity* newEntity(Entity_Class class, char name[50]) {
// allocate memory to player pointers.
Entity *tempEntity = malloc(sizeof(Entity));
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
    case BEAST:
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 0;
        tempEntity->stats.currenthp = tempEntity->stats.max_hp;
        tempEntity->stats.currentmp = tempEntity->stats.max_mp;
        tempEntity->stats.physical_armor = 20;
        tempEntity->stats.magic_armor = 03;
        tempEntity->stats.strength = 20;
        tempEntity->stats.dexterity = 7;
        tempEntity->stats.wisdom = 2;
        tempEntity->stats.intelligence = 1;
        tempEntity->stats.luck = 5;
        tempEntity->class = BEAST;
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

// setName creates the name for our entity. Currently this function leaks memory   
// due to strcpy which is unstable, however when the game transitions over to  
// SGDK a different built-in function will be used. 
void setName(Entity *Target, char name[50]) {
    strcpy(Target->name, name);
    return; 
}

// Point the invocated results to a pointer with the name of the Entity you want to create
// Pass in a character class to establish pre-defined stats and a name for the Entity
Entity* newEntity(Entity_Class class, char name[50]);

/* Use integers to trigger the creation and return of an Entity to play around with on a battlefield.
This allows us to manipulate data related to location, health, and other integer based stats.

1: Jima, 2: Brock, and 3: Sean The Mage */
Entity* playerEntities (int trigger){
    Entity *Jima = newEntity(WARRIOR, "Jima");
    Entity *Brock = newEntity(RANGER, "Brock");
    Entity *SeanTheMage = newEntity(MAGE, "Sean The Mage");

    Entity *returnedPlayer = NULL;

    switch(trigger){
        case 1: 
            returnedPlayer = Jima;
        case 2: 
            returnedPlayer = Brock;
        case 3: 
            returnedPlayer = SeanTheMage;
    }
    return (returnedPlayer);
}

/* Use integers to trigger the creation and return of an Entity to play around with on a battlefield.
This allows us to manipulate data related to location, health, and other integer based stats.

1: Small Monster, 2: Flying Banshee, and 3: Goblin */
Entity* enemyEntities(int triggerEnemy){
    Entity *SmallMonster = newEntity(BEAST, "Small Monster");
    Entity *FlyingBanshee = newEntity(BEAST, "Flying Banshee");
    Entity *Goblin = newEntity(BEAST, "Goblin");

    Entity *returnedEnemy = NULL;
    
    switch (triggerEnemy){
        case 1: 
            returnedEnemy = SmallMonster;
        case 2: 
            returnedEnemy = FlyingBanshee;
        case 3: 
            returnedEnemy = Goblin;
        }
        return (returnedEnemy);
}