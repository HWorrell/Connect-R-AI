//
// Created by Heath on 20.06.2017.
//

#include <iostream>
#include "GameBoard.h"

GameBoard::GameBoard(int Inrows, int Incolumns, int IntoWin) {
    this->columns = Incolumns;
    this->rows = Inrows;
    this->toWin = IntoWin;
    BoardState = new char*[columns];
    for(int i = 0; i < columns; i++){
        BoardState[i] = new char[rows];
    }

    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            BoardState[i][j] = ' ';
        }
    }
    this->childrenHeuristic = new int[columns];

    for(int i = 0; i < this->columns; i++){
        childrenHeuristic[i] = ignoreValue;
    }
}

GameBoard::GameBoard (const GameBoard& Board){
    this->columns = Board.columns;
    this->rows = Board.rows;
    this->BoardState = new char*[columns];
    for(int i = 0; i < columns; i++){
        BoardState[i] = new char[rows];
    }

    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            BoardState[i][j] = Board.BoardState[i][j];
        }
    }
    this->childrenHeuristic = new int[columns];

    for(int i = 0; i < this->columns; i++){
        childrenHeuristic[i] = ignoreValue;
    }

    this->toWin = Board.toWin;
}



GameBoard::~GameBoard(){
    for(int i = 0; i < columns; i++){
        delete BoardState[i];
    }
    delete BoardState;
    delete childrenHeuristic;
}

void GameBoard::setBoardPositionR(int column){
    for(int i = rows - 1; i >= 0; i--){
        if(BoardState[column][i] != 'b' && BoardState[column][i] != 'r'){
            BoardState[column][i] = 'r';
            break;
        }
    }
}

void GameBoard::setBoardPositionB(int column){
    for(int i = rows - 1; i >= 0; i--){
        if(BoardState[column][i] != 'b' && BoardState[column][i] != 'r'){
            BoardState[column][i] = 'b';
            break;
        }
    }
}

char GameBoard::getPosition(int column, int row){
    return this->BoardState[column][row];
}

void GameBoard::printBoard(){
    for(int i = 0; i < this->columns; i++){
        std::cout << "---";
    }
    std::cout << std::endl;
    for(int i = 0; i < this->rows; i++){
        std::cout << "|";
        for (int j = 0; j < this->columns; j++) {
            std::cout << this->getPosition(j, i) << "|";
        }
        std:: cout << std::endl;
    }
    for(int i = 0; i < this->columns; i++){
        std::cout << "---";
    }
    std::cout << std::endl;
}





bool GameBoard::Win(){

    for(int i = 0; i < this->columns; i++){
        if(checkCol(i)){
            return true;
        }
    }

    for(int i = 0; i < this->rows; i++){
        if(checkRow(i)){
            return true;
        }
    }
    if(checkDiagonal()){
        return true;
    }


    return false;
}


bool GameBoard::colFilled(int column) {
    int filled = 0;
    for(int i = 0; i < this->rows; i++){
        if(getPosition(column, i) != ' '){
            filled++;
        }
    }
    if(filled == this->rows){
        return true;
    }
    else{
        return false;
    }
}

int GameBoard::Heuristic(bool blackPlayer) {

    //chips are worth 1 * |distance from board edge| points
    int heuristicValueBlack = 0;
    int heuristicValueRed = 0;
//start black
    int midpoint = this->columns / 2;
    int chipValue = 1;
    if(this->columns % 2 == 1) {
        for (int i = 0; i < midpoint; i++) {
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'b') {
                    heuristicValueBlack += chipValue + 2 * i;
                }
            }
        }
        for (int i = midpoint; i < this->columns; i++) {
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'b') {
                    heuristicValueBlack += chipValue + (2 * (this->columns - 1 - i));
                }
            }
        }
    }
    if(this->columns % 2 == 0){
        for(int i = 0; i < this->columns / 2; i++){
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'b') {
                    heuristicValueBlack += chipValue + 2 * i;
                }
            }
        }
        for(int i = (this->columns / 2); i > 0; i--){
            for(int j = 0; j < this->rows; j++) {
                if (getPosition(i, j) == 'b') {
                    heuristicValueBlack += chipValue + (2 * (i - 1));
                }
            }
        }

    }
