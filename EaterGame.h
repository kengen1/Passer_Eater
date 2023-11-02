#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "Board.h"
#include "Player.h"
#include "MindfulPlayer.h"
#include "MiniMaxPlayer.h"
#include "RandomPlayer.h"
#include "SmartPlayer.h"
#include "StraightLinePlayer.h"
#include "HumanPlayer.h"
#include "MonteCarloPlayer.h"


using namespace std;

class EaterGame{
    private:
        int done;
        int player1;
        int player2;
    public:
        int boardSize;
        Board *board;
        Player *players[2];
        EaterGame();
        void play();
        void getGameType();
        bool isValid(int);
        int setSize();
        bool isValidSize(int);

};

EaterGame::EaterGame(){
    getGameType();
    setSize();
    board = new Board(boardSize);
    switch(player1) {
        case 1 :
            players[0] = new HumanPlayer(1);
            break;
        case 2:
            players[0] = new RandomPlayer(1);
            break;
        case 3:
            players[0] = new SmartPlayer(1);
            break;
        case 4:
            players[0] = new StraightLinePlayer(1);
            break;
        case 5:
            players[0] = new MiniMaxPlayer(1);
            break;
        case 6:
            players[0] = new MindfulPlayer(1);
        case 7:
            players[0] = new MonteCarloPlayer(1);
             break;
    }

    switch(player2) {
        case 1 :
            players[1] = new HumanPlayer(-1);
            break;
        case 2:
            players[1] = new RandomPlayer(-1);
            break;
        case 3:
            players[1] = new SmartPlayer(-1);
            break;
        case 4:
            players[1] = new StraightLinePlayer(-1);
            break;
        case 5:
            players[1] = new MiniMaxPlayer(-1);
            break;
        case 6:
            players[1] = new MindfulPlayer(-1);
        case 7:
             players[1] = new MonteCarloPlayer(-1);
             break;
    }

}

void EaterGame::play(){
    board->displayBoard();
    int a,b,x,y;
    done = 0;

    while(done == 0 && !board->isFull()){
        players[0]->getMove(board,a,b);
        players[1]->getMove(board,x,y);
        board->addMove(a,b,x,y);
        board->displayBoard();
        if(board->hasPath())
            done=1;
    }
        cout << "********* E N D G A M E   I N F O *********" << endl;
        if(board->hasPath()){
            cout << "A path has been made. Passer Wins!" << endl;
            board->displayPath();
        }else if(board-> isFull()){
            cout << "Board is full. Eater Wins!" << endl;
        }
        cout << "Number of moves:" << board->noOfMoves << "       " << "Full board: " << board->fullBoard << endl;

    delete players[0];
    delete players[1];
    delete board;

}

void EaterGame::getGameType(){
        cout << "         PASSER-EATER GAME       " << endl;
    do{
        cout << "=================================" << endl;
        cout << "[PASSER] : please select player type:" << endl;
        cout << "[1]    Human "<< endl;
        cout << "[2]    Random " << endl;
        cout << "[3]    Smart " << endl;
        cout << "[4]    Straight-line"<< endl;
        cout << "[5]    MiniMax"<< endl;
        cout << "[6]    Mindful"<< endl;
        cout << "[7]    MonteCarlo"<< endl;

        cin >> player1;
    }while(!isValid(player1));

    do{
        cout << "=================================" << endl;
        cout << "[Eater] : please select player type:" << endl;
        cout << "[1]    Human "<< endl;
        cout << "[2]    Random " << endl;
        cout << "[3]    Smart " << endl;
        cout << "[4]    Straight-line"<< endl;
        cout << "[5]    MiniMax"<< endl;
        cout << "[6]    Mindful"<< endl;
        cout << "[7]    MonteCarlo"<< endl;

        cin >> player2;
    }while(!isValid(player2));
}

bool EaterGame::isValid(int player){
    if(player >= 1 && player <= 7)
        return true;
    else{
        cout << "Invalid input, please try again." << endl;
        return false;
    }
}

int EaterGame::setSize(){
do{
    cout << "Enter board size you wish to play: ";
    cin >> boardSize;
}while(!isValidSize(boardSize));
    return boardSize;
}

bool EaterGame::isValidSize(int boardSize){
    if (boardSize >= 3 && boardSize <= 15){
        return true;
    } else {
        cout << "Invalid board size, please try again." << endl;
        return false;
    }
}