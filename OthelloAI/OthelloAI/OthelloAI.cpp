
// Othello AI Player - Academic Project
// Play Othello against an AI that uses Monte Carlo tree search 
// to determine it's next move, with choice of 
// simple AI (No heuristics) or smart AI (with heuristics)

#include "iostream"
#include "string"
#include "math.h"
#include "vector"
#include "map"
#include "limits"
#include "random"
#include "ctime"

using namespace std;

// global variables
const int boardX = 8;
const int boardY = 8;

// for raw value
const int p1Num = 1;
const int p2Num = 2;

// for printing
const string player1 = "O";
const string player2 = "X";

// moves
map<char, int> moveX;

void mapInit() {
	// for indexing from letter -> value (ex. a -> 0)
	string alph = "abcdefgh";
	for (int i = 0; i < 8; i++) {
		moveX.insert(pair<char, int>(alph.at(i), i));
	}

	return;
}

void printBoard(int** board) {

	int length = 8;

	cout << "	   a b c d e f g h" << endl;
	cout << "	   _______________" << endl;

	for (int y = 0; y < boardX; y++) {
		cout << "	" << y + 1 << " |";
		for (int x = 0; x < boardY; x++) {
			int cell = board[x][y];

			if (cell == -1) {
				cout << "- ";
			}
			else {
				if (cell == p1Num) {
					cout << player1 + " ";
				}
				if (cell == p2Num) {
					cout << player2 + " ";
				}
			}

		}
		cout << endl;
	}
	cout << endl;


	return;
}

bool checkCellIsPlayer(int** board, int startX, int startY, int displaceX, int displaceY, string player) {
	// check the next cell 
	// true if cell == player
	// else false
	bool result = false;

	int x = startX + displaceX;
	int y = startY + displaceY;

	// check if borders
	if ((x < 0) || (x >= boardX)) {
		return false;
	}
	if ((y < 0) || (y >= boardY)) {
		return false;
	}

	// check if cell is player
	int nextCell = board[x][y];
	int piece;

	if (player == player1) {
		piece = p1Num;
	}
	else {
		piece = p2Num;
	}
	if (nextCell == piece) {
		result = true;
	}

	return result;
}

bool checkCellIsEmpty(int** board, int x, int y) {
	bool empty = false;

	// check borders
	if ((x < 0) || (x >= boardX)) {
		return false;
	}
	if ((y < 0) || (y >= boardY)) {
		return false;
	}

	if (board[x][y] == -1) {
		empty = true;
	}

	return empty;
}

void placePiece(int** board, int x, int y, string player) {
	int piece = -1;

	if (player == player1) {
		piece = p1Num
			;
	}
	else {
		if (player == player2) {
			piece = p2Num;
		}
	}

	board[x][y] = piece;
}

int* stringToCoord(string stringCoord) {
	int* coord = new int[2];
	char xFrag = tolower(stringCoord[0]);
	char yFrag = stringCoord[1];

	int xCoord = moveX.at(xFrag);
	int yCoord = yFrag - '0' - 1;

	coord[0] = xCoord;
	coord[1] = yCoord;

	return coord;
}

string coordToString(int x, int y) {
	string alph = "abcdefgh";

	return  string(1, alph.at(x)) + to_string(y + 1);
}

void coordCorrectionStart(string direction, int* x, int* y) {
	// used to find starting cell in possibleMoves
	if (direction == "UP") {
		int displaceX = 0;
		int displaceY = -1;
		*x = *x - displaceX;
		*y = *y - displaceY;
	}
	if (direction == "UPRIGHT") {
		int displaceX = 1;
		int displaceY = -1;
		*x = *x - displaceX;
		*y = *y - displaceY;
	}
	if (direction == "RIGHT") {
		int displaceX = 1;
		int displaceY = 0;
		*x = *x - displaceX;
		*y = *y - displaceY;
	}
	if (direction == "DOWNRIGHT") {
		int displaceX = 1;
		int displaceY = 1;
		*x = *x - displaceX;
		*y = *y - displaceY;
	}
	if (direction == "DOWN") {
		int displaceX = 0;
		int displaceY = 1;
		*x = *x - displaceX;
		*y = *y - displaceY;
	}
	if (direction == "DOWNLEFT") {
		int displaceX = -1;
		int displaceY = 1;
		*x = *x - displaceX;
		*y = *y - displaceY;
	}
	if (direction == "LEFT") {
		int displaceX = -1;
		int displaceY = 0;
		*x = *x - displaceX;
		*y = *y - displaceY;
	}
	if (direction == "UPLEFT") {
		int displaceX = -1;
		int displaceY = -1;
		*x = *x - displaceX;
		*y = *y - displaceY;
	}
}

