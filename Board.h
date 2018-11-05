/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 09.10.2018
 */

#ifndef Board_h
#define Board_h

#include <vector>

#include "Utilities.h"

class Board {
    vector< vector<Status> > boardVector;
    int lastTurnPegRow;
    int lastTurnPegCol;
    bool doesValidMoveExist(const vector< vector<Status> >&) const;
public:
    Board();
    void printBoard() const;
};

#endif /* Board_h */
