/*
    Player will start at 1*1 and make a vertical line.
    once prevented from making that line it will move to the next column.
*/
#include "Player.h"

class StraightLinePlayer : public Player {
    public:
        StraightLinePlayer(int playerNo):Player(playerNo){}

        void getMove(Board* board, int& x, int& y){
            //int size = board -> getSize() / 2; *if you want the player to start in the middle of the board
            y = 0;
            do {
                x++;
                if(x == board->getSize()){
                    x = 0;
                    y++;
                }
            }while(!board->isValidMove(x,y,player));
        }
};