void coordCorrectionMove(string direction, int* x, int* y) {
	// used to find starting cell in possibleMoves
	if (direction == "UP") {
		int displaceX = 0;
		int displaceY = -1;
		*x = *x + displaceX;
		*y = *y + displaceY;
	}
	if (direction == "UPRIGHT") {
		int displaceX = 1;
		int displaceY = -1;
		*x = *x + displaceX;
		*y = *y + displaceY;
	}
	if (direction == "RIGHT") {
		int displaceX = 1;
		int displaceY = 0;
		*x = *x + displaceX;
		*y = *y + displaceY;
	}
	if (direction == "DOWNRIGHT") {
		int displaceX = 1;
		int displaceY = 1;
		*x = *x + displaceX;
		*y = *y + displaceY;
	}
	if (direction == "DOWN") {
		int displaceX = 0;
		int displaceY = 1;
		*x = *x + displaceX;
		*y = *y + displaceY;
	}
	if (direction == "DOWNLEFT") {
		int displaceX = -1;
		int displaceY = 1;
		*x = *x + displaceX;
		*y = *y + displaceY;
	}
	if (direction == "LEFT") {
		int displaceX = -1;
		int displaceY = 0;
		*x = *x + displaceX;
		*y = *y + displaceY;
	}
	if (direction == "UPLEFT") {
		int displaceX = -1;
		int displaceY = -1;
		*x = *x + displaceX;
		*y = *y + displaceY;
	}
}

