/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 09.10.2018
 */

#ifndef Board_h
#define Board_h

#include <chrono> // high_resolution_clock
#include <vector> // vector
#include <queue> // queue
#include <iomanip> // setprecision, fixed

#include "Utilities.h"

class Board {
    vector< vector<Status> > boardVector;
    int lastTurnPegRow;
    int lastTurnPegCol;
public:
    Board();
    Board(const vector< vector<Status> >&, int, int);
    void printBoard() const;
    vector<Board> getPossibleMoves() const;
    int getNumberOfPegs() const;
    void bfsSolve() const;
};

#endif /* Board_h */
