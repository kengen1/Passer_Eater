#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

#ifndef BOARD_h
#define BOARD_h

class Board{
private:
    int boardSize=0;
    int **board;
    bool** gameBoard;

public:
    int fullBoard;
    int noOfMoves = 0;

/* Constructors */
    Board(Board&);
    Board(int);
    ~Board();
	int getGrid(int i, int j) {
		return board[i][j];
	}

/* Board output functions */
    int getSize();
    void displayBoard();
    void displayPath();

/* Move input functions */
    void addMove(int, int, int, int);
    void addCompMove(int, int, int);
    bool isValidMove(int, int, int);
    bool isValidCompMove(int,int,int);

/* EaterGame rules */
    bool hasPath();
    bool isFull();
    int gameStatus();
    bool checkNeighbors(int, int);
    int threatenLevel(int);

    vector<int> getEmptyPositions();
    void getaRandomMove(int&, int&);
};

Board::Board(Board& b){
//COPY CONSTRUCTOR FOR: INT GAME BOARD FOR MOVE INPUTS
    boardSize = b.getSize();
    board = new int *[boardSize];
    for (int i=0; i < boardSize; i++)
        board[i] = new int[boardSize];

    for (int i=0; i < boardSize; i++)
        for (int j=0; j < boardSize; j++)
            board[i][j] = 0;

    for (int i=0; i < boardSize; i++)
        for (int j=0; j < boardSize; j++)
            board[i][j] = b.getGrid(i,j);

//COPY CONSTRUCTOR FOR : BOOL GAME BOARD FOR DISPLAYING A WINNING PATH
    gameBoard = new bool*[boardSize];
    for (int i=0; i < boardSize; i++)
        gameBoard[i] = new bool[boardSize];

    for (int i=0; i < boardSize; i++)
        for (int j=0; j < boardSize; j++)
            gameBoard[i][j] = false;
}

Board::Board(int size){
//INT GAME BOARD FOR MOVE INPUTS
    boardSize = size;
    board = new int *[boardSize];
    for (int i=0; i < boardSize; i++)
        board[i] = new int[boardSize];

    for (int i=0; i < boardSize; i++)
        for (int j=0; j < boardSize; j++)
            board[i][j] = 0;

//BOOLEAN GAME BOARD FOR PATH CHECKING AND DISPLAY
    gameBoard = new bool*[boardSize];
    for (int i=0; i < boardSize; i++)
        gameBoard[i] = new bool[boardSize];

    for (int i=0; i < boardSize; i++)
        for (int j=0; j < boardSize; j++)
            gameBoard[i][j] = false;
}

//Validating game state function
bool Board::isFull(){
    fullBoard = (boardSize)*(boardSize);
     if(noOfMoves == fullBoard){
        return true;
    }
    return false;
}

//return winning player based on two game rules
//function was built for Minimax + MonteCarlo players
int Board::gameStatus(){
    if(hasPath()){
        return 1;
    }
    if(isFull()){
        return -1;
    }
    return 0;
}

//used for all "Smart" AI players to know possible move states
vector<int> Board::getEmptyPositions(){
    vector<int> emptyCells;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == 0)
                emptyCells.push_back(i * boardSize + j);
        }
    }
	random_shuffle(emptyCells.begin(), emptyCells.end());

    return emptyCells;
}

void Board::getaRandomMove(int& x, int& y) {
	vector<int> emptyCells = getEmptyPositions();

	int index = rand() % emptyCells.size();
	x = emptyCells[index] / boardSize;
	y = emptyCells[index] % boardSize;
}

//separate function that calls recursive neighbour function
bool Board::hasPath(){
    for (int col = 0; col < boardSize; col++) {
        if (checkNeighbors(0,col))
                return true;
        }
            return false;
}

//recursive function that calls upon itself to form a continuous bool path statement
//separate bool game board is updated in this function to show a winning path
bool Board::checkNeighbors(int x, int y){
if (x < boardSize && y < boardSize && x >= 0 && y >= 0 && board[x][y] == 1) {
        gameBoard[x][y] = true;
        if (x >= boardSize - 1 && board[x][y] == 1){
            return true;
        }
            if (checkNeighbors(x + 1, y - 1)) { //down left
                gameBoard[x+1][y-1] = true;
                return true;
            }

            if (checkNeighbors(x + 1, y)) { //down
                gameBoard[x+1][y] = true;
                return true;
            }
            if (checkNeighbors(x + 1, y + 1)) { //down right
                 gameBoard[x+1][y+1] = true;
                return true;
            }

            if (checkNeighbors(x, y + 1)) { //check right
                gameBoard[x][y+1] = true;
                return true;
            }
    }

    return false;
}

