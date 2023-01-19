#ifndef _TEST_H
#define _TEST_H

#include <stdio.h>
#include <ncurses.h>
#include <time.h>

void helloWorld();
void displayMenu();
void beginNCurses();
void endNCurses();
void clearAndMove(int row, int column);

#endif