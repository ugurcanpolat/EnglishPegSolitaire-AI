/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 09.10.2018
 */

#ifndef Utilities_h
#define Utilities_h

#define NUM_ROWS 7
#define NUM_COLS 7

#include <string>

using namespace std;

typedef enum Status {
    NOTSPECIFIED = 0, EMPTY, PEG
} Status;

string representativeCharForStatus(Status status) {
    if (status == NOTSPECIFIED)
        return " ";
    else if (status == EMPTY)
        return "o";
    else
        return "·";
}

#endif /* Utilities_h */
