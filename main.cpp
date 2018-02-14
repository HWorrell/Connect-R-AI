#include <iostream>
#include <limits>
#include "GameBoard.h"

int main() {

    int rows = 0;

    int columns = 0;

    int toWin = 0;

    int depth;

    std::cout << "How many rows?" << std::endl;

    std::cin >> rows;

    std::cout << "How many columns?" << std::endl;

    std::cin >> columns;

    std::cout << "How many in a row to win?" << std::endl;

    std::cin >> toWin;

    std::cout << "How deep should searches be run?" << std::endl;

    std::cin >> depth;

    std::cout << "Enter 1 for the computer to play first, or 2 for second" << std::endl;
    int computerPlayer;
    std::cin >> computerPlayer;

    GameBoard* Board = new GameBoard(rows, columns, toWin);
int playerNumber;
    if(computerPlayer == 1) {
        playerNumber = 1;
    }
    else if(computerPlayer == 2){
        computerPlayer = 2;
    }
    int columnChoice = -1;

    //testing

    //Board->recursiveCount(*count);


    int* maxPossible = new int(std::numeric_limits<int>::max());
    int* minPossible = new int(std::numeric_limits<int>::min());

    //std::cout << *maxPossible << std::endl;

    //std::cout << *minPossible << std::endl;

    //Board->miniMax(0, 4, true, *maxPossible, *minPossible);

    //int maxIndex = Board->getMaxIndex();

    //int maxValue = Board->getMaxValue();



    //std::cout << "The chip should be placed in row: " << maxIndex << " with a heuristic value of " << maxValue << std::endl;

    //std::cout << *count <<std::endl;

    //int hold;

    //std::cin >> hold;

    //std::cout << "A board is " << sizeof(*Board) << std::endl;

    //end testing

    int piecePlacement;
    bool redWin;
    bool blackWin;

    while(!Board->Win()){
        //run game
        std::cout << "Current Board:" << std::endl;

        //Board->setBoardPositionR(6);

        //Board->printBoard();


        if(computerPlayer == 1){
            Board->printBoard();
            Board->miniMax(0, depth, true, *maxPossible, *minPossible);
            std::cout << "The computer places a piece in column " << Board->getMaxIndex() << " (Remember, index starts at 0" << std::endl;
            Board->setBoardPositionB(Board->getMaxIndex());

            if(Board->Win()){
                blackWin = true;
                break;
            }
            Board->printBoard();
            std::cout << "Red player, please place your piece: " << std::endl;
            std::cin >> piecePlacement;
            Board->setBoardPositionR(piecePlacement);

            if(Board->Win()){
                redWin = true;
                break;
            }
        }
        else{
            Board->printBoard();
            std::cout << "Red player, please place your piece: " << std::endl;
            std::cin >> piecePlacement;
            Board->setBoardPositionR(piecePlacement);

            if(Board->Win()){
                blackWin = true;
                break;
            }
            Board->printBoard();
            Board->miniMax(0, depth, false, *maxPossible, *minPossible);
            std::cout << "The computer places a piece in column " << Board->getMaxIndex() << " (Remember, index starts at 0" << std::endl;
            Board->setBoardPositionB(Board->getMaxIndex());

            if(Board->Win()){
                redWin = true;
                break;
            }
        }



        /*TESTING
        if(computerPlayer == 1){
            Board->printBoard();
            Board->miniMax(0, depth, true, *maxPossible, *minPossible);
            Board->setBoardPositionB(Board->getMaxIndex());
            for(int i = 0; i < Board->numColumns(); i++){
                std::cout << "Branch " << i << " = " << Board->getHeuristic(i) << std::endl;
            }
            playerNumber++;
            if(Board->Win()){
                break;
            }
            Board->printBoard();
            //std::cout << "Red player, please place a piece:" << std::endl;
            //std::cin >> columnChoice;
            //Board->setBoardPositionR(columnChoice);
            Board->miniMax(0, depth, false, *maxPossible, *minPossible);
            Board->setBoardPositionR(Board->getMaxIndex());
            playerNumber--;
        }
        else if(computerPlayer == 2){
            Board->printBoard();
            std::cout << "Black player, please place a piece:" << std::endl;
            std::cin >> columnChoice;
            Board->setBoardPositionB(columnChoice);
            if(Board->Win()){
                break;
            }
            playerNumber++;
            Board->printBoard();
            Board->miniMax(0, depth, false, *maxPossible, *minPossible);
            Board->setBoardPositionR(Board->getMaxIndex());
            playerNumber--;        }
        END TESTING
        */

    }

    std::cout << "Game over! The winner is ";
    if(blackWin){
        std::cout << "Black!" << std::endl;
    }
    else{
        std::cout<< "Red!" << std::endl;
    }

    std::cout << "Final Board: " << std::endl;
    Board->printBoard();


    delete Board;
    delete maxPossible;
    delete minPossible;

    return 0;
}

