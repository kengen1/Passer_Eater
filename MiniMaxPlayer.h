/*
	source code taken from lecture/ PASS session tictactoe file and repurposed for PasserEater Game
    - algorithm is not 100% effective in both player scenarios due to implementation issues
*/

#include "Player.h"

class MiniMaxPlayer : public Player{
    private:
        int steps;
        int size;

	int opponent(int symbol) {
		if(MiniMaxPlayer::player == 1){
            symbol = 1;
        }else { symbol = -1;}
        return symbol;
	}

    public:
    MiniMaxPlayer(int playerNo):Player(playerNo){
        steps = 100000;
    }
    ~MiniMaxPlayer(){

    }

    void getMove(Board* board, int& x, int& y) {
        size =board->getSize();

        vector<int> emptyCells = board->getEmptyPositions();
        if (emptyCells.empty())
            return;

        x = emptyCells[0] / size;
        y = emptyCells[0] % size;
        int max = -2;
        for (int index : emptyCells) {
            int i = index / size;
            int j = index % size;
			Board tempBoard(*board);
            tempBoard.addCompMove(i,j,player);
            int result = tempBoard.gameStatus();

            if(result != 0){
			if (result == MiniMaxPlayer::player) {
                x = i;
                y = j;
                return;
            } else if (result == opponent(MiniMaxPlayer::player)) {
                continue;
            }
           }
            int utility = minMove(tempBoard);
            if (utility > max) {
                x = i;
                y = j;
                max = utility;
            }
        }

        cout << "Minimax Utility = " << max << endl;

        return;
    }

    int maxMove(Board& board) {
    if (steps <= 0) return 0.01;
        vector<int> emptyCells = board.getEmptyPositions();
        if (emptyCells.empty())
            return -100;

        int maxUtility = -2;

        for (int index : emptyCells) {
            int i = index / size;
            int j = index % size;
			Board tempBoard(board);
            tempBoard.addCompMove(i, j,player);

			if (tempBoard.gameStatus() == MiniMaxPlayer::player) {
                return 1;
            }
            if (tempBoard.gameStatus() != MiniMaxPlayer::player) {
                return -1;
            }

            int utility = minMove(tempBoard);

            if (utility > maxUtility) {
                maxUtility = utility;
            }
        }

        steps--;
        return maxUtility;
    }

    int minMove(Board& board) {
        int size = board.getSize();

    if (steps <= 0) return 0.01;
        vector<int> emptyCells = board.getEmptyPositions();
        if (emptyCells.empty())
            return -100;

        int minUtility = 2;
        for (int index : emptyCells) {
            int i = index / size;
            int j = index % size;
			Board tempBoard(board);
            tempBoard.addCompMove(i, j,opponent(player));

		if (tempBoard.gameStatus() == MiniMaxPlayer::player)
			return 1;
		if (tempBoard.gameStatus() != MiniMaxPlayer::player)
			return -1;


            int utility = maxMove(tempBoard);
            if (utility < minUtility) {
                minUtility = utility;
            }
        }

        steps--;
        return minUtility;
    }
};