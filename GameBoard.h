//
// Created by Heath on 20.06.2017.
//

#ifndef CONNECTR_GAMEBOARD_H
#define CONNECTR_GAMEBOARD_H

class GameBoard{
public:

    GameBoard(int rows, int columns, int toWin);
    GameBoard(const GameBoard& Original);
    GameBoard(int col);
    ~GameBoard();
    int numColumns(){return this->columns;};
    int numRows(){return rows;};
    int getHeuristic(int value){return childrenHeuristic[value];};
    int getMinIndex();
    int getMaxIndex();
    int getMinValue();
    int getMaxValue();
    void setBoardPositionR(int column);
    void setBoardPositionB(int column);
    char getPosition(int column, int row);
    bool checkRow(int rowNum);
    bool checkCol(int colNum);
    bool checkDiagonal();
    void printBoard();
    bool colFilled(int column);
    int Heuristic(bool blackPlayer);
    //the following functions are very 'hackey' but I realized I needed them very late, right before the
    //deadline, so I either put them together this way, or didn't have them. "Weeks of coding saves hours of planning" indeed
    bool RedWin();
    bool checkRowR(int rowNum);
    bool checkColR(int colNum);
    bool checkDiagonalR();
    bool BlackWin();
    bool checkRowB(int rowNum);
    bool checkColB(int colNum);
    bool checkDiagonalB();
    bool Win();
    int miniMax(int depth, int depthLimit, bool blackTurn, int& maxPossible, int& minPossible);
    //testing
    void recursiveCount(int &count);
    int Heuristic2(bool blackPlayer);
    //testing


private:
    //2d array for the board state.  'b' = black, 'r' = red
    char** BoardState;
    int rows;
    int columns;
    int toWin;
    int* childrenHeuristic;
    GameBoard* child;
    int heuristic;
    int ignoreValue = -100000;
};




#endif //CONNECTR_GAMEBOARD_H
