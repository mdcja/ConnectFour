/*
Julian Martinez del Campo

Function file for connect 4 game
*/


#include <iostream>     // input/output libs
#include <iomanip>      // input/output manipulation libs
#include <cstdlib>      // for random function generator
#include <time.h>       // for random function generator
#include "connect.h"         // prototype file for connect four game

using namespace std;

/*
void create( Board &game );
params: board <- pass a board to function
pre: board does not exist
post: board is created and initialized
*/
void create( Board &game ){
    int i, j;
    // fill board
    for( i = 0 ; i < ROWS ; i++ ){
        for( j = 0 ; j < COLS ; j++ ){
            game.board[i][j] = 'O' ;
        }
    }
}

/*
void display( Board game );
params: board <- the game board is passed 
pre: board exists
post: board is displayed
*/
void display( Board game ){
    int i, j , k;
    
    cout << endl;
    // row
    for( i = 0 ; i < ROWS ; i++ ){
        // start printing 10 characters over
        cout << setw(10);
        // column
        for( j = 0 ; j < COLS ; j++ ){
            cout << game.board[i][j] ;
            // print one less "|"
            if( j < COLS - 1 )
                cout << " | ";
        }
        // newline
        cout << endl;
        // print one less line of "-"
        if( i < ROWS - 1 ){
            // line
            // start printing 10 characters over
            cout << setw(10);
            for( k = 0 ; k < 13 ; k++ ){
                cout << "-" ;
            }
            cout << endl;
        }
    }
    cout << endl << endl;
    // print slot names
    cout << "Columns: " ;
    cout << "A" << "   " ;
    cout << "B" << "   " ;
    cout << "C" << "   " ;
    cout << "D";
}

/*
void chooseColor( Board &game );
params: board <- game board is passed 
pre: board exists
post: player color is assigned to board
*/
void chooseColor( Board &game ){
    char color;

    cout << endl << endl;
    // if user input is 'y' or 'n' allow function to continue
    do{
        // prompt user
        cout << "What color would you like to be?" << endl;
        cout << "Yellow (Y) or Red (R)" << endl;
        // get color
        cin >> color;
        // make sure input is uppercase
        color = toupper( color );
    }while( !(color == 'Y' || color == 'R') ); 

    cout << endl;

    // set player turn
    game.playerTurn = 0;

    // assign color
    if( color == 'Y' ){
        game.player[0] = 'Y';
        game.player[1] = 'R';
    }
    else{
        game.player[0] = 'R';
        game.player[1] = 'Y';
    }
}

/*
bool isValid( Board game, int slot );
params: board <- game board is passed
        slot <- the column number to drop tokien
pre: board exists
post: if slot free return true
      else return false
*/
bool isValid( Board game, int col ){
    if( game.board[0][col] == 'O' ){
        return true;
    }
    else{
        return false;
    }
}

/*
int whichRow( Board game, int slot );
params: game <- game board is passed 
        slot <- slot number of board to check
pre: board exists
     slot is free
post: return which row is free
*/
int whichRow( Board game, int col ){
    int i;
    // count how many rows are free
    for( i = 0; game.board[i][col] == 'O' && i  < ROWS ; i++ ){}
    // return rows free    
    return i-1;
}

/*
void move( Board &game );
params: game <- game board is passed
pre: none
post: player moves
      return 0 if no connect 4 or board is not full
      return 1 if board is full
      return 2 if connect four
*/
int move( Board &game ){
    // variables
    char slot;
    int row, col;
    bool moved = false; 
    bool full = false;
    bool connectFour = false;

    cout << endl;   // formatting newline
    
    do{
        // set variables
        getSlot( slot );
        col = slotToNum( slot );
        
        // if the move is valid
        if ( isValid( game, col ) ){
            // get row number
            row = whichRow( game, col );
            // move player on board
            game.board[row][col] = game.player[game.playerTurn];
            // return true
            moved = true;
        }
        else{
            // ask for a valid column
            cout << "That move is not valid" << endl;
            cout << "Please choose another column!" << endl;
            // moved is still equal to false
        }
    }while( moved  == false );

    // check board to see if it is full
    // or if connect four
    full = isFull( game );
    connectFour = isConnect( game );

    // switch players
    switchPlayer( game );

    // set return codes
    if( full )
        return 1;
    else if( connectFour )
        return 2;
    else
        return 0;
}

