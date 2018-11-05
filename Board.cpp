/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 09.10.2018
 */

#include "Board.h"

#include <iostream>

Board::Board() {
    vector<Status> emptyRow(NUM_COLS, PEG);
    vector< vector<Status> > initialBoard(NUM_ROWS, emptyRow);
    
    for(int row = 0; row < 2; row ++) {
        for(int col = 0; col < 2; col++) {
            initialBoard[row][col] = NOTSPECIFIED;
            initialBoard[row][NUM_COLS-col-1] = NOTSPECIFIED;
            initialBoard[NUM_ROWS-row-1][col] = NOTSPECIFIED;
            initialBoard[NUM_ROWS-row-1][NUM_COLS-col-1] = NOTSPECIFIED;
        }
    }
    
    int centerRow = NUM_ROWS / 2;
    int centerCol = NUM_COLS / 2;
    initialBoard[centerRow][centerCol] = EMPTY;
    
    boardVector = initialBoard;
    lastTurnPegCol = -1;
    lastTurnPegRow = -1;
}

void Board::printBoard() const {
    for(int row = 0; row < NUM_ROWS; row++) {
        for(int col = 0; col < NUM_COLS; col++) {
            if (row == lastTurnPegRow && col == lastTurnPegCol)
                cout << "*" << "  ";
            else
                cout << representativeCharForStatus(boardVector[row][col]) << "  ";
        }
        cout << endl;
    }
}
