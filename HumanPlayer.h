#include "Player.h"

class HumanPlayer : public Player {
    public:
        HumanPlayer(int playerNo):Player(playerNo){}

        void getMove(Board* board,int& a, int& b){
            do{
                cout << "Enter [row] and [column] values: ";
                cin >> a >> b;
                a--; b--;
                if(!board->isValidMove(a,b,player))
                    cout << "Invalid move, please try again." << endl;
            }while(!board->isValidMove(a,b,player));
        }
};