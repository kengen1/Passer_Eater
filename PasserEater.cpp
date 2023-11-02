#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

#include "Board.h"
#include "EaterGame.h"

void playAgain();

int main(){
    srand(time(0));
    EaterGame Game;     //construct a EaterGame object, this subsequently constructs the Board and Players
    Game.play();        //run the play function from EaterGame class
    playAgain();

    //ask user to ply again
    //if statement

    return 0;           //primary functions for the program to run are all nested in the game class for abstraction purposes.
}

void playAgain(){
    cout << endl << "Would you like to play again? [y][n]";
    char playAgain;
    cin >> playAgain;

    if(playAgain == 'y' || playAgain == 'Y'){
        main();
    }
}