//end black


    //start red

    midpoint = this->columns / 2;
    chipValue = 1;
    if(this->columns % 2 == 1) {
        for (int i = 0; i < midpoint; i++) {
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'r') {
                    heuristicValueRed += chipValue + 2 * i;
                }
            }
        }
        for (int i = midpoint; i < this->columns; i++) {
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'r') {
                    heuristicValueRed += chipValue + (2 * (this->columns - 1 - i));
                }
            }
        }
    }
    if(this->columns % 2 == 0){
        for(int i = 0; i < this->columns / 2; i++){
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'r') {
                    heuristicValueRed += chipValue + 2 * i;
                }
            }
        }
        for(int i = (this->columns / 2); i > 0; i--){
            for(int j = 0; j < this->rows; j++) {
                if (getPosition(i, j) == 'r') {
                    heuristicValueRed += chipValue + (2 * (i - 1));
                }
            }
        }

    }

    //end red

    //chips in a row/vertical/diagonal are worth 3 * number in row points (assuming there are blanks to move to

    //row

    //black

    int rowValueSum,mostInRow, numInRow = 0;

    if(this->columns % 2 == 1) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (getPosition(j, i) == 'b') {
                    numInRow++;
                    if(numInRow > 1 && j < this->columns / 2){
                        heuristicValueBlack += chipValue + 2 * j;
                    }
                    else if( numInRow > 1 && j >= this->columns / 2){
                        heuristicValueBlack += chipValue + (2 * (this->columns - 1 - i));
                    }
                }
                else {
                    if (numInRow > mostInRow) {
                        mostInRow = numInRow;
                    }
                    numInRow = 0;
                }
            }
        }
    }
    else if(this ->columns % 2 == 0){//redundant, but I link to use else if rather than else.  No idea why.
        for(int i = 0; i < this->rows; i++){
            for (int j = 0; j < this->columns; j++) {
                if(getPosition(j, i) == 'b'){
                    numInRow++;
                    if(numInRow > 1 && j <= this->columns / 2){
                        heuristicValueBlack += chipValue + 2 * i;
                    }
                    else if(numInRow > 1 && j > this->columns / 2){
                        heuristicValueBlack += chipValue + (2 * (i - 1));
                    }
                }
                else{
                    if(numInRow > mostInRow){
                        mostInRow = numInRow;
                    }
                    numInRow = 0;
                }
            }
        }
    }

    //end black

    //red

    rowValueSum,mostInRow, numInRow = 0;

    if(this->columns % 2 == 1) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (getPosition(j, i) == 'r') {
                    numInRow++;
                    if(numInRow > 1 && j < this->columns / 2){
                        heuristicValueRed += chipValue + 2 * j;
                    }
                    else if( numInRow > 1 && j >= this->columns / 2){
                        heuristicValueRed += chipValue + (2 * (this->columns - 1 - i));
                    }
                }
                else {
                    if (numInRow > mostInRow) {
                        mostInRow = numInRow;
                    }
                    numInRow = 0;
                }
            }
        }
    }
    else if(this ->columns % 2 == 0){//redundant, but I link to use else if rather than else.  No idea why.
        for(int i = 0; i < this->rows; i++){
            for (int j = 0; j < this->columns; j++) {
                if(getPosition(j, i) == 'r'){
                    numInRow++;
                    if(numInRow > 1 && j <= this->columns / 2){
                        heuristicValueRed += chipValue + 2 * i;
                    }
                    else if(numInRow > 1 && j > this->columns / 2){
                        heuristicValueRed += chipValue + (2 * (i - 1));
                    }
                }
                else{
                    if(numInRow > mostInRow){
                        mostInRow = numInRow;
                    }
                    numInRow = 0;
                }
            }
        }
    }

    //end red

    //col
    int colValueSum = 0;
    int mostInCol, numInCol = 0;

    //black

    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(getPosition(i, j) == 'r'){
                numInCol++;
            }
            else{
                if(numInCol > mostInCol){
                    mostInCol = numInCol;
                }
                numInCol = 0;
            }
        }
        if(numInCol > mostInCol){
            mostInCol = numInCol;
        }
        if(mostInCol > 1){
            heuristicValueRed += mostInCol * i;
        }
        mostInCol = 0;
        numInCol = 0;
    }


    //end black
    numInCol = 0; mostInCol = 0;
    //red
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(getPosition(i, j) == 'b'){
                numInCol++;
            }
            else{
                if(numInCol > mostInCol){
                    mostInCol = numInCol;
                }
                numInCol = 0;
            }
        }
        if(numInCol > mostInCol){
            mostInCol = numInCol;
        }
        if(mostInCol > 1){
            heuristicValueBlack += mostInCol * i;
        }
    }
    //end red

    //diag

    //scan TL to BR

    //top half TL to BR
    int blackInARow = 0;
    int mostBlackInARow = 0;
    int redInARow = 0;
    int mostRedInARow = 0;
    //top half TL to BR
    for(int i = 0; i < this->columns; i++){
        for (int j = 0, index = i; j < this->rows, index < this->columns; j++, index++) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
            }
            else{
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
            }
            else{
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
                blackInARow = 0;
            }
            if(blackInARow > mostBlackInARow){
                mostBlackInARow = blackInARow;
            }
            if(redInARow > mostRedInARow){
                mostRedInARow = redInARow;
            }
        }

        if(mostBlackInARow > 1){
            heuristicValueBlack += 5 * mostBlackInARow; //this does not track with my original plan, but I am out of time.
        }
        if(mostRedInARow > 1){
            heuristicValueRed += 5 * mostRedInARow; //I am increasing the multiplier to compensate for the lack of weighted columns
        }

        blackInARow = 0;
        redInARow = 0;
    }

    //bottom half TL to BR

    blackInARow = 0;
    redInARow = 0;
    mostBlackInARow = 0;
    mostRedInARow = 0;
    for(int i = 0; i < this->columns; i++){
        for (int j = i, index = 0; j < this->rows, index < this->columns; j++, index++) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow > 1){
            heuristicValueBlack += 5 * mostBlackInARow;
        }
        if(mostRedInARow > 1){
            heuristicValueRed += 5 * mostRedInARow;
        }
    }

    //scan TR to BL

    //top half TR to BL

    for(int i = this->columns - 1; i >= 0; i--){
        for (int j = 0, index = i; j < this->rows, index >= 0; j++, index--) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow >1){
            heuristicValueBlack += mostBlackInARow * 5;
        }
        if(mostRedInARow > 1){
            heuristicValueRed += 5 * mostRedInARow;
        }
        blackInARow = 0;
        redInARow = 0;
        mostBlackInARow = 0;
        mostRedInARow = 0;
    }

    //bottom half TR to BL

    for (int j = 0; j < this->rows; j++) {
        for(int k = j, index = this->columns - 1; k < this->rows, index >= 0; k++, index--){
            if(getPosition(index, k) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, k) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow > 1){
            heuristicValueBlack += mostBlackInARow * 5;
        }
        if(mostRedInARow > 1){
            heuristicValueRed += mostRedInARow * 5;
        }
        mostBlackInARow = 0;
        mostRedInARow = 0;
        redInARow = 0;
        blackInARow = 0;
    }

    //black

    //end black

    //red

    //end red
    //a winning board state is worth 100 points

    if(BlackWin()){
        heuristicValueBlack += 10000;
    }
    if(RedWin()){
        heuristicValueRed += 10000;
    }

    //TODO work out a way to allow for checking of possible moves (ie XXOOO) but x's turn.

    //return the whole thing
    if(blackPlayer) {
        return heuristicValueBlack - heuristicValueRed;
    }
    else{
        return heuristicValueRed - heuristicValueBlack;
    }
}

