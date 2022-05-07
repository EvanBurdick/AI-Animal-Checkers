//Board.cpp
//Created by: Evan Burdick
//1/28/2022
#include "Board.h"

void Board :: PrintBoard(){
    cout<< "    1   2   3   4   5   6   7"<<endl; //print out column legend
    int rowCount = 1;
    for (vector<char> vect1D : boardVect)
    {
        cout << "  -----------------------------"<< endl;
        cout<< rowCount<< " ";
        rowCount ++;
        cout << "| ";
        for (char x : vect1D)
        {
            cout << x << " | ";
        }   
        cout << endl;
    }
    cout << "  -----------------------------"<< endl;
}

bool Board :: IsLegalMove(int row, int col, char direction){

    char currentPiece = boardVect[row][col];
    //determine if cell is empty
    if (currentPiece == ' ')
    {
        return false;
    }
    //determine if player is trying to move enemy piece
    if (playerTurn)
    {
        if (currentPiece == 'm' || currentPiece == 't' ||currentPiece == 'w'|| currentPiece == 'e')
        {
            return false;
        }
    }
    //determine if enemy is trying to move player piece
    if (!playerTurn)
    {
        if (currentPiece == 'M' || currentPiece == 'T' ||currentPiece == 'W'|| currentPiece == 'E')
        {
            return false;
        }
    }
    //determine if trying to move den
    if (currentPiece == 'D' || currentPiece == 'd')
    {
        return false;
    }

    //determine if move is within scope of board
    if(col < 0 || col > 6 || row < 0 || row > 8){
        return false;
    }
    //determine if the direction is valid
    if (direction == 'u' || direction == 'd' || direction == 'l' || direction == 'r'){
    }
    else{
        return false;
    }
    //determine if move is valid
    if (col == 0 && direction == 'l')//piece is trying to move off of the left side of board
    {
        return false;
    }
    if (col == 6 && direction == 'r')//piece is trying to move off of the right side of board
    {
        return false;
    }
    if (row == 0 && direction == 'u')//piece is trying to move off of the top side of board
    {
        return false;
    }
    if (row == 8 && direction == 'd')//piece is trying to move off of the bottom side of board
    {
        return false;
    }

    /////////////////////////////////////
    //         CAPTURE LOGIC           //
    ///////////////////////////////////// 
    char targetLocation;


    if (direction == 'u')//move piece up
    {
        targetLocation = boardVect[row-1][col];
    }
    if (direction == 'd')//move piece down
    {
        targetLocation = boardVect[row+1][col];
    }
    if (direction == 'l')//move piece left
    {
        targetLocation = boardVect[row][col-1];
    }
    if (direction == 'r')//move piece right
    {
        targetLocation = boardVect[row][col+1];
    }
    
    if (targetLocation != ' ') //if the current piece is trying to capture a piece
    {     
        if ((isupper(currentPiece) && isupper(targetLocation)) || (islower(currentPiece) && islower(targetLocation))) // the current piece is trying to capture its own team's piece
        {
            return 0;
        }
    }

    if (currentPiece == 'E') //Player elephant
    {
        if (targetLocation == 'm')
            return 0;
    }
    if (currentPiece == 'T') //Player tiger
    {
        if (targetLocation == 'e')
            return 0;
    }
    if (currentPiece == 'W') //Player wolf
    {
        if (targetLocation == 'e' || targetLocation == 't')
            return 0;
    }
    if (currentPiece == 'M') //Player mouse
    {
        if (targetLocation == 't' || targetLocation == 'w')
            return 0;
    }
    
    if (currentPiece == 'e') //Enemy elephant
    {
        if (targetLocation == 'M')
            return 0;
    }
    if (currentPiece == 't') //Enemy tiger
    {
        if (targetLocation == 'E')
            return 0;
    }
    if (currentPiece == 'w') //Enemy wolf
    {
        if (targetLocation == 'E' || targetLocation == 'T')
            return 0;
    }
    if (currentPiece == 'm') //Enemy mouse
    {
        if (targetLocation == 'T' || targetLocation == 'W')
            return 0;
    }
    return true; //all tests were done, move is 100% legal
}