bool lineWalk(int** board, int startX, int startY, string direction, string player, bool place) {
	// helper for legal move checking
	// check if one direction is legal
	// starting cell is a cell that contains the player
	// from starting cell, walk one direction
	// while next cell is player, keep walking
	// if last cell is free cell and 2nd to last cell is player: true
	// if next cell is past boardsize, or is the opponent, not a legal move: false
	bool possible = false;
	int displaceX;
	int displaceY;
	int nextCellX = startX;
	int nextCellY = startY;

	string opponent;
	int playerPiece;
	if (player == player1) {
		playerPiece = p1Num;
		opponent = player2;
	}
	else {
		playerPiece = p2Num;
		opponent = player1;
	}

	if (direction == "UP") {
		displaceX = 0;
		displaceY = -1;

		// place pieces ( assuming legal move has been checked )
		if (place) {
			if (board[nextCellX][nextCellY] == -1) {
				return false;
			}
			while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
				// cout << "inside checkCellIsPlayer" << endl;

				placePiece(board, nextCellX, nextCellY, player);
				nextCellX = nextCellX + displaceX;
				nextCellY = nextCellY + displaceY;
			}
			placePiece(board, nextCellX, nextCellY, player);

			return false;
		}

		// check if space available to place piece
		if (!checkCellIsEmpty(board, nextCellX - displaceX, nextCellY - displaceY)) {
			return false;
		}

		// keep walking until cell is not opponent
		while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
			// next cell
			nextCellX = nextCellX + displaceX;
			nextCellY = nextCellY + displaceY;
		}

		// off by 1
		nextCellX = nextCellX + displaceX;
		nextCellY = nextCellY + displaceY;

		// check borders
		if ((nextCellX < 0) || (nextCellX >= boardX)) {
			return false;
		}
		if ((nextCellY < 0) || (nextCellY >= boardY)) {
			return false;
		}
		if (board[nextCellX][nextCellY] == -1) {
			return false;
		}
		// if last piece in line is player
		if (board[nextCellX][nextCellY] == playerPiece) {
			possible = true;
		}

		return possible;
	}
	if (direction == "UPRIGHT") {
		displaceX = 1;
		displaceY = -1;

		// place pieces ( assuming legal move has been checked )
		if (place) {
			if (board[nextCellX][nextCellY] == -1) {
				return false;
			}
			while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
				placePiece(board, nextCellX, nextCellY, player);
				nextCellX = nextCellX + displaceX;
				nextCellY = nextCellY + displaceY;
			}
			placePiece(board, nextCellX, nextCellY, player);

			return false;
		}

		// check if space available to place piece
		if (!checkCellIsEmpty(board, nextCellX - displaceX, nextCellY - displaceY)) {
			return false;
		}

		// keep walking until cell is not opponent
		while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
			// next cell
			nextCellX = nextCellX + displaceX;
			nextCellY = nextCellY + displaceY;
		}

		// off by 1
		nextCellX = nextCellX + displaceX;
		nextCellY = nextCellY + displaceY;
		if ((nextCellX < 0) || (nextCellX >= boardX)) {
			return false;
		}
		if ((nextCellY < 0) || (nextCellY >= boardY)) {
			return false;
		}
		if (board[nextCellX][nextCellY] == -1) {
			return false;
		}
		// if last piece in line is player
		if (board[nextCellX][nextCellY] == playerPiece) {
			possible = true;
		}

		return possible;
	}
	if (direction == "RIGHT") {
		displaceX = 1;
		displaceY = 0;

		// place pieces ( assuming legal move has been checked )
		if (place) {
			if (board[nextCellX][nextCellY] == -1) {
				return false;
			}
			while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
				placePiece(board, nextCellX, nextCellY, player);
				nextCellX = nextCellX + displaceX;
				nextCellY = nextCellY + displaceY;
			}
			placePiece(board, nextCellX, nextCellY, player);

			return false;
		}

		// check if space available to place piece
		if (!checkCellIsEmpty(board, nextCellX - displaceX, nextCellY - displaceY)) {
			return false;
		}

		// keep walking until cell is not opponent
		while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
			// next cell
			nextCellX = nextCellX + displaceX;
			nextCellY = nextCellY + displaceY;
		}

		// off by 1
		nextCellX = nextCellX + displaceX;
		nextCellY = nextCellY + displaceY;

		// check borders
		if ((nextCellX < 0) || (nextCellX >= boardX)) {
			return false;
		}
		if ((nextCellY < 0) || (nextCellY >= boardY)) {
			return false;
		}
		if (board[nextCellX][nextCellY] == -1) {
			return false;
		}
		// if last piece in line is player
		if (board[nextCellX][nextCellY] == playerPiece) {
			possible = true;
		}

		return possible;
	}
	if (direction == "DOWNRIGHT") {
		displaceX = 1;
		displaceY = 1;
		// place pieces ( assuming legal move has been checked )
		if (place) {
			if (board[nextCellX][nextCellY] == -1) {
				return false;
			}
			while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
				placePiece(board, nextCellX, nextCellY, player);
				nextCellX = nextCellX + displaceX;
				nextCellY = nextCellY + displaceY;
			}
			placePiece(board, nextCellX, nextCellY, player);

			return false;
		}

		// check if space available to place piece
		if (!checkCellIsEmpty(board, nextCellX - displaceX, nextCellY - displaceY)) {
			// cout << "No space to make move in cell (X: " << nextCellX - displaceX + 1 << ", Y: " << nextCellY - displaceY + 1 << ") \n";
			return false;
		}

		// keep walking until cell is not opponent
		while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
			// next cell
			nextCellX = nextCellX + displaceX;
			nextCellY = nextCellY + displaceY;
		}

		// off by 1
		nextCellX = nextCellX + displaceX;
		nextCellY = nextCellY + displaceY;

		// check borders
		if ((nextCellX < 0) || (nextCellX >= boardX)) {
			return false;
		}
		if ((nextCellY < 0) || (nextCellY >= boardY)) {
			return false;
		}
		if (board[nextCellX][nextCellY] == -1) {
			return false;
		}
		// if last piece in line is player
		if (board[nextCellX][nextCellY] == playerPiece) {
			possible = true;
		}

		return possible;
	}
	if (direction == "DOWN") {
		displaceX = 0;
		displaceY = 1;
		// place pieces ( assuming legal move has been checked )
		if (place) {
			if (board[nextCellX][nextCellY] == -1) {
				return false;
			}
			while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
				// cout << "inside checkCellIsPlayer" << endl;

				placePiece(board, nextCellX, nextCellY, player);
				nextCellX = nextCellX + displaceX;
				nextCellY = nextCellY + displaceY;
			}
			placePiece(board, nextCellX, nextCellY, player);

			return false;
		}

		// check if space available to place piece
		if (!checkCellIsEmpty(board, nextCellX - displaceX, nextCellY - displaceY)) {
			return false;
		}

		// keep walking until cell is not opponent
		while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
			// next cell
			nextCellX = nextCellX + displaceX;
			nextCellY = nextCellY + displaceY;
		}

		// off by 1
		nextCellX = nextCellX + displaceX;
		nextCellY = nextCellY + displaceY;

		// check borders
		if ((nextCellX < 0) || (nextCellX >= boardX)) {
			return false;
		}
		if ((nextCellY < 0) || (nextCellY >= boardY)) {
			return false;
		}
		if (board[nextCellX][nextCellY] == -1) {
			return false;
		}
		// if last piece in line is player
		if (board[nextCellX][nextCellY] == playerPiece) {
			possible = true;
		}

		return possible;
	}
	if (direction == "DOWNLEFT") {
		displaceX = -1;
		displaceY = 1;
		// place pieces ( assuming legal move has been checked )
		if (place) {
			if (board[nextCellX][nextCellY] == -1) {
				return false;
			}
			while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
				placePiece(board, nextCellX, nextCellY, player);
				nextCellX = nextCellX + displaceX;
				nextCellY = nextCellY + displaceY;
			}
			placePiece(board, nextCellX, nextCellY, player);

			return false;
		}

		// check if space available to place piece
		if (!checkCellIsEmpty(board, nextCellX - displaceX, nextCellY - displaceY)) {
			return false;
		}

		// keep walking until cell is not opponent
		while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
			// next cell
			nextCellX = nextCellX + displaceX;
			nextCellY = nextCellY + displaceY;
		}

		// off by 1
		nextCellX = nextCellX + displaceX;
		nextCellY = nextCellY + displaceY;

		// check borders
		if ((nextCellX < 0) || (nextCellX >= boardX)) {
			return false;
		}
		if ((nextCellY < 0) || (nextCellY >= boardY)) {
			return false;
		}
		if (board[nextCellX][nextCellY] == -1) {
			return false;
		}
		// if last piece in line is player
		if (board[nextCellX][nextCellY] == playerPiece) {
			possible = true;
		}

		return possible;
	}
	if (direction == "LEFT") {
		displaceX = -1;
		displaceY = 0;
		// place pieces ( assuming legal move has been checked )
		if (place) {
			if (board[nextCellX][nextCellY] == -1) {
				return false;
			}
			while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
				placePiece(board, nextCellX, nextCellY, player);
				nextCellX = nextCellX + displaceX;
				nextCellY = nextCellY + displaceY;
			}
			placePiece(board, nextCellX, nextCellY, player);

			return false;
		}


		// check if space available to place piece
		if (!checkCellIsEmpty(board, nextCellX - displaceX, nextCellY - displaceY)) {
			return false;
		}

		// keep walking until cell is not opponent
		while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
			// next cell
			nextCellX = nextCellX + displaceX;
			nextCellY = nextCellY + displaceY;
		}

		// off by 1
		nextCellX = nextCellX + displaceX;
		nextCellY = nextCellY + displaceY;

		// check borders
		if ((nextCellX < 0) || (nextCellX >= boardX)) {
			return false;
		}
		if ((nextCellY < 0) || (nextCellY >= boardY)) {
			return false;
		}
		if (board[nextCellX][nextCellY] == -1) {
			return false;
		}
		// if last piece in line is player
		if (board[nextCellX][nextCellY] == playerPiece) {
			possible = true;
		}

		return possible;
	}
	if (direction == "UPLEFT") {
		displaceX = -1;
		displaceY = -1;
		// place pieces ( assuming legal move has been checked )
		if (place) {
			if (board[nextCellX][nextCellY] == -1) {
				return false;
			}
			while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
				placePiece(board, nextCellX, nextCellY, player);
				nextCellX = nextCellX + displaceX;
				nextCellY = nextCellY + displaceY;
			}
			placePiece(board, nextCellX, nextCellY, player);

			return false;
		}


		// check if space available to place piece
		if (!checkCellIsEmpty(board, nextCellX - displaceX, nextCellY - displaceY)) {
			return false;
		}

		// keep walking until cell is not opponent
		while (checkCellIsPlayer(board, nextCellX, nextCellY, displaceX, displaceY, opponent)) {
			// next cell
			nextCellX = nextCellX + displaceX;
			nextCellY = nextCellY + displaceY;
		}

		// off by 1
		nextCellX = nextCellX + displaceX;
		nextCellY = nextCellY + displaceY;

		// check borders
		if ((nextCellX < 0) || (nextCellX >= boardX)) {
			return false;
		}
		if ((nextCellY < 0) || (nextCellY >= boardY)) {
			return false;
		}
		if (board[nextCellX][nextCellY] == -1) {
			return false;
		}
		// if last piece in line is player
		if (board[nextCellX][nextCellY] == playerPiece) {
			possible = true;
		}

		return possible;
	}

	cout << "	in lineWalk():" << endl;
	cout << "	Error: Invalid move made, " << direction << endl;
	return possible;
}

