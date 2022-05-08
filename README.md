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


## How to compile / run
-compile and run file *driver.cpp*

## Minimax algorithm explanation (alpha/beta pruning)