/*
int moveComputer( Board &game );
params: game <- pass game board
pre: board exists
post: computer moves
      return 0 if no connect 4 or board is not full
      return 1 if board is full
      return 2 if connect four
*/
int moveComputer( Board &game ){
    // set variables
    int row, col;
    bool moved = false; // has computer moved
    bool full = false; // is board full
    bool connectFour = false; // is connect four

    do{
        // chose a random column number
        col = randNum( COLS );
        
        // check to see if move is valid
        if ( isValid( game, col ) ){
            // move
            row = whichRow( game, col );
            game.board[row][col] = game.player[game.playerTurn];
            // display computer move 
            cout << endl << "The computer places a token in column " << col+1 << endl;
            moved = true; // set moved equal to true
        }
    }while( moved == false );
    
    // check for full board or connect four
    full = isFull( game );
    connectFour = isConnect( game );
    
    // switch player
    switchPlayer( game );

    // return codes
    if( full )
        return 1;
    else if( connectFour )
        return 2;
    else
        return 0;


}

/*
int randNum( int ceil );
params: ceiling number <- max number
pre: none
post: random number is returned between 0 and 
        cieling number.
*/
int randNum( int ceil ){
   
    // Seed random number with time
    // Declare variable to hold seconds on clock.
    time_t seconds;
    // Get value from system clock and place in seconds variable.
    time(&seconds);
    // Convert seconds to a unsigned integer.
    srand((unsigned int) seconds);

    // return random number between 0 and ciel
    return rand() % ceil;
}

/*
void switchPlayer( Board &game );
params: game <- pass game board
pre: game exists <- game board exists
post: player is switched
*/
void switchPlayer( Board &game ){
    // swap players
    // if player 0 then change to 1
    // if player 1 then change to 0
    if( game.playerTurn == 0 )
        game.playerTurn = 1;
    else if( game.playerTurn == 1 )
        game.playerTurn = 0;
    else
        cout << "Could not switch players" << endl;
}

/*
int slotToNum( char slot );
params: slot character
pre: none
post: return slot number
*/
int slotToNum( char slot ){
    int col;
    // check to see if slot is eqal to A,B,C,D
    if( slot == 'A' )
        col = 0;
    else if( slot == 'B' )
        col = 1;
    else if( slot == 'C' )
        col = 2;
    else if( slot == 'D' )
        col = 3;
    else
        cout << "could not convert column to number" << endl;
    
    // return column number
    return col;
}

/*
void getSlot( char &slot );
params: slot character <- slot charcter input
pre: none
post: a valid column is chosen from std input
*/
void getSlot( char &slot ){
    do{
        cout << "Choose a column: " ;
        cin >> slot;
        cout << endl;
        slot = toupper( slot );
    }while( !( slot == 'A' || slot == 'B' || slot == 'C' || slot == 'D' ) );
}

/*
bool isFull( Board game );
params: game <- game board is passed
pre: game exists
post: return true if board is full
      else return false
*/
bool isFull( Board game ){
    // variables
    int i, sum;
    int full[COLS]; // truth array
    // check top row for valid move
    // fill truth array
    for( i = 0 ; i < COLS; i++ ){
        if( game.board[0][i] != 'O' )
            full[i] = 1;
        else
            full[i] = 0;
    }
    // get sum of array
    for( sum = 0, i = 0; i < COLS ; i++ ){
        sum += full[i];
    }
    // if sum is euqal to the number of columns
    // board is full
    // set return values
    if( sum == COLS )
        return true;
    else
        return false;
}

/*
void fillTable( Board game, int table[ROWS][COLS] );
params: board, table
pre: none
post: a truth table is filled
*/
/*
void fillTable( Board game, int table[ROWS][COLS] ){
    int i,j;

    for( i = 0 ; i < ROWS ; i++ ){
        for( j = 0 ; j < COLS ; j++ ){
            if( game.board[i][j] == game.player[game.playerTurn] )
                table[i][j] = 1;
            else
                table[i][j] = 0;
        }
    }

}
*/

/*
bool connectRow( Board game );
params: board <- pass game board
pre: board is initialized
post: if four in a row return true
      else return false
*/
bool connectRow( Board game ){
    // variables
    int i,j;
    int table[ROWS][COLS];
    int sum[ROWS];
    bool connect;
    // check row 
    for( i = 0 ; i < ROWS ; i++ ){
        // check column
         for( j = 0 ; j < COLS ; j++ ){
            // if no character is there 0 // so total sum = 0
            // if player 1 set 1 
            //     total = number of columns
            // if player 2 set 5 
            //     total = no. of cols. , 
            //      set player to number greater than sum of player 1 to
            //      differentiate between players

            if( game.board[i][j] == 'O' )
                table[i][j] = 0;
            else if( game.board[i][j] == game.player[game.playerTurn] )
                table[i][j] = 1;
            else
                table[i][j] = 5;
        }
    }
    // get sums of each row from truth table for player 1
    for( i = 0 ; i < ROWS ; i++ ){
        // add each column of row
        for( sum[i] = 0, j = 0 ; j < COLS ; j++ ){
            sum[i] += table[i][j];
        }
    }
    //get sums of each row from truth table for player 2
    for( i = 0 ; i < ROWS ; i ++ ){
        // if connect return true and exit loop
        if( sum[i] == 5*COLS || sum[i] == COLS ){
            connect = true;
            break;
        }
        else{
            connect = false;
        }
    }
    // return value of connect
    return connect;
}

