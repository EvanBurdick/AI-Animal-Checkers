//Board.h
//Created by: Evan Burdick
//1/28/2022
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

class Move{ //This class is used for storing move information
public:
    int row, col;
    char direction;
};
class LastMoveInfo{ //This class is used to store the last move information
public:
    int startPositionRow, startPositionCol;
    char startPositionValue;

    int endPositionRow, endPositionCol;
    char endPosiotionValue;
};

class Board{
public:
    bool playerTurn = true;
    vector<vector<char>> boardVect
    {
        {' ', 'm', ' ', 'd', ' ', 'e', ' '},
        {' ', ' ', 't', ' ', 'w', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', 'W', ' ', 'T', ' ', ' '},
        {' ', 'E', ' ', 'D', ' ', 'M', ' '}
    };
    Move bestMove;
    LastMoveInfo lastMoveInfo;
    void PrintBoard(); //prints out the current board state 
    int StaticEvaluation(); //returns the value of hte board state (positive number indicates computer is ahead)
    void MovePiece(int, int, char); //moves a piece at given location and direction
    void UndoMove(); //undoes the last move made
    bool IsLegalMove(int, int, char); //returns true is the attempted move is legal
    bool DetectGameOver();  //returns true if the game is over
    void DetermineWinner(); //prints out the winner of the game
    vector<Move> GetPossibleMoves(char); //returns a vector of the possible moves for given player

    void operator = (const Board &B ) { //overloads assignment operator to allow board copies
        boardVect = B.boardVect;
    }
};
#include "Board.cpp"
#endif