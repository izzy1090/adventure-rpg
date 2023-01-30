#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

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
typedef enum Entity_Class_Enum {
    WARRIOR,
    RANGER,
    MAGE,
    GOD_NERD,
} Entity_Class;

// struct for creating new character stats
typedef struct {
    char characterBio[50];
    char combat_menu_options;
    int location;
    bool moving;
    bool stopping;
    char name[20];
    Entity_Stats stats;
    Entity_Class class;
} Entity;

int system_DiceRoll(int maximum, int minimum, int add_to_roll, int subtract_from_roll);

Entity* newEntity(Entity_Class class, char name[50]);
void setName(Entity *Target, char name[50]);

int main () {
    int row = 3;
    int col = 3;
    int matrix[3][3] = { 
        {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
    };

    Entity *Monster = newEntity(WARRIOR, "Monster");
    Monster->moving = true;
    Monster->location = 10;
    matrix[0][1] = Monster->location;

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("\nElements at: [%i]", i);
            printf("[%d]", matrix[i][j]);
        }
    }

    // printf("First enemy's location on the grid: %d", matrix[2][1]);
    // // for the indexes
    // int i, j;
    // for (i = 0; i < 3; i++){
    //     for (j = 0; j < 3; j++){
    //     printf("Elements at: [%i]", i);
    //     printf("[%d]\n", matrix[i][j]);
    //     }
    // }
    // srand(time(0));
    // int x = rand() % 6; // returns a number between 0 and 6
    // int y = rand() % 3; // returns a number between 0 and 3
    // int diceRoll = system_DiceRoll(6, 1, x, y);
    // printf("\nThe dice results are: %d\n", diceRoll);

    return 0;
}

// Dice roll function to determine probabilities. Helpful for hitPercentage, damageCalc, etc.
int system_DiceRoll(int maximum, int minimum, int add_to_roll, int subtract_from_roll) {
    int dice_roll = random() % (maximum - minimum + 1) + minimum;
    int adjusted_roll = dice_roll + add_to_roll - subtract_from_roll;
    bool debug_showDiceRolls;
    if (adjusted_roll > maximum) {
        adjusted_roll = maximum; 
    }
    else if (adjusted_roll < minimum) {
        adjusted_roll = minimum; 
    }
    return adjusted_roll; 
}

// Creates player and sets class to establish what stats they have.
Entity* newEntity(Entity_Class class, char name[50]) {
// allocate memory to player pointers.
Entity *tempEntity = malloc(sizeof(Entity));
setName(tempEntity, name);

// Assign stats based on the given class. 
switch(class){
    case WARRIOR:
        tempEntity->stats.currenthp = 60;
        tempEntity->stats.currentmp = 0;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
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
        tempEntity->stats.currenthp = 35;
        tempEntity->stats.currentmp = 0;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
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
        tempEntity->stats.currenthp = 20;
        tempEntity->stats.currentmp = 60;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
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
        tempEntity->stats.currenthp = 100;
        tempEntity->stats.currentmp = 100;
        tempEntity->stats.max_hp = 100;
        tempEntity->stats.max_mp = 100;
        tempEntity->stats.physical_armor = 100;
        tempEntity->stats.magic_armor = 100;
        tempEntity->stats.strength = 100;
        tempEntity->stats.dexterity = 100;
        tempEntity->stats.wisdom = 100;
        tempEntity->stats.intelligence = 100;
        tempEntity->stats.luck = 100;
        tempEntity->class = GOD_NERD;
    }
    return(tempEntity);     // return memory address of player.
}

// setName creates the name for our entity. Currently this function leaks memory   
// due to strcpy which is not stable, however when the game transitions over to  
// SGDK a different built-in function will be used. 
void setName(Entity *Target, char name[50]) {
    strcpy(Target->name, name);
    return; 
}