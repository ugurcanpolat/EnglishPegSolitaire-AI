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
    
    // Create initial board
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
    // Center of board is a hole
    initialBoard[centerRow][centerCol] = EMPTY;
    
    boardVector = initialBoard;
    lastTurnPegCol = -1; // Default value
    lastTurnPegRow = -1; // Default value
    cost = findCost(); // Calculate cost
}

Board::Board(const vector< vector<Status> >& copy, int lastTurnPegRow,
             int lastTurnPegCol, int previousCost) {
    
    boardVector = copy;
    this->lastTurnPegRow = lastTurnPegRow;
    this->lastTurnPegCol = lastTurnPegCol;
    cost = findCost(); // Calculate cost
}

int Board::findCost() const {
    int cost = 0;
    
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if (boardVector[row][col] == PEG) {
                if ((row == (CENTER-1) || row == (CENTER+1)) &&
                    (col == (CENTER-1) || col == (CENTER+1))) {
                    cost += 2;
                } else if ((row == (CENTER-1) || row == (CENTER+1)) &&
                           col == CENTER) {
                    continue;
                } else if (row == CENTER &&
                          (col == (CENTER-1) || col == (CENTER+1))) {
                    continue;
                } else if ((row == 0 || row == NUM_ROWS-1) &&
                           (col == FIRST || col == LAST)) {
                    cost += 4;
                } else if ((row == FIRST || row == LAST) &&
                           (col == 0 || col == NUM_COLS-1)) {
                    cost += 4;
                } else {
                    cost += 1;
                }
            }
        }
    }

    return cost + getNumberOfPegs() * 2;
}

bool Board::operator<(const Board& comp) const {
    // < Operator overloading which compares costs. This will be used
    // in list.sort() function
    if (cost < comp.getCost())
        return true;
    
    return false;
}

int Board::getCost() const {
    return cost;
}

