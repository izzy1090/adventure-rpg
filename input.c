#include "input.h"

// Used to detect input from the keyboard and then return integers 
// that correspond with keys on a computer keyboard. We can use 
// those values to then trigger certain actions or states
int gameController() {
    int change;
    keypad(stdscr, TRUE);   // This allows keypad input
    while((change = getch()) != KEY_ENTER){
        switch(change){   
            case KEY_LEFT:
                return (change);
            case KEY_RIGHT:
                return (change);
            case KEY_DOWN:
                return (change);
            case KEY_UP:
                return (change);
            case 97: //a
                break;
            case 115: //s
                break;
            case 100: //d
                break;
            case 119: //w
                break;
            case 113: //q
                return (change);
            case 101: //e
                return (change);
            default:
                break;
        }
    } 
    return (change); 
}