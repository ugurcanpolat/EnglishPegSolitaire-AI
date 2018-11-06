/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 09.10.2018
 */

#ifndef Board_h
#define Board_h

#include <chrono> // high_resolution_clock
#include <vector> // vector
#include <list> // list
#include <stack> // stack
#include <queue> // queue
#include <iomanip> // setprecision, fixed

#include "Utilities.h"

class Board {
    vector< vector<Status> > boardVector;
    int lastTurnPegRow;
    int lastTurnPegCol;
    int cost;
    int findCost() const;
public:
    Board();
    Board(const vector< vector<Status> >&, int, int, int);
    bool operator<(const Board&) const;
    int getCost() const;
    void printBoard() const;
    vector<Board> getPossibleMoves() const;
    int getNumberOfPegs() const;
    void bfsSolve() const;
    void dfsSolve() const;
    void aStarSolve() const;
};

#endif /* Board_h */
