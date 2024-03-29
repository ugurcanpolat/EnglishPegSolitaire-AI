/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 09.10.2018
 */

#ifndef Utilities_h
#define Utilities_h

#define NUM_ROWS 7
#define NUM_COLS 7

#define FIRST  2
#define LAST   4
#define CENTER 3

#include <string>

using namespace std;

typedef enum Status {
    NOTSPECIFIED = 0, EMPTY, PEG
} Status;

typedef enum Heuristic {
    VALID_MOVES = 0, MOVABLE_PEGS
} Heuristic;

string representStatusAsChar(Status status) {
    if (status == NOTSPECIFIED)
        return " ";
    else if (status == EMPTY)
        return "o";
    else
        return "·";
}

bool isUpMovePossible(int row, int col) {
    // Check if Up move is possible for given row-column
    if (row < FIRST)
        return false;
    else if (row >= FIRST && row <= LAST) {
        if (row < LAST && ((col < FIRST) || (col > LAST)))
            return false;
    } else {
        if (col < FIRST || col > LAST)
            return false;
    }
    
    return true;
}

bool isDownMovePossible(int row, int col) {
    // Use rotation rules since board is symmetric
    return isUpMovePossible(NUM_ROWS-row-1, col);
}

bool isLeftMovePossible(int row, int col) {
    // Use rotation rules since board is symmetric
    return isUpMovePossible(col, NUM_COLS-row-1);
}

bool isRightMovePossible(int row, int col) {
    // Use rotation rules since board is symmetric
    return isUpMovePossible(NUM_ROWS-col-1, row);
}

#endif /* Utilities_h */
