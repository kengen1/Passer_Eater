#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "Board.h"

#ifndef PLAYER_h
#define PLAYER_h

using namespace std;

class Player {
    protected:
        int player;
    public:
        Player(int playerNo){
            player = playerNo;
        }
        virtual void getMove(Board*,int&,int&)=0;
};

#endif //PLAYER_h