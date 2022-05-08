# Animal Checkers AI Program 
*By: @EvanBurdick*

## Introduction
This is a player vs computer board game called Animal Checkers, which is a modified version of a Chinese game called Jungle. The computer
automatically operates it's turn using a backtracking decision-making algorithm called [minimax](https://en.wikipedia.org/wiki/Minimax). The AI is set up so that it is impossible for the computer to lose. This can be modified by changing the depth count for the minimax function.

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

### Board Layout
The board includes 7 rows and 9 columns, which are labeled on the outside of the board, making for a total of 63 cells. Each piece is represented by a letter. Capital letters are the player's pieces, while lowercase letters represent the opponent's pieces.
- 'D/d' = Den
- 'E/e' = Elephant
- 'T/t' = Tiger
- 'W/w' = Wolf
- 'M/m' = Mouse

![Board Configuration](https://github.com/EvanBurdick/AI-Animal-Checkers/blob/main/Demo/BoardLayout.jpg)

### Player's Turn
On your turn, you are presented with the board state and are asked which piece to move. To do this, enter in the row, column, and direction respectively. For the row/column, enter in an integer cooresponding to the row/column legend. For the direction, enter in 'u' , 'd' , 'l' , or 'r' for up, down, left, and right, respectively. 

Demo:

![Turn Demo](https://github.com/EvanBurdick/AI-Animal-Checkers/blob/main/Demo/YourTurnDemo.gif)
### Computer's Turn
On the computer's turn, moves are done automatically. You can scroll up in the terminal to view the computer's decision.

## Minimax algorithm explanation (alpha/beta pruning)

Minimax is a recursion algorithm that searches for the move that will return the highest [static evaluation](https://en.wikipedia.org/wiki/Evaluation_function) of the board. A depth is set which indicates how deep the search will go (how many moves it will look ahead). The further the depth of the search, the "smarter" the play is, as well as the more time it takes to compute. The depth is 8 moves by default but that can be changed in the driver.cpp file.

The search works by first gathering a collection of possible moves to make. Then, it explores each of the moves, by then making a collection of moves the player could make in response. This continues to happen until the depth is met, in which it then returns the static evaluation of that move. 

My program uses a modified version of the minimax algorithm called the [alpha-beta pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning) method, which helps cut down computation time by abandoning search paths that are not worth exploring. 
