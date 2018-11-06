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

int Board::getNumberOfPegs() const {
    int numberOfPegs = 0;
    for(int row = 0; row < NUM_ROWS; row++) {
        for(int col = 0; col < NUM_COLS; col++) {
            if (boardVector[row][col] == PEG)
                numberOfPegs++;
        }
    }
    return numberOfPegs;
}

void Board::bfsSolve() const {
    int generatedCount = 1;
    int expandCount = 0;
    int maxMem = 0;
    float runtime = 0.0;
    
    using namespace chrono;
    auto bfsStart = high_resolution_clock::now(); // Begin time stamp
    
    queue<Board> bfsQueue;
    bfsQueue.push(*this);
    
    Board v, w;
    vector<Board> possibleMoves;
    int moveSize;
    
    while(!bfsQueue.empty()) {
        v = bfsQueue.front();
        bfsQueue.pop();
        
        possibleMoves = v.getPossibleMoves();
        
        if (possibleMoves.empty())
            break;
        
        expandCount++;
        
        moveSize = static_cast<int>(possibleMoves.size());
        
        for(int i = 0; i < moveSize; i++) {
            w = possibleMoves[i];
            bfsQueue.push(w); // Add to the stack
            generatedCount++;
        }
        
        if(bfsQueue.size() > maxMem)
            maxMem = static_cast<int>(bfsQueue.size());
    }
    
    auto bfsEnd = high_resolution_clock::now(); // End time stamp
    // Get the elapsed time in unit microseconds
    runtime = duration_cast<microseconds>(bfsEnd - bfsStart).count();
    runtime /= 1000;
    
    cout << "Algorithm: BFS" << endl;
    cout << "Number of generated nodes: " << generatedCount << endl;
    cout << "Number of expanded nodes: " << expandCount << endl;
    cout << "Maximum number of nodes kept in the memory: " << maxMem << endl;
    cout << "Running time: " << fixed << setprecision(3) << runtime << " milliseconds" << endl;
    cout << "Number of pegs left: " << v.getNumberOfPegs() << endl;
    cout << "Final board:" << endl;
    v.printBoard();
}
