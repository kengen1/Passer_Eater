/*
	source code taken from lecture/ PASS session tictactoe file and repurposed for PasserEater Game
    AI returns a utility score based on a number of simulations conducted with copy constructor boards
    it will play itself as both the passer and the eater and can return the best move when playing
    the actual game as a passer or eater.
*/

#include "Player.h"

#ifndef MONTECARLOPLAYER_H_
#define MONTECARLOPLAYER_H_

const int TIMES = 500;

class MonteCarloPlayer : public Player{
    private:
        int size;
    public:
        MonteCarloPlayer(int playerNo):Player(playerNo){}

        void getMove(Board* board, int& x, int& y){
            vector<int> emptyCells =board->getEmptyPositions();
            size = board->getSize();

            if (emptyCells.empty())
                return;

            double maxUtility = -1.0;

            for (int index : emptyCells) {
                int i = index / size;
                int j = index % size;
			    Board tempBoard(*board);

                tempBoard.addCompMove(i, j, player);

                double utility = simulation(tempBoard);

                if (utility > maxUtility) {
                    maxUtility = utility;
                    x = i;
                    y = j;
                }
            }
		//cout << "Monte Carlo Utility = " << maxUtility  << endl;

            return;
        }

        double simulation(Board board) {
            double winning = 0.0;

            for (int i = 0; i < TIMES; i++) {
                Board tempBoard(board);
                winning += expansion((player == 1) ? -1 : 1, tempBoard);
            }

            return winning/TIMES;
        }



        double expansion(int player, Board board) {

            if(board.gameStatus() != 0){
            if (board.gameStatus() == MonteCarloPlayer::player) {
                return 1;
            } else if (board.gameStatus() != MonteCarloPlayer::player) {
                return -1;
            }
            }

            vector<int> emptyCells = board.getEmptyPositions();
            if(emptyCells.empty())
                return 0;
            int index = emptyCells[rand() % emptyCells.size()];

            int x = index / size;
            int y = index % size;

            board.addCompMove(x, y, player);

            player = (player == 1) ? -1 : 1;

            return expansion(player, board);
        }

};

#endif /* MONTECARLOPLAYER_H_ */