int GameBoard::miniMax(int depth, int depthLimit, bool blackTurn, int& maxPossible, int& minPossible) {

    if(depth == depthLimit * 2){
        //std::cout << this->Heuristic() << std::endl;

        return this->Heuristic2(blackTurn);
        //testing one huristic v another
        /*
        if(blackTurn)
        return this->Heuristic(blackTurn);
        else
            return this->Heuristic2(blackTurn);
            */
    }
    else{
        for(int i = 0; i < this->columns; i++){
            if(this->colFilled(i) != true){
                //std::cout << "Created child " << i << " at depth " << depth << std::endl;
                child = new GameBoard(*this);
                if(blackTurn){
                    child->setBoardPositionB(i);
                }//end black turn if
                else{
                    child->setBoardPositionR(i);
                }//end red turn else
                childrenHeuristic[i] = child->miniMax((depth + 1), depthLimit, !blackTurn, maxPossible, minPossible);
                //std::cout << "Value = " << childrenHeuristic[i] << std::endl;
                delete child;
                if(depth == 0){
                    std::cout << i << " Branches completed" << std::endl;
                }
            }//end col filled if
            if(colFilled(i) == true){
                childrenHeuristic[i] = ignoreValue;
            }
        }//end for

        //if odd numbered level, return min
        if(depth % 2 == 1){

            //std::cout << "Min index = " << this->getMinIndex() << std::endl;
            return this->getMinValue();

        }
        //if even number level, return max
        if(depth % 2 == 0){

            //std::cout << "Max index = " << this->getMaxIndex() << std::endl;
            return this->getMaxValue();

        }

    }

}



    /*
    if(depth != (depthLimit * 2)){
        for (int i = 0; i < this->columns; i++) {
            if (colFilled(i) != true) {
                child = new GameBoard(this);
                if (blackTurn) {
                    child->setBoardPositionB(i);
                    child->printBoard();
                    std::cout << std::endl;
                } else {
                    child->setBoardPositionR(i);
                    this->printBoard();
                    std::cout << std::endl;
                }
                childrenHeuristic[i] = child->miniMax(depth + 1, depthLimit, !blackTurn, maxIndex);

                delete child;
            }
            else if(colFilled(i)){
                //known value that can be accounted for
                childrenHeuristic[i] = -10000;
            }
        }


    }
    else if(depth == depthLimit * 2){
        std::cout << this->Heuristic() << std::endl;
        return this->Heuristic();
    }


    int max = childrenHeuristic[0];
    int min = childrenHeuristic[0];
    for(int i = 0; i < this->columns; i++){
        if(childrenHeuristic[i] != -10000){
            if(max == -10000){
                max = childrenHeuristic[i];
            }
            if(min == -10000){
                min = childrenHeuristic[i];
            }

            if(childrenHeuristic[i] > max && childrenHeuristic[i] != -10000){
                max = childrenHeuristic[i];

            }
            if(childrenHeuristic[i] < min && childrenHeuristic[i] != -10000){
                min = childrenHeuristic[i];
            }

        }
    }

    if(depth != 1) {
        if (depth % 2 == 0) {
            return max;
        } else {
            return min;
        }
    }
    else{

        maxIndex = 0;
        for(int i = 0; i < this->columns; i++){
            if(childrenHeuristic[i] > childrenHeuristic[maxIndex]){
                maxIndex = i;
            }
        }
    }
}
     */
    int GameBoard::getMinIndex() {
        int minIndex = 0;
        for(int i = 0; i < this->columns; i++){
            if(childrenHeuristic[i] < childrenHeuristic[minIndex]){
                minIndex = i;
            }
        }

        return minIndex;
    }

