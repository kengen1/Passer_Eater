#include "Player.h"

class RandomPlayer : public Player{
    private:
    public:
        RandomPlayer(int playerNo):Player(playerNo){}

        void getMove(Board* board, int&x, int&y) {
            if(board->isFull()){
                return;
            }
            do{
                board->getaRandomMove(x,y);
            }while(!board->isValidMove(x,y,player));
        }
};