vector<string> possibleMoves(int** board, string player, bool show) {
	// look through each cell in board till opponent found
	// line walk each direction to check if move possible
	int cell;
	int playerPiece;
	int oppPiece;
	string opponent;
	string chosenDir;

	int directionSize = 8;
	string directions[8] = { "UP", "UPRIGHT", "RIGHT", "DOWNRIGHT", "DOWN", "DOWNLEFT", "LEFT", "UPLEFT" };

	vector<string> movesTemp;

	// define player and opponent pieces
	if (player == player1) {
		playerPiece = p1Num;
		oppPiece = p2Num;
		opponent = player2;
	}
	else {
		playerPiece = p2Num;
		oppPiece = p1Num;
		opponent = player1;
	}

	// loop through board
	for (int x = 0; x < boardX; x++) {
		for (int y = 0; y < boardY; y++) {
			cell = board[x][y];

			// opponent piece found
			if (cell == oppPiece) {
				for (int i = 0; i < directionSize; i++) {
					chosenDir = directions[i];

					// if a direction is possible
					if (lineWalk(board, x, y, chosenDir, player, false)) {
						int startX = x;
						int startY = y;
						coordCorrectionStart(chosenDir, &startX, &startY);

						bool duplicate = false;
						string possibleMove = coordToString(startX, startY);
						// check duplicate
						for (unsigned int i = 0; i < movesTemp.size(); i++) {
							string moveTest = movesTemp.at(i);
							if (moveTest == possibleMove) {
								duplicate = true;
								break;
							}
						}
						if (!duplicate) {
							movesTemp.push_back(possibleMove);
						}
					}
				}

			}

		}
	}

	if (show) {
		cout << "	Possible moves are: ";
		for (unsigned int i = 0; i < movesTemp.size(); i++) {

			cout << movesTemp.at(i) << " ";
		}
	}
	return movesTemp;;

}