//adds both passer and eater moves in a single function which makes it possible
//for an Eater move priority with minimal lines of code
//also increments the number of moves in a game
void Board::addMove(int a, int b, int x, int y){
    if(a == x && b == y){
        noOfMoves= noOfMoves+1;
    } else {
        noOfMoves = noOfMoves + 2;
    }
    board[a][b] = 1;
    board[x][y] = -1;

    cout << "[PASSER]: " << a+1 << " " << b+1 << " " << "[EATER]: " << x+1 << " " << y+1 << endl;

}

//simple validation for player moves
//called in getMove function from varying inherited Player classes
bool Board::isValidMove(int x, int y, int player){
    if (x >= 0 && x <= boardSize && y >= 0 && y <= boardSize && board[x][y] == 0){
        return true;
    } else return false;
}

//separate function that allows AI simulations to add moves from a single player
void Board::addCompMove(int x, int y, int player){
    if(!isValidCompMove(x,y,player)){
        return;
    }
    board[x][y] = player;
    noOfMoves++;
}

bool Board::isValidCompMove(int x, int y, int player){
    if (x >= 0 && x < boardSize && y >= 0 && y < boardSize && board[x][y] == 0){
        return true;
    } else return false;
}

//removing board object from memory
//called once the game is complete
Board::~Board(){
	for (int i = 0; i < boardSize; i++)
		delete[] board[i];
    delete[] board;
}

//function used by other classes to retrieve board size info
int Board::getSize(){
    return boardSize;
}


void Board::displayBoard(){
	for (int i = 0; i < boardSize; i++)
    if(i >= 10){
        cout << "  " << i+1 << " ";

    }else{
        cout << "   " << i+1 << " ";
    }    cout << endl;
    for (int i = 0; i < boardSize; i++)
        cout << " ----";
    cout << endl;
	for (int i = 0; i < boardSize; i++) {
        cout << i+1;
		for (int j = 0; j < boardSize; j++) {
			char playerSymbol = ' ';
			if (board[i][j] == 1)
				playerSymbol = 'P';
			else if (board[i][j] == -1)
				playerSymbol = 'E';
			cout << setw(3) << playerSymbol;
            if (j != boardSize-1)
			    cout << " |";
        }
    	cout << endl ;
            for (int i = 0; i < boardSize; i++){
                cout << " ----";
            }
        cout << endl;
    }
	cout << endl;
}

void Board::displayPath(){
	for (int i = 0; i < boardSize; i++)
    if(i >= 10){
        cout << "  " << i+1 << " ";

    }else{
        cout << "   " << i+1 << " ";
    }
    cout << endl;
    for (int i = 0; i < boardSize; i++)
        cout << " ----";
    cout << endl;
	for (int i = 0; i < boardSize; i++) {
        cout << i+1;
		for (int j = 0; j < boardSize; j++) {
			char playerSymbol = ' ';
			if (gameBoard[i][j] == true)
				playerSymbol = '*';
			else if (gameBoard[i][j] == false)
				playerSymbol = ' ';
			cout << setw(3) << playerSymbol;
            if (j != boardSize-1)
			    cout << " |";
        }
    	cout << endl ;
            for (int i = 0; i < boardSize; i++){
                cout << " ----";
            }
        cout << endl;
    }
	cout << endl;
}

int Board::threatenLevel(int playerNo) {
	int max = 0;
    int opponent =0;
    if(playerNo == 1){
        opponent = -1;
    } else opponent = 1;

	for (int row = 0; row < boardSize; row++) {
		int counter = 0;
		for (int col = 0; col < boardSize; col++) {
			if (board[row][col] == playerNo) {
				counter = 0;
				break;
			} else if (board[row][col] == opponent)
				counter++;
		}
		if (counter > max)
			max = counter;
	}

	for (int col = 0; col < boardSize; col++) {
		int counter = 0;
		for (int row = 0; row < boardSize; row++) {
			if (board[row][col] == playerNo) {
				counter = 0;
				break;
			} else if (board[row][col] == opponent)
				counter++;
		}
		if (counter > max)
			max = counter;
	}

	int counter = 0;
	for (int k = 0; k < boardSize; k++) {
		if (board[k][k] == playerNo) {
			counter = 0;
			break;
		} else if (board[k][k] == opponent)
			counter++;
	}
	if (counter > max)
		max = counter;

	counter = 0;
	for (int k = 0; k < boardSize; k++) {
		if (board[k][2-k] == playerNo) {
			counter = 0;
			break;
		} else if (board[k][2-k] == opponent)
			counter++;
	}
	if (counter > max)
		max = counter;

    return max;
}

#endif //BOARD_h