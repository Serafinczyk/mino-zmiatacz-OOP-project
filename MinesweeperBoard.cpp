#include "MinesweeperBoard.h"

MinesweeperBoard::MinesweeperBoard() {
	initializeBoard(7, 5);
	placeMinesAtHardCodedPos();
}

void MinesweeperBoard::initializeBoard(int _width, int _height) {
	width = _width;
	height = _height;
	Field defaultField = { false, false, false };
	std::vector<Field> column(height, defaultField);
	board.resize(width,column);
}

void MinesweeperBoard::placeMinesAtHardCodedPos() {
	board[0][0].hasMine = true; //x=0 y=0 has mine, has not flag, is not revealed
	board[1][1].isRevealed = true; //x=1 y=1 has not mine, has not flag, is revealed
	
	board[2][0].hasMine = true; //x=2 y=0 has mine
	board[2][0].hasFlag = true; //Also has flag
}