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
    
    for(int row = 0; row < FIRST; row ++) {
        for(int col = 0; col < FIRST; col++) {
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

bool Board::doesValidMoveExist(const vector< vector<Status> >& check) const {
    int col, endCol;
    
    for(int row = 0; row < NUM_ROWS; row++) {
        if (row < FIRST || row > LAST) {
            col = FIRST;
            endCol = LAST;
        } else {
            col = 0;
            endCol = NUM_COLS;
        }
        
        for(; col < endCol; col++) {
            if (check[row][col] != PEG)
                continue;
            
            if (isUpMovePossible(row, col)) {
                if (check[row-2][col] == EMPTY && check[row-1][col] == PEG)
                    return true;
            }
            
            if (isDownMovePossible(row, col)) {
                if (check[row+2][col] == EMPTY && check[row+1][col] == PEG)
                    return true;
            }
            
            if (isLeftMovePossible(row, col)) {
                if (check[row][col-2] == EMPTY && check[row][col-1] == PEG)
                    return true;
                
            }
            
            if (isRightMovePossible(row, col)) {
                if (check[row][col+2] == EMPTY && check[row][col+1] == PEG)
                    return true;
            }
        }
    }
    
    return false;
}
