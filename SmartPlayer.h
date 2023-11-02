/*
    this player class acts as a slightly more intelligent version of the random player
    in which the likelihood of making a good move increases as the game progresses due to the
    AI knowing where empty cells are
*/

#include "Player.h"

class SmartPlayer : public Player {
    private:
        int* index;
    public:
        SmartPlayer(int playerNo):Player(playerNo){}

        void getMove(Board* board,int& x, int& y) {
            int row,col;

            int size = board->getSize();
            vector<int> emptyCells = board->getEmptyPositions();
            do{
                if(emptyCells.size() == 0){
                    return;
                }
                int index = rand() % emptyCells.size();
                row = emptyCells[index] / size;
                col = emptyCells[index] % size;
            }while(!board->isValidMove(row,col,player));
            x=row;
            y=col;
        }
};