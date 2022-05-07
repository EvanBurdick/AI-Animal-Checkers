//driver.cpp
//Created by: Evan Burdick
//1/28/2022
#include <iostream>
#include "Board.h"

using namespace std;

int main(){

    int minimax(Board &, int, int, int, bool); //define the function
    void startGameInformation();
    startGameInformation();
    Board gameInstance;
    int row, col;
    char dir;
    bool validMove;
    char startChoice = ' ';
    while (startChoice != 'C' && startChoice != 'c' && startChoice != 'P' && startChoice != 'p')
    {
        cout << "Who will start the game? Enter 'p' for player, 'c' for computer: ";
        cin >> startChoice;
        if (startChoice == 'C' || startChoice == 'c')
            gameInstance.playerTurn = false;
        else if(startChoice == 'P' || startChoice == 'p')
            gameInstance.playerTurn = true;
        else
            cout << "Incorrect input! Try again."<<endl;
    }

    while (!gameInstance.DetectGameOver()) //Both dens are intact (MAIN GAME LOOP)
    {
        if (gameInstance.playerTurn == true) //Player's Turn
        {         
            cout << "\n  -----------------------------"<<endl;
            cout << "  |         Your Turn         |"<<endl;
            cout << "  -----------------------------"<<endl<<endl;
            gameInstance.PrintBoard();

            cout << "Move piece in row: ";
            cin >> row;
            row--; //correct the offset

            cout << "Move piece in column: ";
            cin >> col;
            col--; //correct the offset

            cout << "Which direction to move piece? Enter u for up, d for down, l for left, r for right: ";
            cin >> dir;

            validMove = gameInstance.IsLegalMove(row, col, dir); //check to see if the player's move is legal
            if (validMove)
            {
                gameInstance.MovePiece(row,col,dir);
                gameInstance.playerTurn = false; //end the player's turn
            }
            else {
                cout << "\nThe move you are trying to make is not valid!"<<endl;
            }
        }
        else //Enemy's Turn
        {
            int test = minimax(gameInstance, 8, -100000, 100000, true);
            gameInstance.MovePiece(gameInstance.bestMove.row, gameInstance.bestMove.col, gameInstance.bestMove.direction);
            cout << "\n  -----------------------------"<<endl;
            cout << "  |       Computer's Turn     |"<<endl;
            cout << "  -----------------------------"<<endl<<endl;
            gameInstance.PrintBoard();
            cout << "Computer moved piece from row: " << gameInstance.bestMove.row +1 <<endl;
            cout << "Computer moved piece from column: " << gameInstance.bestMove.col +1<<endl;
            cout << "Computer moved piece: " << gameInstance.bestMove.direction <<endl;
            gameInstance.playerTurn = true;
        }
    }
    gameInstance.DetermineWinner(); // Print out who won!
    cout << "< Enter any key to quit program >";
    char nothing;
    cin >> nothing; //keep terminal up until user closes program
    return 0;
}

int minimax(Board &b, int depth, int alpha, int beta, bool maximizingPlayer){

    if (depth == 0 || b.DetectGameOver())
    {
        return b.StaticEvaluation();
    }
    if (maximizingPlayer) //computer
    {
        int maxEval = -100000;
        b.playerTurn = false;
        vector<Move> possibleMoves = b.GetPossibleMoves('e'); //get possible moves for enemy
        for (Move x : possibleMoves)
        {
            b.MovePiece(x.row,x.col,x.direction);
            Board c = b;
            c.playerTurn = false;
            int eval = minimax(c, depth-1, alpha, beta, false);
            b.UndoMove();
            if (eval > maxEval)
            {
                maxEval = eval;
                b.bestMove.row = x.row , b.bestMove.col = x.col , b.bestMove.direction = x.direction;
            }
            if (alpha < eval)
                alpha = eval;
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else{ //player
        int minEval = 100000;
        b.playerTurn = true;
        vector<Move> possibleMoves = b.GetPossibleMoves('p'); //get possible moves for player
        for (Move x : possibleMoves)
        {
            b.MovePiece(x.row,x.col,x.direction);
            Board c = b;
            c.playerTurn = true;
            int eval = minimax(c, depth-1, alpha, beta, true);
            b.UndoMove();
            if (eval < minEval)
            {
                minEval = eval;
            }
            if (beta > eval)
                beta = eval;
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

void startGameInformation(){

    cout << "\n------------------------------"<<endl;
    cout << "| ANIMAL CHECKERS AI PROGRAM |"<<endl;
    cout << "| Created by: Evan Burdick   |"<<endl;
    cout << "| On: 1/28/2022              |"<<endl;
    cout << "------------------------------"<<endl<<endl<<endl;
}