int GameBoard::getMaxIndex() {
    int maxIndex = 0;
    for(int i = 0; i < this->columns; i++){
        if(childrenHeuristic[i] > childrenHeuristic[maxIndex]){
            maxIndex = i;
        }
    }

    return maxIndex;
}

int GameBoard::getMaxValue(){

    int MaxValue = this->childrenHeuristic[0];
    for(int i = 0; i < this->columns; i++){
        if(childrenHeuristic[i] > MaxValue && childrenHeuristic[i] != ignoreValue){
            MaxValue = childrenHeuristic[i];
        }
    }

    return MaxValue;
}

int GameBoard::getMinValue(){

    int minValue = this->childrenHeuristic[0];
    for(int i = 0; i < this->columns; i++){
        if(childrenHeuristic[i] < minValue && childrenHeuristic[i] != ignoreValue){
            minValue = childrenHeuristic[i];
        }
    }

    return minValue;

}






bool GameBoard::checkRow(int rowNum){
    //check red
    int redInARow = 0;
    int mostRedInARow = 0;
    for (int i = 0; i < this->columns; i++) {
        if(getPosition(i, rowNum) == 'r'){
            redInARow++;
        }
        else{
            if(redInARow > mostRedInARow) {
                mostRedInARow = redInARow;
            }
            redInARow = 0;
        }
    }

    if(mostRedInARow >= this->toWin || redInARow >= this->toWin){
        return true;
    }

    //check black
    int blackInARow = 0;
    int mostBlackInARow = 0;
    for (int i = 0; i < this->columns; i++) {
        if(getPosition(i, rowNum) == 'b'){
            blackInARow++;
        }
        else{
            if(blackInARow > mostBlackInARow) {
                mostBlackInARow = blackInARow;
            }
            blackInARow = 0;
        }
    }

    if(mostBlackInARow >= this->toWin || blackInARow >= this->toWin){
        return true;
    }

    return false;

}

bool GameBoard::checkCol(int colNum) {

    int blackInACol = 0;
    int mostBlackInACol = 0;
    int redInACol = 0;
    int mostRedInACol = 0;
    for(int i = 0; i < this->rows; i++){
        if(getPosition(colNum, i) == 'r'){
            redInACol++;
        }
        else{
            if(redInACol > mostRedInACol){
                mostRedInACol = redInACol;
            }
            redInACol = 0;
        }
    }
    if(mostRedInACol >= this->toWin || redInACol >= this->toWin){
        return true;
    }

    for(int i = 0; i < this->rows; i++){
        if(getPosition(colNum, i) =='b'){
            blackInACol++;
        }
        else{
            if(blackInACol > mostBlackInACol){
                mostBlackInACol = blackInACol;
            }
            blackInACol = 0;
        }
    }
    if(mostBlackInACol >= this->toWin || blackInACol >= this->toWin){
        return true;
    }

    return false;
}