void Board::printBoard() const {
    cout << endl;
    for(int row = 0; row < NUM_ROWS; row++) {
        cout << "  ";
        for(int col = 0; col < NUM_COLS; col++) {
            if (row == lastTurnPegRow && col == lastTurnPegCol)
                cout << "*" << "  ";
            else
                cout << representStatusAsChar(boardVector[row][col]) << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<Board> Board::getPossibleMoves() const {
    vector<Board> moves;
    vector< vector<Status> > move;
    
    // Traverse through whole board
    for(int row = 0; row < NUM_ROWS; row++) {
        for(int col = 0; col < NUM_COLS; col++) {
            if (boardVector[row][col] == PEG) {
                // If Up move is possible add the move board to vector
                if (isUpMovePossible(row, col)) {
                    if (boardVector[row-2][col] == EMPTY &&
                        boardVector[row-1][col] == PEG) {
                        move = boardVector;
                        move[row][col] = EMPTY;
                        move[row-1][col] = EMPTY;
                        move[row-2][col] = PEG;
                        Board possibleMove(move, row-2, col, cost);
                        moves.push_back(possibleMove);
                    }
                }
                
                // If Down move is possible add the move board to vector
                if (isDownMovePossible(row, col)) {
                    if (boardVector[row+2][col] == EMPTY &&
                        boardVector[row+1][col] == PEG) {
                        move = boardVector;
                        move[row][col] = EMPTY;
                        move[row+1][col] = EMPTY;
                        move[row+2][col] = PEG;
                        Board possibleMove(move, row+2, col, cost);
                        moves.push_back(possibleMove);
                    }
                }
                
                // If Left move is possible add the move board to vector
                if (isLeftMovePossible(row, col)) {
                    if (boardVector[row][col-2] == EMPTY &&
                        boardVector[row][col-1] == PEG) {
                        move = boardVector;
                        move[row][col] = EMPTY;
                        move[row][col-1] = EMPTY;
                        move[row][col-2] = PEG;
                        Board possibleMove(move, row, col-2, cost);
                        moves.push_back(possibleMove);
                    }
                }
                
                // If Right move is possible add the move board to vector
                if (isRightMovePossible(row, col)) {
                    if (boardVector[row][col+2] == EMPTY &&
                        boardVector[row][col+1] == PEG) {
                        move = boardVector;
                        move[row][col] = EMPTY;
                        move[row][col+1] = EMPTY;
                        move[row][col+2] = PEG;
                        Board possibleMove(move, row, col+2, cost);
                        moves.push_back(possibleMove);
                    }
                }
            }
        }
        
    }
    return moves;
}

int Board::getNumberOfPegs() const {
    // Returns number of pegs on the board
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
    // BFS function is implemented according to my implementation from
    // homework of Analysis of Algorithms II class.
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
    cout << "Running time: " << fixed << setprecision(3) << runtime;
    cout << " milliseconds" << endl;
    cout << "Number of pegs left: " << v.getNumberOfPegs() << endl;
    cout << "Final board:" << endl;
    v.printBoard();
}

void Board::dfsSolve() const {
    // BFS function is implemented according to my implementation from
    // homework of Analysis of Algorithms II class.
    int generatedCount = 1;
    int expandCount = 0;
    int maxMem = 0;
    float runtime = 0.0;
    
    using namespace chrono;
    auto dfsStart = high_resolution_clock::now(); // Begin time stamp
    
    stack<Board> dfsStack;
    dfsStack.push(*this);

    Board u, v;
    vector<Board> possibleMoves;
    int moveSize;
    
    while(!dfsStack.empty()) {
        u = dfsStack.top();
        dfsStack.pop();
        
        possibleMoves = u.getPossibleMoves();
        
        if (possibleMoves.empty())
            break;
        
        expandCount++;
        
        moveSize = static_cast<int>(possibleMoves.size());
        
        for(int i = 0; i < moveSize; i++) {
            v = possibleMoves[i];
            dfsStack.push(v);
            generatedCount++;
        }
                
        if(dfsStack.size() > maxMem)
            maxMem = static_cast<int>(dfsStack.size());
    }
    
    auto dfsEnd = high_resolution_clock::now(); // Begin time stamp
    // Get the elapsed time in unit microseconds
    runtime = duration_cast<microseconds>(dfsEnd - dfsStart).count();
    runtime /= 1000;
    
    cout << "Algorithm: DFS" << endl;
    cout << "Number of generated nodes: " << generatedCount << endl;
    cout << "Number of expanded nodes: " << expandCount << endl;
    cout << "Maximum number of nodes kept in the memory: " << maxMem << endl;
    cout << "Running time: " << fixed << setprecision(3) << runtime;
    cout << " milliseconds" << endl;
    cout << "Number of pegs left: " << v.getNumberOfPegs() << endl;
    cout << "Final board:" << endl;
    v.printBoard();
}

void Board::aStarSolve() const {
    int generatedCount = 1;
    int expandCount = 0;
    int maxMem = 0;
    float runtime = 0.0;
    
    using namespace chrono;
    auto aStarStart = high_resolution_clock::now(); // Begin time stamp
    
    list<Board> aStarList;
    aStarList.push_back(*this);
    
    Board x, y;
    vector<Board> possibleMoves;
    int moveSize;
    
    while(!aStarList.empty()) {
        x = aStarList.front();
        aStarList.pop_front();
        
        possibleMoves = x.getPossibleMoves();
        
        if (possibleMoves.empty())
            break;
        
        expandCount++;
        
        moveSize = static_cast<int>(possibleMoves.size());
        
        for(int i = 0; i < moveSize; i++) {
            y = possibleMoves[i];
            aStarList.push_back(y);
            generatedCount++;
        }
        
        aStarList.sort();
        
        if(aStarList.size() > maxMem)
            maxMem = static_cast<int>(aStarList.size());
    }
    
    auto aStarEnd = high_resolution_clock::now(); // Begin time stamp
    // Get the elapsed time in unit microseconds
    runtime = duration_cast<microseconds>(aStarEnd - aStarStart).count();
    runtime /= 1000;
    
    cout << "Algorithm: A*" << endl;
    cout << "Number of generated nodes: " << generatedCount << endl;
    cout << "Number of expanded nodes: " << expandCount << endl;
    cout << "Maximum number of nodes kept in the memory: " << maxMem << endl;
    cout << "Running time: " << fixed << setprecision(3) << runtime;
    cout << " milliseconds" << endl;
    cout << "Number of pegs left: " << y.getNumberOfPegs() << endl;
    cout << "Final board:" << endl;
    y.printBoard();
}
