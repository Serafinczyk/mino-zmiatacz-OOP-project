#include "MinesweeperBoard.h"

MinesweeperBoard::MinesweeperBoard() {
	initializeBoard(7, 5);
	initializeRandomDevice();
	placeMinesAtHardCodedPos();
	waitingForFirstMove = true;
	gameMode = EASY;
	gameState = RUNNING;
}

MinesweeperBoard::MinesweeperBoard(int _width, int _height, GameMode _mode) {
	initializeBoard(_height, _width);
	initializeRandomDevice();
	if(_mode == DEBUG) {
		placeMinesInDebugMode();
	} else {
		float numberOfMinesToPlace = (float) width * height * _mode / 100 ; //Calculating from value inside enum :)
		placeMinesRandomly(static_cast<int>(std::ceil(numberOfMinesToPlace)));
	}
	waitingForFirstMove = true;
	gameMode = _mode;
	gameState = RUNNING;
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

	minesCount = 2;
}

void MinesweeperBoard::placeMinesInDebugMode() {
	minesCount = width + height - 1 + std::min(width, height) - 1;

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
	minesCount = _minesToPlace;
	for (int mine = 0; mine < _minesToPlace; ++mine) {
		placeMineAtRandomEmptyField();
	}
}

void MinesweeperBoard::moveMine(int _row, int _col) {
	board[_row][_col].hasMine = false;
	placeMineAtRandomEmptyField();
}

void MinesweeperBoard::placeMineAtRandomEmptyField() {
	int row = randomDistributionForRow(randomGenerator);
	int col = randomDistributionForCol(randomGenerator);
	while (board[row][col].hasMine) {
		row = randomDistributionForRow(randomGenerator);
		col = randomDistributionForCol(randomGenerator);
	}
	board[row][col].hasMine = true;
}

int MinesweeperBoard::getBoardWidth() const {
	return width;
}

int MinesweeperBoard::getBoardHeight() const {
	return height;
}

int MinesweeperBoard::getMineCount() const {
	return minesCount;
}

GameState MinesweeperBoard::getGameState() const {
	return gameState;
}

int  MinesweeperBoard::countMines(int _row, int _col) const {
	int minesAround = 0;

	if (_row < 0 || _col < 0 || _row >= height || _col >= width) return -1; //Invalid position
	if (!board[_row][_col].isRevealed) return -1; //Position was not revealed yet
	//Start scanning
	_row--;
	_col--;
	for (int row = _row; row < 3 + _row;++row) {
		for (int col = _col; col < 3 + _col;++col) {
			if (row < 0 || col < 0 || row >= height || col >= width) continue; //Out of bounds, skip
			if (board[row][col].hasMine) {
				minesAround++;
			}
		}
	}
	return minesAround;
}

bool MinesweeperBoard::hasFlag(int _row, int _col) const {
	if (_row < 0 || _col < 0 || _row >= height || _col >= width) return false; //Outside the board
	if (board[_row][_col].isRevealed) return false; //Already revealed
	return board[_row][_col].hasFlag;
}

void  MinesweeperBoard::toggleFlag(int _row, int _col) {
	if (_row < 0 || _col < 0 || _row >= height || _col >= width) return; //Outside the board
	if (board[_row][_col].isRevealed) return; //Already revealed
	if (gameState != RUNNING) return; //Game is already finished
	board[_row][_col].hasFlag ^= true; //using XOR to togle the flag
}

void MinesweeperBoard::revealField(int _row, int _col) {
	if (_row < 0 || _col < 0 || _row >= height || _col >= width) return; //Outside the board
	if (board[_row][_col].isRevealed) return; //Already revealed
	if (gameState != RUNNING) return; //Game is already finished
	if (board[_row][_col].hasFlag) return; //There is a flag on the field

	if (!board[_row][_col].hasMine) { //If the field was not revealed and there is no mine on it 
		board[_row][_col].isRevealed = true;
		waitingForFirstMove = false;
		return;
	}

	//If (if not needed) the field was not revealed and there is a mine on it 
	if (waitingForFirstMove && gameMode!=DEBUG) { //its the first player action - move mine to another location, reveal field (not in DEBUG mode!)
		moveMine(_row, _col);
		board[_row][_col].isRevealed = true;
		waitingForFirstMove = false;
		return;
	}
	else {
		revealAllMines();
		gameState = FINISHED_LOSS;
		waitingForFirstMove = false;
		return;
	}
}

void MinesweeperBoard::revealAllMines() { //First time i have to scan whole board :(
	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			if (board[row][col].hasMine && !board[row][col].hasFlag) { // Uncover only ones without flag
				board[row][col].isRevealed = true;
			}
		}
	}
}

bool MinesweeperBoard::isRevealed(int _row, int _col) const {
	if (_row < 0 || _col < 0 || _row >= height || _col >= width) return false; //Outside the board
	return board[_row][_col].isRevealed;
}

//Returns field info for display
char MinesweeperBoard::getFieldInfo(int _row, int _col) const {
	if (_row < 0 || _col < 0 || _row >= height || _col >= width) return '#'; //Outside the board
	Field f = board[_row][_col];
	if (!f.isRevealed && f.hasFlag) return 'F';
	if (!f.isRevealed && !f.hasFlag) return '_';
	//Only revealed fields will reach this point
	if (f.hasMine) return 'x';
	//Only revealed fields without mines will reach this point
	int minesAround = countMines(_row, _col);
	if (minesAround == 0) return ' ';
	return '0' + minesAround; //int to char
}


//Debugging helper
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