bool GameBoard::checkDiagonal() {

    //scan TL to BR

    //top half TL to BR
    int blackInARow = 0;
    int mostBlackInARow = 0;
    int redInARow = 0;
    int mostRedInARow = 0;
    //top half TL to BR
    for(int i = 0; i < this->columns; i++){
        for (int j = 0, index = i; j < this->rows, index < this->columns; j++, index++) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
            }
            else{
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
            }
            else{
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
                blackInARow = 0;
            }
        }

        if(mostBlackInARow >= this->toWin || mostRedInARow >= this->toWin || blackInARow >= this->toWin || redInARow >= this->toWin){
            return true;
        }

        blackInARow = 0;
        redInARow = 0;
    }

    //bottom half TL to BR

    blackInARow = 0;
    redInARow = 0;
    mostBlackInARow = 0;
    mostRedInARow = 0;
    for(int i = 0; i < this->columns; i++){
        for (int j = i, index = 0; j < this->rows, index < this->columns; j++, index++) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow >= this->toWin || mostRedInARow >= this->toWin){
            return true;
        }
    }

    //scan TR to BL

    //top half TR to BL

    for(int i = this->columns - 1; i >= 0; i--){
        for (int j = 0, index = i; j < this->rows, index >= 0; j++, index--) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow >= this->toWin || mostRedInARow >= this->toWin){
            return true;
        }
        blackInARow = 0;
        redInARow = 0;
        mostBlackInARow = 0;
        mostRedInARow = 0;
    }

    //bottom half TR to BL

    for (int j = 0; j < this->rows; j++) {
        for(int k = j, index = this->columns - 1; k < this->rows, index >= 0; k++, index--){
            if(getPosition(index, k) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, k) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow >= this->toWin || mostRedInARow >= this->toWin){
            return true;
        }
        mostBlackInARow = 0;
        mostRedInARow = 0;
        redInARow = 0;
        blackInARow = 0;
    }


    return false;
}

bool GameBoard::RedWin(){

    for(int i = 0; i < this->columns; i++){
        if(checkColR(i)){
            return true;
        }
    }

    for(int i = 0; i < this->rows; i++){
        if(checkRowR(i)){
            return true;
        }
    }
    if(checkDiagonalR()){
        return true;
    }


    return false;
}

bool GameBoard::checkRowR(int rowNum){
    //check red
    int redInARow = 0;
    int mostRedInARow = 0;
    for (int i = 0; i < this->columns; i++) {
        if(getPosition(i, rowNum) == 'r'){
            redInARow++;
        }
        else{
            if(redInARow > mostRedInARow) {
                mostRedInARow = redInARow;
            }
            redInARow = 0;
        }
    }

    if(mostRedInARow >= this->toWin || redInARow >= this->toWin){
        return true;
    }


    return false;

}

bool GameBoard::checkColR(int colNum) {

    int redInACol = 0;
    int mostRedInACol = 0;
    for(int i = 0; i < this->rows; i++){
        if(getPosition(colNum, i) == 'r'){
            redInACol++;
        }
        else{
            if(redInACol > mostRedInACol){
                mostRedInACol = redInACol;
            }
            redInACol = 0;
        }
    }
    if(mostRedInACol >= this->toWin || redInACol >= this->toWin){
        return true;
    }


    return false;
}

