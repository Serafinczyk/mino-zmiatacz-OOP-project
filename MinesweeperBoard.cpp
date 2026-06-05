#include "MinesweeperBoard.h"

MinesweeperBoard::MinesweeperBoard() {
	initializeBoard(7, 5);
	placeMinesAtHardCodedPos();
}

void MinesweeperBoard::initializeBoard(int _height, int _width) {
	width = _width;
	height = _height;
	Field defaultField = { false, false, false };
	std::vector<Field> row(width, defaultField);
	board.resize(height,row);
}

void MinesweeperBoard::placeMinesAtHardCodedPos() {
	board[0][0].hasMine = true; //row=0 col=0 has mine, has not flag, is not revealed
	board[1][1].isRevealed = true; //row=1 col=1 has not mine, has not flag, is revealed
	
	board[0][2].hasMine = true; //row=0 col=2 has mine
	board[0][2].hasFlag = true; //Also has flag
}