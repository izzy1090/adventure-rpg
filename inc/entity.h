#ifndef _ENTITY_H
#define _ENTITY_H

    #include "defines.h"

    /*============================================================*

        Prototypes and structs required for Players / Enemies.

    *============================================================*/

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

    typedef struct {
        u16 xPos;
        u16 yPos;
        u16 move;
    } Entity_Loc;

    // struct for creating new character stats
    typedef struct {
        char name[20];
        char characterBio[50];
        Entity_Stats stats;
        Entity_Class class;
    } Entity;

    Entity* newEntity(Entity_Class class, char *name);
    void setName(Entity *Target, char *name);
    Entity* playerEntities (u16 trigger);
    Entity* enemyEntities(u16 trigger);

#endif