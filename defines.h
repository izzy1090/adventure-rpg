#ifndef _DEFINES_H
#define _DEFINES_H

    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <time.h>
    #include <ncurses.h>

    /*==================================================*

        Here lies all of the State Machine declarations

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

        Function prototypes required 
        for event call stack and UI.

    *==================================================*/

    // An empty node to store a queue entry - for message counter
    struct QNode {
        char *key;
        struct QNode* next; 
    };

    // Used in conjunction with the createQueue() function to create a call stack
    // and creates a place to point our front and rear nodes. Currently used
    // for the messages.
    struct Queue {
        struct QNode *front, *rear; 
    };

    int enQueue(struct Queue* q, char *k);
    void deQueue(struct Queue* q);
    void printOut (char *queuedMessages);

    // Prototypes declarations necessary for the terminal log UI, menus and messages
    void beginNCurses();
    void endNCurses();
    void clearAndMove(int row, int column);
    
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

#endif