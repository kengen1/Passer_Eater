/*
	source code taken from lecture/ PASS session tictactoe file and repurposed for PasserEater Game
	slight upgrade from "Smart Player" that uses a temp board to simulate random move inputs
*/
#include "Player.h"

class MindfulPlayer : public Player {
    public:
        MindfulPlayer(int playerNo):Player(playerNo){}

	void getMove(Board* board, int& x, int& y) {
        int size = board->getSize();

		vector<int> emptyCells = board->getEmptyPositions();
		if (emptyCells.empty())
			return;

		for (int index : emptyCells) {
			int i = index / size;
			int j = index % size;
			Board tempBoard = Board(size);

			x = i;
			y = j;

			tempBoard.addCompMove(x, y, player);
			if (tempBoard.hasPath()) {
				return;
			}else if(tempBoard.isFull()){
                return;
            }

			if (tempBoard.threatenLevel(player) == 2)
				continue;

		}
	}
};