void Board :: MovePiece(int row, int col, char direction){

    char currentPiece = boardVect[row][col];

    /////////////////////////////////////
    //         MOVE THE PIECE          //
    /////////////////////////////////////

    lastMoveInfo.startPositionRow = row;
    lastMoveInfo.startPositionCol = col;
    lastMoveInfo.startPositionValue = boardVect[row][col];

    boardVect[row][col] = ' '; //set the current cell to empty

    if (direction == 'u')//move piece up
    {
        lastMoveInfo.endPositionRow = row -1;
        lastMoveInfo.endPositionCol = col;
        lastMoveInfo.endPosiotionValue = boardVect[row-1][col];
        boardVect[row-1][col] = currentPiece;
    }
    if (direction == 'd')//move piece down
    {
        lastMoveInfo.endPositionRow = row +1;
        lastMoveInfo.endPositionCol = col;
        lastMoveInfo.endPosiotionValue = boardVect[row+1][col];
        boardVect[row+1][col] = currentPiece;
    }
    if (direction == 'l')//move piece left
    {
        lastMoveInfo.endPositionRow = row;
        lastMoveInfo.endPositionCol = col-1;
        lastMoveInfo.endPosiotionValue = boardVect[row][col-1];
        boardVect[row][col-1] = currentPiece;
    }
    if (direction == 'r')//move piece right
    {
        lastMoveInfo.endPositionRow = row;
        lastMoveInfo.endPositionCol = col+1;
        lastMoveInfo.endPosiotionValue = boardVect[row][col+1];
        boardVect[row][col+1] = currentPiece;
    }
}
void Board :: UndoMove(){

    boardVect[lastMoveInfo.startPositionRow][lastMoveInfo.startPositionCol] = lastMoveInfo.startPositionValue;
    boardVect[lastMoveInfo.endPositionRow][lastMoveInfo.endPositionCol] = lastMoveInfo.endPosiotionValue;
}

void Board :: DetermineWinner(){
    
    playerTurn = false;
    vector<Move> eMoves = GetPossibleMoves('e');
    bool enemyOutOfMoves = (eMoves.size() == 0);

    //determine who won
    if(boardVect[0][3] != 'd' || enemyOutOfMoves){ //player won
        cout << "   -----------------------------"<< endl;
        cout << "   | Congratulations! You won! |"<<endl;
        cout << "   -----------------------------"<< endl<<endl;
        cout << "        Thanks for playing!"<<endl;
    }
    else{ //computer won
        cout << "   --------------------------"<< endl;
        cout << "   | Unfortunate! You lost! |"<<endl;
        cout << "   --------------------------"<< endl<<endl;
        cout << "       Thanks for playing!"<<endl;
    }
}

int Board :: StaticEvaluation(){

    int playerScore = 0, enemyScore = 0;
    for (vector<char> vect1D : boardVect) //for every cell
    {
        for (char x : vect1D)
        {
            if (x == 'D') //player den
                playerScore += 1000;
            if (x == 'E') //player elephant
                playerScore += 100;
            if (x == 'T') //player tiger
                playerScore += 75;
            if (x == 'M') //player mouse
                playerScore += 50;
            if (x == 'W') //player wolf
                playerScore += 25;

            if (x == 'd') //enemy den
                enemyScore += 1000;
            if (x == 'e') //enemy elephant
                enemyScore += 100;
            if (x == 't') //enemy tiger
                enemyScore += 75;
            if (x == 'm') //enemy mouse
                enemyScore += 50;
            if (x == 'w') //enemy wolf
                enemyScore += 25;
        }
    }
    return enemyScore - playerScore;
}

bool Board :: DetectGameOver(){ //returns true if either player's dens are captured
    bool preserveTurn = playerTurn;

    bool denIsCaptured = !(boardVect[0][3] == 'd' && boardVect[8][3] == 'D');
    playerTurn = false;
    vector<Move> eMoves = GetPossibleMoves('e');
    bool enemyOutOfMoves = (eMoves.size() == 0);
    playerTurn = true;
    vector<Move> pMoves = GetPossibleMoves('p');
    bool playerOutOfMoves = (pMoves.size() == 0);

    playerTurn = preserveTurn;

    if(denIsCaptured && enemyOutOfMoves && playerOutOfMoves)
        cout <<"test"<<endl<<"test"<<endl<<"test"<<endl<<"test"<<endl<<"test"<<endl<<"test"<<endl;
    return(denIsCaptured || enemyOutOfMoves || playerOutOfMoves);
}

