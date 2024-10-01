The project was created for the purpose of passing the project part of the Algorithms and Data Structures course in the second semester of studies. 
The goal of the project was to write an engine for the gipf game in c++.
I will enter test cases with input and expected output files to test the program.

The program responds to several commands that the user enters. To test the program enter inputs that i will upload to this project and check them with the expected output files.
Now i will describe the commands to which the program responds:

*LOAD_GAME_BOARD 
Followed by the game parameters and the state of the board.
Let's take a look at the numbers we entered at the beginning in the first two lines of input right after entering the LOAD_GAME_BOARD command:
  - The first number is the length of the side of our board (hexagon)
  - The second number is number of player pieces that trigger the collection of pieces.
  - The third number is number of pieces belonging to the white player, which must be greater than the three pieces initially placed on the board for the player.
  - The fourth number is the number of pieces belonging to the black player.
In the second line we have number of pieces that are actually in white reserve, black reserve (initially, we awarded players 15 pieces, of which 3 are already on the board, so they
already have 15-3 = 12 pieces in reserve) and the last character is the player which start the game.
This command already check if board that you enter correspond correctly to the parameters entered at the beggining (check test 0) if you e.g. enter that the size of hexagon shoud be 3 but you upload board with size 4 program will print "WRONG_BOARD_ROW_LENGTH".

*PRINT_GAME_BOARD
Prints the current state of the board. After loading the game, it should be exactly the same as the printout provided during loading,
assuming it was valid if not then program will inform you that board does not exist.

*DO_MOVE <xN - yM> (command before it makes a stone move checks a lot of cases if the movement can be done correctly for better understanding test it with a given input tests 2-5)
Performs the given move for the active player on the current board. The move notation should be consistent with the notation used in the Gipf for One (GF1) program. If the move is valid, a new board will be generated, and the active player will switch to the opponent. The game may end if the opponent no longer has any reserve pieces. If the move is invalid, the appropriate game state should be established as "bad_move," and the player and move that caused this state should be remembered. In cases where a player needs to remove pieces from the board and there are multiple possibilities, he must decide which pieces he want to remove. This information must be added to the command in the form of coordinates for those pieces.
Therefore, in the case of a move that leads to an ambiguous situation requiring clarification of which pieces should be removed, the command includes the color of the player for whom the choice applies, followed by a sequence of coordinates specifying the removed pieces. The command will look as follows:
DO_MOVE <xN - yM> [w:|b:]x1 xn ...
If there are multiple choices, they will be provided as subsequent sequences of indexes.

*GEN_ALL_POS_MOV (test 6a)
Prints list of all possible moves (without repetitions) leading to unique board states.

*GEN_ALL_POS_MOV_NUM (test 6) 
Prints the number of all moves obtained as a result of the GEN_ALL_POS_MOV command.


