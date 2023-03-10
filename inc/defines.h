#ifndef _DEFINES_H
#define _DEFINES_H

    #include <genesis.h>
    #include <joy.h>
    #include <resources.h>

    /*==================================================*

        Here lies all of the State Machine declarations

    *==================================================*/

    // Papa state machine: where all the big state machine containers live!
    typedef enum { Exploration, Battle, Attack, GameOver } stateMachine;
    stateMachine initialGameState;
    stateMachine nextState;

    typedef enum { Exploration_MovePlayer, Exploration_Enemy, Exploration_WorldEvent } stateMachine_Exploration;

    typedef enum { MovePlayer_Forward, MovePlayer_Left, MovePlayer_Right, MovePlayer_Down } stateMachine_Exploration_MovePlayer;
    typedef enum { EnemyEncounter_SmallMonster } stateMachine_Exploration_EnemyEncounter;
    stateMachine_Exploration_EnemyEncounter enemyEnountered;

    // These are just potential options for the game. We don't necessarily need to program all of these right now.
    typedef enum { Menu_Attack, Menu_Magic, Menu_Defend, Menu_Items, Menu_Escape } stateMachine_Battle;
    typedef enum { Attack_HitCheck, Attack_DamageCalc, Attack_KillCheck } stateMachine_Attack;
    typedef enum { Attack_KillCheck_Loot} stateMachine_Attack_KillCheck;
    typedef enum { GameOver_Win, GameOver_Lose } stateMachine_GameOver;
    typedef enum { GameOver_WinCredits } stateMachine_GameOver_Win;
    typedef enum { GameOver_LoseCredits } stateMachine_GameOver_Lose;

#endif