#include "MinesweeperBoard.h"

MinesweeperBoard::MinesweeperBoard() {
	initializeBoard(7, 5);
	initializeRandomDevice();
	placeMinesAtHardCodedPos();
}

MinesweeperBoard::MinesweeperBoard(int _width, int _height, GameMode _mode) {
	initializeBoard(_height, _width);
	initializeRandomDevice();
	if(_mode == DEBUG) {
		placeMinesInDebugMode();
	} else {
		float numberOfMinesToPlace = (float) width * height * _mode / 100 ; //Calculating from value inside enum :)
		placeMinesRandomly(std::ceil(numberOfMinesToPlace));
	}
}

void MinesweeperBoard::initializeBoard(int _height, int _width) {
	width = _width;
	height = _height;
	Field defaultField = { false, false, false };
	std::vector<Field> row(width, defaultField);
	board.resize(height,row);
}

void MinesweeperBoard::initializeRandomDevice() {
	randomGenerator = std::mt19937(randomDevice());
	randomDistributionForRow = std::uniform_int_distribution<>(0, height - 1);
	randomDistributionForCol = std::uniform_int_distribution<>(0, width - 1);
}

//Placing mines logic
void MinesweeperBoard::placeMinesAtHardCodedPos() {
	board[0][0].hasMine = true; //row=0 col=0 has mine, has not flag, is not revealed
	board[1][1].isRevealed = true; //row=1 col=1 has not mine, has not flag, is revealed
	
	board[0][2].hasMine = true; //row=0 col=2 has mine
	board[0][2].hasFlag = true; //Also has flag
}

void MinesweeperBoard::placeMinesInDebugMode() {
	//To be more efficient, i won't go through each tile
	for (int col = 0; col < width; ++col) {
		board[0][col].hasMine = true;
	}

	for (int row = 1; row < height; ++row) {
		board[row][0].hasMine = true;
	}

	for (int diagonal = 1; diagonal < std::min(width, height); ++diagonal) {
		board[diagonal][diagonal].hasMine = true;
	}
}

void MinesweeperBoard::placeMinesRandomly(int _minesToPlace) {
	for (int mine = 0; mine < _minesToPlace; ++mine) {
		int row = randomDistributionForRow(randomGenerator);
		int col = randomDistributionForCol(randomGenerator);
		while (board[row][col].hasMine) {
			row = randomDistributionForRow(randomGenerator);
			col = randomDistributionForCol(randomGenerator);
		}
		board[row][col].hasMine = true;
	}
}

//Debugging helpers
void MinesweeperBoard::debug_display() const {
	std::cout << "    ";
	for (int col = 0; col < width; ++col) { //Table header with column numbers
		std::cout << col << "    ";
	}
	std::cout << std::endl;

	for (int row = 0; row < height; ++row) { //Each individual row
		std::cout << row << ' ';
		for (int col = 0; col < width; ++col) { //Each column
			std::cout << '[';
			if (board[row][col].hasMine) std::cout << 'M'; else std::cout << '.';
			if (board[row][col].isRevealed) std::cout << 'r'; else std::cout << '.';
			if (board[row][col].hasFlag) std::cout << 'f'; else std::cout << '.';
			std::cout << ']';
		}
		std::cout << std::endl;
	}
	
}