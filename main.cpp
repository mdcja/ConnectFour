/*
Julian Martinez del Campo

main file for connect four game
*/

// include headers
#include <iostream>
#include <iomanip>
#include "connect.h"         // include header file for custom functions

using namespace std;

// Main
int main(){
    // variables
    Board game;
    bool again = true;      // play again, true or false
    int state = 0;
    int wins = 0;
    int losses = 0;
    int total = 0;
    
    // check game is played, and if user wants to play again
    while( again == true ){
        state = playGame( game );
        again = playAgain(); 
        // add totals 
        if( state == 0 ){
            total++;
        }
        // if win then add win
        else if( state == 1 ){
            wins++;
            total++;
        }
        // if loses then add lose
        else if( state == 2 ){
            losses++;
            total++;
        }
    }
    // display info to user
    cout << endl;
    cout << "You played " << total << " times." << endl;
    cout << "You won " << wins << " times." << endl;
    cout << "The computer won " << losses << " times." << endl;

    return 0;
}