/*
bool connectCol( Board game );
params: board <- pass game board
pre: none
post: if four in a col return true
      else return false
*/
bool connectCol( Board game ){
    // variables
    int i,j;
    int table[ROWS][COLS];
    int sum[COLS];
    bool connect;
    // for each column
    for( i = 0 ; i < COLS ; i++ ){
        // check rows
        for( j = 0 ; j < ROWS ; j++ ){
            // fill truth tables
            if( game.board[i][j] == 'O' )
                table[i][j] = 0;
            else if( game.board[i][j] == game.player[game.playerTurn] )
                table[i][j] = 1;
            else
                table[i][j] = 5;
        }
    }
    // get sums of each column and full sum array
    for( i = 0 ; i < COLS ; i++ ){
        for( sum[i] = 0, j = 0 ; j < ROWS ; j++ ){
            sum[i] += table[j][i];
        }
    }
    // check for connect
    for( i = 0 ; i < COLS ; i ++ ){
        if( sum[i] == 5*ROWS || sum[i] == ROWS ){
            connect = true;
            break;
        }
        else{
            connect = false;            
        }
    }
    return connect;
}

/*
bool connectDiag( Board game );
params: board <- pass game board
pre: none
post: if connect diagonally return true
      else return false
*/
bool connectDiag( Board game ){
    // variables
    int i,j;
    int table[ROWS][COLS]; // truth table
    int sum[2]; // sums of diagonals
    bool connect;
    // fill truth table
    for( i = 0 ; i < ROWS ; i++ ){
        for( j = 0 ; j < COLS ; j++ ){
            if( game.board[i][j] == 'O' )
                table[i][j] = 0;
            else if( game.board[i][j] == game.player[game.playerTurn] )
                table[i][j] = 1;
            else
                table[i][j] = 5;
        }
    }

    // add sums of diagonal left
    for( sum[0] = 0, i = 0 ; i < ROWS ; i++ ){
        sum[0] += table[i][i];
    }

    // add for diag right
    for( sum[1] = 0, i = 0 ; i < ROWS ; i++ ){
        sum[1] += table[i][(ROWS-1)-i];
    }

    // check diagonals 
    for( i = 0 ; i < 2 ; i ++ ){
        // if turue then connect four
        if( sum[i] == 5*ROWS || sum[i] == ROWS ){
            connect = true;
            break;
        }
        else{
            connect = false;            
        }
    }
    // return connect four
    return connect;
}

/*
bool isConnect( Board game );
params: board <- pass game board
pre: none
post: if there is four in a row/col/diagonally return true
      else return false
*/
bool isConnect( Board game ){
    // check for all types of connects
    if( connectRow( game ) ){
        return true;
    }
    else if( connectCol( game ) ){
        return true;
    }
    else if( connectDiag( game )){
        return true;
    }
    else{
        return false;
    }
}

/*
int playGame( Board game );
params: board <- pass game board
pre: none
post: game is played 
      return 1 if player wins
      return 2 if computer wins
      return 0 if nobody wins
*/
int playGame( Board game ){
    // intialize state to zeros
    // state = which player return code, for both players 
    int state[2] = {0,0};

    create( game );
    chooseColor( game );
    display( game );
    
    // while both players can move
    while( state[0] == 0 || state[1] == 0 ){
        // move
        state[0] = move( game );
        if( state[0] != 0 )
            break;
        // computer move
        state[1] = moveComputer( game );
        if( state[1] != 0 )
            break;
        // show board
        display( game );
    }

    cout << endl;
    
    // set return codes for moves
    // player
    if( state[0] == 1 ){
        cout << "No more moves are possible" << endl;
        cout << "Nobody wins" << endl;
        return 0;
    }
    else if( state[0] == 2 ){
        cout << "Connect four!" << endl;
        cout << "You (" << game.player[0] << ") win!" << endl;
        return 1;
    }
    // computer
    else if( state[1] == 1 ){
        cout << "No more moves are possible" << endl;
        cout << "Nobody wins" << endl;
        return 0;
    }
    else if( state[1] == 2 ){
        cout << "Connect four!" << endl;
        cout << "Computer (" << game.player[1] << ") wins!" << endl;
        return 2;
    }

}

/*
bool playAgain( void );
params: none
pre: none
post: return true if play game again
      else return false

*/
bool playAgain( void ){
    char choice;
    do{
        // prompt user
        cout << "Would you like to play again?" << endl;
        cout << "(y)es, (n)o" << endl;
        // get input
        cin >> choice;
        // set input to uppercase
        choice = toupper(choice);
        // check for valid choice
    }while( !(choice == 'Y' || choice == 'N') ); 

    // set return values 
    if( choice == 'Y' )
        return 1;
    else
        return 0;
}
