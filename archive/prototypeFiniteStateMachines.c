#include <stdio.h>
#include <stdbool.h>

typedef enum {
    IDLE, 
    PLAYER_TURN,
    AI_TURN,
    PLAYER_DEAD, 
    AI_DEAD
} FSM_STATES;

void stateMachine(FSM_STATES currentState);

int main (){
    stateMachine(3);
    return 0;
}

void stateMachine(FSM_STATES currentState) {
    switch(currentState){
        case IDLE:
            printf("This is the IDLE state");
            // if it's the first turn, whoever has the highest dexterity goes first
            // if it's the second turn, whoever hasn't gone or went last, goes next
            // if the battle is over, terminate state machine - might not be needed 
            break;
        case PLAYER_TURN:
            printf("This is the PLAYER_TURN state");
            // If the player attacks
            // check to see if he hits
                // if he does display the damage and reduce the monsters health
                // check to see if the monster's dead
                    // if he is, then engage the AI_DEAD state
                // if the monster isn't dead, move it to the AI's turn
            // else if he misses display the miss message and move it to the AI's turn
            break;
        case AI_TURN:
            printf("This is the AI_TURN state");
            // check to see if physical defense is higher than magic defense
            // if physical is higher
                // hit with a physical attack
                // display stats
                // if player's health is 0 or below
                    // engage the PLAYER_DEAD state
            // if magic is higher
                // hit with a magic attack
                // display stats
                // if player's health is 0 or below
                    // engage the PLAYER_DEAD state
            break;
        case PLAYER_DEAD:
            printf("This is the PLAYER_DEAD state");
            // display game over screen that the player is dead and they should try again
            break;
        case AI_DEAD:
            printf("This is the AI_DEAD state");
            // display a game over screen that enemy is dead and they can try again to see what happens
            break;
        
    }
}