// check legal moves if player is making the move
void makeMove(int** board, string move, string player) {
	// places the piece on the board and uses linewalk to
	// caputre the other pieces

	int* cell = stringToCoord(move);
	int x = cell[0];
	int y = cell[1];

	int directionSize = 8;
	string directions[8] = { "UP", "UPRIGHT", "RIGHT", "DOWNRIGHT", "DOWN", "DOWNLEFT", "LEFT", "UPLEFT" };



	for (int i = 0; i < directionSize; i++) {
		string chosenDir = directions[i];
		int startX = x;
		int startY = y;

		coordCorrectionMove(chosenDir, &startX, &startY);

		if (lineWalk(board, startX, startY, chosenDir, player, false)) {
			lineWalk(board, startX, startY, chosenDir, player, true);
		}
		// cout << endl;
	}
	placePiece(board, x, y, player);

	delete[] cell;

	return;
}

int* scoreCount(int** board, bool print) {
	// counts how many pieces player 1 and player 2 has each
	// score[0] = player 1, score[1] = player 2
	// cout << "scoreCount start" << endl;
	int* score = new int[2];

	int p1Score = 0;
	int p2Score = 0;

	for (int x = 0; x < boardX; x++) {
		for (int y = 0; y < boardY; y++) {
			int cell = board[x][y];

			if (cell == p1Num) {
				p1Score++;
			}
			else {
				if (cell == p2Num) {
					p2Score++;
				}
			}

		}
	}

	score[0] = p1Score;
	score[1] = p2Score;

	if (print) {
		cout << "inside print" << endl;
		cout << "player 1 score: " << score[0] << endl;
		cout << "player 2 score: " << score[1] << endl;
	}

	return score;
}

int** copyBoard(int** board) {
	// init new copy
	int** copy = new int* [boardX];
	for (int i = 0; i < boardX; i++) {
		copy[i] = new int[boardX];
	}

	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			copy[x][y] = board[x][y];
		}
	}

	return copy;
}

bool gameEnd(int** board) {
	bool end = true;

	// check if both players cannot make move
	vector<string> player1moves = possibleMoves(board, player1, false);
	vector<string> player2moves = possibleMoves(board, player2, false);
	if ((player1moves.size() == 0) && player2moves.size() == 0) {
		return end;
	}

	// check if board is filled
	int limit = boardX * boardY;

	int count = 0;
	int iX = 0;
	int iY = 0;
	while (end && (count < limit)) {
		int cell = board[iX][iY];
		if (cell == -1) {
			end = false;
			return end;
		}

		iX++;
		if (iX == boardX) {
			iX = 0;
			iY++;
		}
		count++;
	}

	return end;
}

int learn(int** board, string move, string player, string opponent, bool myTurn) {

	// base case
	if (gameEnd(board)) {
		int* scores = scoreCount(board, false);
		//player win
		if (scores[0] > scores[1]) {

			delete[] scores;
			return 2;
		}
		if (scores[0] < scores[1]) {

			delete[] scores;
			return -1;
		}
		if (scores[0] == scores[1]) {

			delete[] scores;
			return 1;
		}
	}

	// init choices
	vector<string> choices;
	bool nextTurn = false;

	// make the move
	if (myTurn) {
		if (move != "") {
			makeMove(board, move, player);
		}
		choices = possibleMoves(board, opponent, false);
		// no choices available
		if (choices.size() == 0) {
			return learn(board, "", player, opponent, false);
		}
	}
	else {
		// opponent turn
		if (move != "") {
			makeMove(board, move, opponent);
		}
		choices = possibleMoves(board, player, false);
		if (choices.size() == 0) {
			return learn(board, "", player, opponent, true);
		}
		nextTurn = true;
	}

	// pick random move for next players turn
	srand(time(0));
	int randomIndex = rand() % choices.size();
	string nextMove = choices.at(randomIndex);


	return learn(board, nextMove, player, opponent, nextTurn);
}