bool GameBoard::checkDiagonalR() {

    //scan TL to BR

    //top half TL to BR
    int blackInARow = 0;
    int mostBlackInARow = 0;
    int redInARow = 0;
    int mostRedInARow = 0;
    //top half TL to BR
    for(int i = 0; i < this->columns; i++){
        for (int j = 0, index = i; j < this->rows, index < this->columns; j++, index++) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
            }
            else{
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
            }
            else{
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
                blackInARow = 0;
            }
        }

        if(mostRedInARow >= this->toWin || redInARow >= this->toWin){
            return true;
        }

        blackInARow = 0;
        redInARow = 0;
    }

    //bottom half TL to BR

    blackInARow = 0;
    redInARow = 0;
    mostBlackInARow = 0;
    mostRedInARow = 0;
    for(int i = 0; i < this->columns; i++){
        for (int j = i, index = 0; j < this->rows, index < this->columns; j++, index++) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostRedInARow >= this->toWin || redInARow >= this->toWin){
            return true;
        }
    }

    //scan TR to BL

    //top half TR to BL

    for(int i = this->columns - 1; i >= 0; i--){
        for (int j = 0, index = i; j < this->rows, index >= 0; j++, index--) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostRedInARow >= this->toWin){
            return true;
        }
        blackInARow = 0;
        redInARow = 0;
        mostBlackInARow = 0;
        mostRedInARow = 0;
    }

    //bottom half TR to BL

    for (int j = 0; j < this->rows; j++) {
        for(int k = j, index = this->columns - 1; k < this->rows, index >= 0; k++, index--){
            if(getPosition(index, k) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, k) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostRedInARow >= this->toWin){
            return true;
        }
        mostBlackInARow = 0;
        mostRedInARow = 0;
        redInARow = 0;
        blackInARow = 0;
    }


    return false;
}

bool GameBoard::BlackWin(){

    for(int i = 0; i < this->columns; i++){
        if(checkColB(i)){
            return true;
        }
    }

    for(int i = 0; i < this->rows; i++){
        if(checkRowB(i)){
            return true;
        }
    }
    if(checkDiagonalB()){
        return true;
    }


    return false;
}

bool GameBoard::checkRowB(int rowNum){
    //check red

    //check black
    int blackInARow = 0;
    int mostBlackInARow = 0;
    for (int i = 0; i < this->columns; i++) {
        if(getPosition(i, rowNum) == 'b'){
            blackInARow++;
        }
        else{
            if(blackInARow > mostBlackInARow) {
                mostBlackInARow = blackInARow;
            }
            blackInARow = 0;
        }
    }

    if(mostBlackInARow >= this->toWin || blackInARow >= this->toWin){
        return true;
    }

    return false;

}

bool GameBoard::checkColB(int colNum) {

    int blackInACol = 0;
    int mostBlackInACol = 0;


    for(int i = 0; i < this->rows; i++){
        if(getPosition(colNum, i) =='b'){
            blackInACol++;
        }
        else{
            if(blackInACol > mostBlackInACol){
                mostBlackInACol = blackInACol;
            }
            blackInACol = 0;
        }
    }
    if(mostBlackInACol >= this->toWin || blackInACol >= this->toWin){
        return true;
    }

    return false;
}

bool GameBoard::checkDiagonalB() {

    //scan TL to BR

    //top half TL to BR
    int blackInARow = 0;
    int mostBlackInARow = 0;
    int redInARow = 0;
    int mostRedInARow = 0;
    //top half TL to BR
    for(int i = 0; i < this->columns; i++){
        for (int j = 0, index = i; j < this->rows, index < this->columns; j++, index++) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
            }
            else{
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
            }
            else{
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
                blackInARow = 0;
            }
        }

        if(mostBlackInARow >= this->toWin || blackInARow >= this->toWin){
            return true;
        }

        blackInARow = 0;
        redInARow = 0;
    }

    //bottom half TL to BR

    blackInARow = 0;
    redInARow = 0;
    mostBlackInARow = 0;
    mostRedInARow = 0;
    for(int i = 0; i < this->columns; i++){
        for (int j = i, index = 0; j < this->rows, index < this->columns; j++, index++) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow >= this->toWin){
            return true;
        }
    }

    //scan TR to BL

    //top half TR to BL

    for(int i = this->columns - 1; i >= 0; i--){
        for (int j = 0, index = i; j < this->rows, index >= 0; j++, index--) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow >= this->toWin){
            return true;
        }
        blackInARow = 0;
        redInARow = 0;
        mostBlackInARow = 0;
        mostRedInARow = 0;
    }

    //bottom half TR to BL

    for (int j = 0; j < this->rows; j++) {
        for(int k = j, index = this->columns - 1; k < this->rows, index >= 0; k++, index--){
            if(getPosition(index, k) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, k) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow >= this->toWin){
            return true;
        }
        mostBlackInARow = 0;
        mostRedInARow = 0;
        redInARow = 0;
        blackInARow = 0;
    }


    return false;
}

