/*
Julian Martinez del Campo

header file for connect 4 game
*/

// preprocessor directives
// check if header file has been
#ifndef _TA_H
#define _TA_H

// constants
const int ROWS = 4;
const int COLS = 4;

// board
struct Board{
    char board[ROWS][COLS];
    char player[2];
    int playerTurn;
};

// Function protytpes

/*
void create( Board &game );
params: board <- pass a board to function
pre: board does not exist
post: board is created and initialized
*/
void create( Board &game );

/*
void display( Board game );
params: board <- the game board is passed 
pre: board exists
post: board is displayed
*/
void display( Board game );

/*
void chooseColor( Board &game );
params: board <- game board is passed 
pre: board exists
post: player color is assigned to board
*/
void chooseColor( Board &game );

/*
bool isValid( Board game, int col );
params: board <- game board is passed
        slot <- the column number to drop tokien
pre: board exists
post: if slot free return true
      else return false
*/
bool isValid( Board game, int col );

/*
int whichRow( Board game, int col );
params: game <- game board is passed 
        slot <- slot number of board to check
pre: board exists
     slot is free
post: return which row is free
*/
int whichRow( Board game, int col );

/*
void move( Board &game );
params: game <- game board is passed
pre: none
post: player moves
      return 0 if no connect 4 or board is not full
      return 1 if board is full
      return 2 if connect four
*/
int move( Board &game );

/*
int moveComputer( Board &game );
params: game <- pass game board
pre: board exists
post: computer moves
      return 0 if no connect 4 or board is not full
      return 1 if board is full
      return 2 if connect four
*/
int moveComputer( Board &game );

/*
int randNum( int ceil );
params: ceiling number <- max number
pre: none
post: random number is returned between 0 and 
        cieling number.
*/
int randNum( int ceil );

/*
void switchPlayer( Board &game );
params: game <- pass game board
pre: game exists <- game board exists
post: player is switched
*/
void switchPlayer( Board &game );

/*
int slotToNum( char slot );
params: slot character
pre: none
post: return slot number
*/
int slotToNum( char slot );

/*
void getSlot( char &slot );
params: slot character <- slot charcter input
pre: none
post: a valid column is chosen from std input
*/
void getSlot( char &slot );

/*
bool isFull( Board game );
params: game <- game board is passed
pre: game exists
post: return true if board is full
      else return false
*/
bool isFull( Board game );

//void fillTable( Board game, int table[ROWS][COLS] );

/*
bool connectRow( Board game );
params: board <- pass game board
pre: board is initialized
post: if four in a row return true
      else return false
*/
bool connectRow( Board game );

/*
bool connectCol( Board game );
params: board <- pass game board
pre: none
post: if four in a col return true
      else return false
*/
bool connectCol( Board game );

/*
bool connectDiag( Board game );
params: board <- pass game board
pre: none
post: if connect diagonally return true
      else return false
*/
bool connectDiag( Board game );

/*
bool isConnect( Board game );
params: board <- pass game board
pre: none
post: if there is four in a row/col/diagonally return true
      else return false
*/
bool isConnect( Board game );

/*
int playGame( Board game );
params: board <- pass game board
pre: none
post: game is played 
      return 1 if player wins
      return 2 if computer wins
      return 0 if nobody wins
*/
int playGame( Board game );

/*
bool playAgain( char &choice );
params: user choice <- char value of input
pre: none
post: return true if play game again
      else return false

*/
bool playAgain( void );

#endif  // end prepocessor directive