void AIMove(int** board, string player) {
	// for each possible move, do an amount of playouts
	// use results of playouts to determine with move to do

	// increase runs depending on how many pieces on board
	int* boardPieces = scoreCount(board, false);
	int totalPieces = boardPieces[0] + boardPieces[1];
	int totalRuns = 4 + totalPieces / 8;

	// initialize move scores
	vector<string> choices = possibleMoves(board, player, false);

	if (choices.size() < 0) {
		cout << "	AI has no moves. Passing this turn.\n";
		return;
	}

	int* choiceScore = new int[choices.size()];
	for (unsigned int i = 0; i < choices.size(); i++) {
		choiceScore[i] = 0;
	}

	// no moves
	if (choices.size() == 0) {
		return;
	}

	// limit amount of total runs, spread amount of runs for each move
	int runs = totalRuns / choices.size();
	if (runs <= 0) {
		runs = 1;
	}


	string opponent;
	if (player == player1) {
		opponent = player2;
	}
	else {
		opponent = player1;
	}

	// playouts
	cout << "	No heuristic AI\n";
	for (unsigned int iMove = 0; iMove < choices.size(); iMove++)
	{

		int score = 0;
		string move = choices.at(iMove);
		for (int run = 0; run < runs; run++) {
			// make copy of board
			int** copyOfBoard = copyBoard(board);
			score = score + learn(copyOfBoard, move, player, opponent, true);

			// delete copyOfBoard
			for (int i = 0; i < boardX; ++i) {
				delete[] copyOfBoard[i];
			}

			//Free the array of pointers
			delete[] copyOfBoard;
		}

		cout << "Thinking..." << endl;
		choiceScore[iMove] = score;

	}

	// decide move

	int bestMove = choiceScore[0];
	string finalMove = choices.at(0);
	// cout << "Scores: ";
	for (unsigned int iScore = 0; iScore < choices.size(); iScore++) {
		int moveScore = choiceScore[iScore];
		if (moveScore > bestMove) {
			bestMove = moveScore;
			finalMove = choices.at(iScore);
		}

		// if tie, choose randomly
		if ((moveScore == bestMove) && (choices.size() > 1)) {
			finalMove = choices.at(rand() % 2);
		}
	}
	cout << "	no Heuristic AI's Move: " << finalMove << endl;
	// make move
	makeMove(board, finalMove, player);

	delete[] boardPieces;
	delete[] choiceScore;
	return;
}

int learnHeuristic(int** board, string move, string player, string opponent, bool playerTurn) {

	// base case
	if (gameEnd(board)) {
		int* scores = scoreCount(board, false);

		// weighting results with coin parity
		// player win
		if (scores[0] > scores[1]) {
			int result = 2;

			delete[] scores;
			return result;
		}
		// player lose
		if (scores[0] < scores[1]) {
			int result = -1;
			delete[] scores;
			return result;
		}
		// draw
		if (scores[0] == scores[1]) {
			int result = 1;
			delete[] scores;
			return result;
		}
	}

	// init choices
	vector<string> choices;
	bool nextTurn = false;
	string curr_player;
	string curr_opp;

	// make the move
	if (playerTurn) {
		// execute players move
		// opponents turn now
		if (move != "") {
			makeMove(board, move, player);

		}
		choices = possibleMoves(board, opponent, false);
		// no choices available
		if (choices.size() == 0) {
			return learnHeuristic(board, "", player, opponent, false);
		}

		curr_player = opponent;
		curr_opp = player;
	}
	else {
		// execute opponents turn
		// playersTurn now
		if (move != "") {
			makeMove(board, move, opponent);

		}
		choices = possibleMoves(board, player, false);
		if (choices.size() == 0) {
			return learnHeuristic(board, "", player, opponent, true);
		}
		curr_player = player;
		curr_opp = opponent;
		nextTurn = true;
	}

	// pick random move for next players turn
	srand(time(0));
	string nextMove = "";

	int* choice_weight = new int[choices.size()];

	// Apply heurstic for each choice
	int weight = 0;
	int lowerBound = 1000000;
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (unsigned int iMove = 0; iMove < choices.size(); iMove++) {
		int** copyOfBoard = copyBoard(board);
		makeMove(copyOfBoard, choices.at(iMove), curr_player);
		// mobility heuristic
		vector<string> oppChoices = possibleMoves(copyOfBoard, curr_opp, false);
		if ((choices.size() + oppChoices.size()) != 0) {
			weight = weight + (100 * (choices.size() - oppChoices.size()) / (choices.size() + oppChoices.size()));
		}

		// coin parity
		int* stateScore = scoreCount(copyOfBoard, false);
		int oppPieces = stateScore[0];
		int myPieces = stateScore[1];

		weight = weight + (100 * (myPieces - oppPieces) / (myPieces + oppPieces));

		if (weight < lowerBound) {
			lowerBound = weight;
		}
		for (int i = 0; i < boardX; ++i) {
			delete[] copyOfBoard[i];
		}
		//Free the array of pointers
		delete[] copyOfBoard;
		choice_weight[iMove] = weight;
	}
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (unsigned int a = 0; a < choices.size(); a++) {
		// weight correction
		choice_weight[a] = choice_weight[a] - lowerBound;
	}

	// adapted from https://stackoverflow.com/questions/1761626/weighted-random-numbers
	int sum_of_weight = 0;
	for (unsigned int i = 0; i < choices.size(); i++) {
		sum_of_weight += choice_weight[i];
	}
	if (sum_of_weight > 0) {
		int rnd = rand() % sum_of_weight;
		for (unsigned int i = 0; i < choices.size(); i++) {
			if (rnd < choice_weight[i]) {
				nextMove = choices.at(i);
				break;
			}
			rnd -= choice_weight[i];
		}

		return learnHeuristic(board, nextMove, player, opponent, nextTurn);
	}
	else {
		return learnHeuristic(board, choices.at(0), player, opponent, nextTurn);
	}
}