int GameBoard::Heuristic2(bool blackPlayer) {

    //chips are worth 1 * |distance from board edge| points
    int heuristicValueBlack = 0;
    int heuristicValueRed = 0;
//start black
    int midpoint = this->columns / 2;
    int chipValue = 1;
    if(this->columns % 2 == 1) {
        for (int i = 0; i < midpoint; i++) {
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'b') {
                    heuristicValueBlack += chipValue + 2 * i;
                }
            }
        }
        for (int i = midpoint; i < this->columns; i++) {
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'b') {
                    heuristicValueBlack += chipValue + (2 * (this->columns - 1 - i));
                }
            }
        }
    }
    if(this->columns % 2 == 0){
        for(int i = 0; i < this->columns / 2; i++){
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'b') {
                    heuristicValueBlack += chipValue + 2 * i;
                }
            }
        }
        for(int i = (this->columns / 2); i > 0; i--){
            for(int j = 0; j < this->rows; j++) {
                if (getPosition(i, j) == 'b') {
                    heuristicValueBlack += chipValue + (2 * (i - 1));
                }
            }
        }

    }
//end black


    //start red

    midpoint = this->columns / 2;
    chipValue = 1;
    if(this->columns % 2 == 1) {
        for (int i = 0; i < midpoint; i++) {
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'r') {
                    heuristicValueRed += chipValue + 2 * i;
                }
            }
        }
        for (int i = midpoint; i < this->columns; i++) {
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'r') {
                    heuristicValueRed += chipValue + (2 * (this->columns - 1 - i));
                }
            }
        }
    }
    if(this->columns % 2 == 0){
        for(int i = 0; i < this->columns / 2; i++){
            for(int j = 0; j < this->rows; j++) {
                if(getPosition(i, j) == 'r') {
                    heuristicValueRed += chipValue + 2 * i;
                }
            }
        }
        for(int i = (this->columns / 2); i > 0; i--){
            for(int j = 0; j < this->rows; j++) {
                if (getPosition(i, j) == 'r') {
                    heuristicValueRed += chipValue + (2 * (i - 1));
                }
            }
        }

    }

    //end red

    //chips in a row/vertical/diagonal are worth 3 * number in row points (assuming there are blanks to move to

    //row

    //black

    int rowValueSum,mostInRow, numInRow = 0;

    if(this->columns % 2 == 1) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (getPosition(j, i) == 'b') {
                    numInRow++;
                    if(numInRow > 1 && j < this->columns / 2){
                        heuristicValueBlack += chipValue + 2 * j;
                    }
                    else if( numInRow > 1 && j >= this->columns / 2){
                        heuristicValueBlack += chipValue + (2 * (this->columns - 1 - i));
                    }
                }
                else {
                    if (numInRow > mostInRow) {
                        mostInRow = numInRow;
                    }
                    numInRow = 0;
                }
            }
        }
    }
    else if(this ->columns % 2 == 0){//redundant, but I link to use else if rather than else.  No idea why.
        for(int i = 0; i < this->rows; i++){
            for (int j = 0; j < this->columns; j++) {
                if(getPosition(j, i) == 'b'){
                    numInRow++;
                    if(numInRow > 1 && j <= this->columns / 2){
                        heuristicValueBlack += chipValue + 2 * i;
                    }
                    else if(numInRow > 1 && j > this->columns / 2){
                        heuristicValueBlack += chipValue + (2 * (i - 1));
                    }
                }
                else{
                    if(numInRow > mostInRow){
                        mostInRow = numInRow;
                    }
                    numInRow = 0;
                }
            }
        }
    }

    //end black

    //red

    rowValueSum,mostInRow, numInRow = 0;

    if(this->columns % 2 == 1) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (getPosition(j, i) == 'r') {
                    numInRow++;
                    if(numInRow > 1 && j < this->columns / 2){
                        heuristicValueRed += chipValue + 2 * j;
                    }
                    else if( numInRow > 1 && j >= this->columns / 2){
                        heuristicValueRed += chipValue + (2 * (this->columns - 1 - i));
                    }
                }
                else {
                    if (numInRow > mostInRow) {
                        mostInRow = numInRow;
                    }
                    numInRow = 0;
                }
            }
        }
    }
    else if(this ->columns % 2 == 0){//redundant, but I link to use else if rather than else.  No idea why.
        for(int i = 0; i < this->rows; i++){
            for (int j = 0; j < this->columns; j++) {
                if(getPosition(j, i) == 'r'){
                    numInRow++;
                    if(numInRow > 1 && j <= this->columns / 2){
                        heuristicValueRed += chipValue + 2 * i;
                    }
                    else if(numInRow > 1 && j > this->columns / 2){
                        heuristicValueRed += chipValue + (2 * (i - 1));
                    }
                }
                else{
                    if(numInRow > mostInRow){
                        mostInRow = numInRow;
                    }
                    numInRow = 0;
                }
            }
        }
    }

    //end red

    //col
    int colValueSum = 0;
    int mostInCol, numInCol = 0;

    //black

    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(getPosition(i, j) == 'r'){
                numInCol++;
            }
            else{
                if(numInCol > mostInCol){
                    mostInCol = numInCol;
                }
                numInCol = 0;
            }
        }
        if(numInCol > mostInCol){
            mostInCol = numInCol;
        }
        if(mostInCol > 1){
            heuristicValueRed += mostInCol * i;
        }
        mostInCol = 0;
        numInCol = 0;
    }


    //end black
    numInCol = 0; mostInCol = 0;
    //red
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows; j++) {
            if(getPosition(i, j) == 'b'){
                numInCol++;
            }
            else{
                if(numInCol > mostInCol){
                    mostInCol = numInCol;
                }
                numInCol = 0;
            }
        }
        if(numInCol > mostInCol){
            mostInCol = numInCol;
        }
        if(mostInCol > 1){
            heuristicValueBlack += mostInCol * i;
        }
    }
    //end red

    //diag

    //scan TL to BR

    //top half TL to BR
    int blackInARow = 0;
    int mostBlackInARow = 0;
    int redInARow = 0;
    int mostRedInARow = 0;
    //top half TL to BR
    for(int i = 0; i < this->columns; i++){
        for (int j = 0, index = i; j < this->rows, index < this->columns; j++, index++) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
            }
            else{
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
            }
            else{
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
                blackInARow = 0;
            }
            if(blackInARow > mostBlackInARow){
                mostBlackInARow = blackInARow;
            }
            if(redInARow > mostRedInARow){
                mostRedInARow = redInARow;
            }
        }

        if(mostBlackInARow > 1){
            heuristicValueBlack += 3 * mostBlackInARow; //this does not track with my original plan, but I am out of time.
        }
        if(mostRedInARow > 1){
            heuristicValueRed += 3 * mostRedInARow; //I am increasing the multiplier to compensate for the lack of weighted columns
        }

        blackInARow = 0;
        redInARow = 0;
    }

    //bottom half TL to BR

    blackInARow = 0;
    redInARow = 0;
    mostBlackInARow = 0;
    mostRedInARow = 0;
    for(int i = 0; i < this->columns; i++){
        for (int j = i, index = 0; j < this->rows, index < this->columns; j++, index++) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow > 1){
            heuristicValueBlack += 3 * mostBlackInARow;
        }
        if(mostRedInARow > 1){
            heuristicValueRed += 3 * mostRedInARow;
        }
    }

    //scan TR to BL

    //top half TR to BL

    for(int i = this->columns - 1; i >= 0; i--){
        for (int j = 0, index = i; j < this->rows, index >= 0; j++, index--) {
            if(getPosition(index, j) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, j) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow >1){
            heuristicValueBlack += mostBlackInARow * 3;
        }
        if(mostRedInARow > 1){
            heuristicValueRed += 3 * mostRedInARow;
        }
        blackInARow = 0;
        redInARow = 0;
        mostBlackInARow = 0;
        mostRedInARow = 0;
    }

    //bottom half TR to BL

    for (int j = 0; j < this->rows; j++) {
        for(int k = j, index = this->columns - 1; k < this->rows, index >= 0; k++, index--){
            if(getPosition(index, k) == 'r'){
                redInARow++;
                if(redInARow > mostRedInARow){
                    mostRedInARow = redInARow;
                }
            }
            else{

                redInARow = 0;
            }
            if(getPosition(index, k) == 'b'){
                blackInARow++;
                if(blackInARow > mostBlackInARow){
                    mostBlackInARow = blackInARow;
                }
            }
            else{

                blackInARow = 0;
            }
        }
        if(mostBlackInARow > 1){
            heuristicValueBlack += mostBlackInARow * 3;
        }
        if(mostRedInARow > 1){
            heuristicValueRed += mostRedInARow * 3;
        }
        mostBlackInARow = 0;
        mostRedInARow = 0;
        redInARow = 0;
        blackInARow = 0;
    }

    //black

    //end black

    //red

    //end red
    //a winning board state is worth 100 points

    if(BlackWin()){
        heuristicValueBlack += 10000;
    }
    if(RedWin()){
        heuristicValueRed += 10000;
    }

    //TODO work out a way to allow for checking of possible moves (ie XXOOO) but x's turn.

    //return the whole thing
    if(blackPlayer) {
        return heuristicValueBlack - heuristicValueRed;
    }
    else{
        return heuristicValueRed - heuristicValueBlack;
    }
}