vector<Move> Board :: GetPossibleMoves(char side){

    //see if each enemy piece exists, and if it does, add all valid moves for that piece to the vector
    vector<Move> moves;
    int row = 0;
    int col = 0;
    Move a;
    for (vector<char> vect1D : boardVect) //for every cell
    {
        for (char x : vect1D)
        {
            if (side == 'e') //collect enemy moves
            {
                if(x == 'e'){ //elephant exists
                if(IsLegalMove(row, col, 'd')){
                    a.row = row, a.col = col, a.direction = 'd';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'u')){
                    a.row = row, a.col = col, a.direction = 'u';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'l')){
                    a.row = row, a.col = col, a.direction = 'l';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'r')){
                    a.row = row, a.col = col, a.direction = 'r';
                    moves.push_back(a);
                }
            }
                if(x == 't'){ //tiger exists
                if(IsLegalMove(row, col, 'd')){
                    a.row = row, a.col = col, a.direction = 'd';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'u')){
                    a.row = row, a.col = col, a.direction = 'u';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'l')){
                    a.row = row, a.col = col, a.direction = 'l';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'r')){
                    a.row = row, a.col = col, a.direction = 'r';
                    moves.push_back(a);
                }
            }
            if(x == 'w'){ //wolf exists
                if(IsLegalMove(row, col, 'd')){
                    a.row = row, a.col = col, a.direction = 'd';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'u')){
                    a.row = row, a.col = col, a.direction = 'u';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'l')){
                    a.row = row, a.col = col, a.direction = 'l';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'r')){
                    a.row = row, a.col = col, a.direction = 'r';
                    moves.push_back(a);
                }
            }
            if(x == 'm'){ //mouse exists
                if(IsLegalMove(row, col, 'd')){
                    a.row = row, a.col = col, a.direction = 'd';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'u')){
                    a.row = row, a.col = col, a.direction = 'u';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'l')){
                    a.row = row, a.col = col, a.direction = 'l';
                    moves.push_back(a);
                }
                if(IsLegalMove(row, col, 'r')){
                    a.row = row, a.col = col, a.direction = 'r';
                    moves.push_back(a);
                }
            }
            }
            else if (side == 'p') //collect player moves
            {
                if(x == 'E'){ //elephant exists
                    if(IsLegalMove(row, col, 'd')){
                        a.row = row, a.col = col, a.direction = 'd';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'u')){
                        a.row = row, a.col = col, a.direction = 'u';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'l')){
                        a.row = row, a.col = col, a.direction = 'l';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'r')){
                        a.row = row, a.col = col, a.direction = 'r';
                        moves.push_back(a);
                    }
                }
                if(x == 'T'){ //tiger exists
                    if(IsLegalMove(row, col, 'd')){
                        a.row = row, a.col = col, a.direction = 'd';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'u')){
                        a.row = row, a.col = col, a.direction = 'u';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'l')){
                        a.row = row, a.col = col, a.direction = 'l';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'r')){
                        a.row = row, a.col = col, a.direction = 'r';
                        moves.push_back(a);
                    }
                }
                if(x == 'W'){ //wolf exists
                    if(IsLegalMove(row, col, 'd')){
                        a.row = row, a.col = col, a.direction = 'd';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'u')){
                        a.row = row, a.col = col, a.direction = 'u';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'l')){
                        a.row = row, a.col = col, a.direction = 'l';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'r')){
                        a.row = row, a.col = col, a.direction = 'r';
                        moves.push_back(a);
                    }
                }
                if(x == 'M'){ //mouse exists
                    if(IsLegalMove(row, col, 'd')){
                        a.row = row, a.col = col, a.direction = 'd';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'u')){
                        a.row = row, a.col = col, a.direction = 'u';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'l')){
                        a.row = row, a.col = col, a.direction = 'l';
                        moves.push_back(a);
                    }
                    if(IsLegalMove(row, col, 'r')){
                        a.row = row, a.col = col, a.direction = 'r';
                        moves.push_back(a);
                    }
                }
            }
            col++;
        }
        row++;
        col = 0;
    }
    return moves;
}