void smartAIMove(int** board, string player) {
	// AI with heuristics
	// for each possible move, do an amount of playouts
	// use results of playouts to determine with move to do
	// using some ideas from https://kartikkukreja.wordpress.com/2013/03/30/heuristic-function-for-reversiothello/

	// increase runs depending on how many pieces on board
	int* boardPieces = scoreCount(board, false);
	int totalPieces = boardPieces[0] + boardPieces[1];
	int totalRuns = 4 + totalPieces / 8;

	// initialize move scores
	vector<string> choices = possibleMoves(board, player, false);
	if (choices.size() < 0) {
		cout << "	AI has no moves. Passing this turn.\n";
		return;
	}
	int* choiceScore = new int[choices.size()];
	for (unsigned int i = 0; i < choices.size(); i++) {
		choiceScore[i] = 0;
	}

	// no moves
	if (choices.size() == 0) {
		return;
	}

	// limit amount of total runs, spread amount of runs for each move
	int runs = totalRuns / choices.size();
	if (runs <= 0) {
		runs = 1;
	}

	string opponent;
	if (player == player1) {
		opponent = player2;
	}
	else {
		opponent = player1;
	}

	// playouts
	cout << "	AI with heuristic\n";
	cout << "totalRuns: " << totalRuns << ", runs; " << runs << endl;
	int* pieces = scoreCount(board, false);
	int piecesCount = pieces[0] + pieces[1];
	for (unsigned int iMove = 0; iMove < choices.size(); iMove++) {

		int score = 0;
		string move = choices.at(iMove);
		for (int run = 0; run < runs; run++) {
			// make copy of board
			int** copyOfBoard = copyBoard(board);
			score = score + learnHeuristic(copyOfBoard, move, player, opponent, true);

			// delete copyOfBoard
			for (int i = 0; i < boardX; ++i) {
				delete[] copyOfBoard[i];
			}
			//Free the array of pointers
			delete[] copyOfBoard;
		}

		cout << "Thinking..." << endl;
		choiceScore[iMove] = score;

	}

	// decide move
	int bestMove = choiceScore[0];
	string finalMove = choices.at(0);

	for (unsigned int iScore = 0; iScore < choices.size(); iScore++) {
		int moveScore = choiceScore[iScore];

		if (moveScore > bestMove) {
			bestMove = moveScore;
			finalMove = choices.at(iScore);
		}

		// if tie, choose randomly
		if ((moveScore == bestMove) && (choices.size() > 1)) {
			finalMove = choices.at(rand() % 2);
		}
	}
	cout << "	Heuristic AI's Move: " << finalMove << endl;
	// make move
	makeMove(board, finalMove, player);
	delete[] boardPieces;
	delete[] choiceScore;
	return;
}

void userMove(int** board, string player) {
	bool legalMove = false;
	string userMove;

	vector<string> userMoveChoices = possibleMoves(board, player, false);

	if (userMoveChoices.size() > 0) {

		while (!legalMove) {
			userMoveChoices = possibleMoves(board, player, true);


			cout << "\n	Please enter your move: ";
			cin >> userMove;

			// check if user input a legal move
			for (unsigned int i = 0; i < userMoveChoices.size(); i++) {
				if (userMove == userMoveChoices.at(i)) {
					legalMove = true;
				}
			}
			if (!legalMove) {
				cout << userMove << " is not a legal move!\n";
			}
		}
		makeMove(board, userMove, player);
	}
	else {
		cout << "	No Possible moves. Passing this turn.\n";
	}
}

