/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 09.10.2018
 */

#include <iostream>

#include "Board.cpp"

int main(void) {
    Board solitareBoard;
    
    cout << "Initial board:" << endl;
    solitareBoard.printBoard();
    solitareBoard.bfsSolve();
    solitareBoard.dfsSolve();
    solitareBoard.aStarSolve();
    
    return 0;
}
