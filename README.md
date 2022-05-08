# Animal Checkers AI Program 
*By: Evan Burdick*

## Introduction
This is a player vs computer board game called Animal Checkers, which is a modified version of a Chinese game called Jungle. The computer
automatically operates it's turn using a backtracking decision-making algorithm called [minimax](https://en.wikipedia.org/wiki/Minimax). 

## Game Objective / Rules
The objective of the game is to capture the oponnent's den piece using one of the four animal pieces (elephant, tiger, wolf, mouse).
To start, you will be asked which player will go first (player or computer). 
Each turn, you can move one piece in an adjacent tile. You can capture opponent pieces by moving your piece on top of theirs, but each piece
is limited to what it can capture.

#### **Capture Logic:**
-Elephant can capture: elephant, tiger, wolf

-Tiger can capture: tiger, wolf, mouse

-Wolf can capture: wolf, mouse

-Mouse can capture: mouse, elephant

The game is finished once a player has sucessfully captured the oponent's den, or a player has successfully captured all of the oponent's pieces.

## How to compile / run
-compile and run file *driver.cpp*


## Using the Program
Upon first running the program, you are asked which user is going to go first. Enter in 'p' for player, or 'c' for computer.

### Player's Turn
On your turn, you are presented with the board state and are asked which piece to move. To do this, enter in the row, column, and direction respectively. For the row/column, enter in an integer cooresponding to the row/column legend. For the direction, enter in 'u' , 'd' , 'l' , or 'r' for up, down, left, and right, respectively. 

Demo:
![](https://github.com/EvanBurdick/AI-Animal-Checkers/blob/main/Demo/YourTurnDemo.gif)
### Computer's Turn
On the computer's turn, moves are done automatically. You can scroll up in the terminal to view the computer's decision.

## Minimax algorithm explanation (alpha/beta pruning)