void play(bool userFirst, bool userPlay, bool withH) {

	int gameRuns = 0;
	int results[2] = { 0, 0 };
	vector<int> winners;
	if (userPlay) {
		gameRuns = 1;
	}
	else {

		gameRuns = 300;
	}
	for (int game = 0; game < gameRuns; game++) {
		// create board
		int** board = new int* [boardX];
		for (int i = 0; i < boardX; i++) {
			board[i] = new int[boardY];
		}
		// initialize
		for (int x = 0; x < boardX; x++) {
			for (int y = 0; y < boardY; y++) {
				board[x][y] = -1;
			}
		}
		mapInit();
		board[3][3] = 1;
		board[3][4] = 2;
		board[4][3] = 2;
		board[4][4] = 1;

		string user;
		string opponent;
		bool userIsPlayer1 = userFirst;
		bool userTurn = false;
		if (userFirst) {
			user = player1;
			opponent = player2;
			userTurn = true;
		}
		else {
			user = player2;
			opponent = player1;
			userTurn = false;
		}

		while (!gameEnd(board)) {
			printBoard(board);
			cout << endl;
			if (userTurn) {
				// user Turn
				if (userPlay) {
					cout << "	Your turn!\n";
					userMove(board, user);
				}
				else {
					cout << "	AI w/ no Heuristic's turn\n";
					AIMove(board, user);
				}

				userTurn = false;

			}
			else {
				// AI turn
				if (userPlay) {
					cout << "	Oponents turn!\n";
					if (withH) {
						smartAIMove(board, opponent);
					}
					else {
						AIMove(board, opponent);
					}
				}
				else {
					cout << "	AI w/ heuristic's turn!\n";
					smartAIMove(board, opponent);
				}

				userTurn = true;
			}
		}

		cout << endl;
		printBoard(board);
		cout << endl;
		int* score = scoreCount(board, false);
		if (userPlay) {
			if (userIsPlayer1) {
				cout << "	Your Score: " << score[0] << endl;
				cout << "	Opponent's Score: " << score[1] << endl;

				if (score[0] > score[1]) {
					cout << "	You win!" << endl;
				}
				else {
					cout << "	Opponent wins!" << endl;
				}
			}
			else {
				cout << "	Your Score: " << score[1] << endl;
				cout << "	Opponent's Score: " << score[0] << endl;

				if (score[1] > score[0]) {
					cout << "	You win!" << endl;
				}
				else {
					cout << "	Opponent wins!" << endl;
				}
			}
		}
		else {
			// player 1 is always no heurstic
			if (score[0] > score[1]) {
				cout << "	AI w/ no Huerstic wins!" << endl;
				results[0] = results[0] + 1;
				winners.push_back(1);
			}
			else {
				cout << "	AI w/ Heurstic wins!" << endl;
				results[1] = results[1] + 1;
				winners.push_back(2);
			}

			cout << "	Score so far:\n";
			cout << "	noHAI = " << results[0] << endl;
			cout << "	HAI = " << results[1] << endl;

			for (unsigned int i = 0; i < winners.size(); ++i)
				cout << "Match #" << i << " winner: " << winners.at(i) << endl;
		}

		// delete copyOfBoard
		for (int i = 0; i < boardX; ++i) {
			delete[] board[i];
		}
		//Free the array of pointers
		delete[] board;
	}

	cout << endl;
	char end;
	cout << "Program ending, you may exit";
	cin >> end;

	return;
}

int main() {

	char first;
	char userPlay;
	char withH;
	bool botNoH = false;
	cout << "	Reversi AI using Monte Carlo Tree Search\n\n";
	cout << "	Would you like to play? Y\\N: ";
	cin >> userPlay;
	cout << endl;
	if (tolower(userPlay) == 'y') {
		cout << "	Would you like to go against AI with Heuristics? Y\\N: ";
		cin >> withH;
		withH = tolower(withH);
		if (withH == 'y') {
			// with heuristic
			cout << "	You'll go against AI with Heuristics!\n";
			botNoH = true;
		}
		else {
			// w/o heuristic
			cout << "	You'll go against AI w/o Heuristics!\n";
			botNoH = false;
		}
		cout << endl;
		cout << "	O goes first, X goes second.\n";
		cout << "Would you like to go first? Y\\N: ";
		cin >> first;
		cout << endl;
		cout << "	You typed: " << first << endl;


		if (tolower(first) == 'y') {
			cout << "	You are going first! Your piece is O" << endl;
			play(true, true, botNoH);
		}
		else {
			cout << "	You are going second! Your piece is X" << endl;
			play(false, true, botNoH);
		}
	}
	else {
		cout << "	AI's will play!" << endl;
		play(true, false, botNoH);
	}
	return 0;
}

