#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int system_DiceRoll(int maximum, int minimum, int add_to_roll, int subtract_from_roll);

int main (void) {
    srand(time(0));
    int x = rand() % 6; // returns a number between 0 and 6
    int y = rand() % 3; // returns a number between 0 and 3
    int diceRoll = system_DiceRoll(6, 1, x, y);
    printf("\nThe dice results are: %d\n", diceRoll);
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