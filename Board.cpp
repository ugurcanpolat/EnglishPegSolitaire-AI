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

Board::Board(const vector< vector<Status> >& copy, int lastTurnPegRow,
      int lastTurnPegCol) {
    
    boardVector = copy;
    this->lastTurnPegRow = lastTurnPegRow;
    this->lastTurnPegCol = lastTurnPegCol;
}

void Board::printBoard() const {
    cout << endl;
    for(int row = 0; row < NUM_ROWS; row++) {
        cout << "  ";
        for(int col = 0; col < NUM_COLS; col++) {
            if (row == lastTurnPegRow && col == lastTurnPegCol)
                cout << "*" << "  ";
            else
                cout << representativeCharForStatus(boardVector[row][col]) << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<Board> Board::getPossibleMoves() const {
    vector<Board> moves;
    vector< vector<Status> > move;
    
    for(int row = 0; row < NUM_ROWS; row++) {
        for(int col = 0; col < NUM_COLS; col++) {
            if (boardVector[row][col] == PEG) {
                if (isUpMovePossible(row, col)) {
                    if (boardVector[row-2][col] == EMPTY &&
                        boardVector[row-1][col] == PEG) {
                        move = boardVector;
                        move[row][col] = EMPTY;
                        move[row-1][col] = EMPTY;
                        move[row-2][col] = PEG;
                        Board possibleMove(move, row-2, col);
                        moves.push_back(possibleMove);
                    }
                }
                
                if (isDownMovePossible(row, col)) {
                    if (boardVector[row+2][col] == EMPTY &&
                        boardVector[row+1][col] == PEG) {
                        move = boardVector;
                        move[row][col] = EMPTY;
                        move[row+1][col] = EMPTY;
                        move[row+2][col] = PEG;
                        Board possibleMove(move, row+2, col);
                        moves.push_back(possibleMove);
                    }
                }
                
                if (isLeftMovePossible(row, col)) {
                    if (boardVector[row][col-2] == EMPTY &&
                        boardVector[row][col-1] == PEG) {
                        move = boardVector;
                        move[row][col] = EMPTY;
                        move[row][col-1] = EMPTY;
                        move[row][col-2] = PEG;
                        Board possibleMove(move, row, col-2);
                        moves.push_back(possibleMove);
                    }
                }
                
                if (isRightMovePossible(row, col)) {
                    if (boardVector[row][col+2] == EMPTY &&
                        boardVector[row][col+1] == PEG) {
                        move = boardVector;
                        move[row][col] = EMPTY;
                        move[row][col+1] = EMPTY;
                        move[row][col+2] = PEG;
                        Board possibleMove(move, row, col+2);
                        moves.push_back(possibleMove);
                    }
                }
            }
        }
        
    }
    return moves;
}
