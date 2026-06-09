#include "MSBoardTextView.h"

MSBoardTextView::MSBoardTextView(MinesweeperBoard& _board) : board(_board){

}

void MSBoardTextView::display() const {
	int width = board.getBoardWidth();
	int height = board.getBoardHeight();

	int widthInChars = width * 3 + 2;

	drawMarginTop(3);
	drawMarginLeft(widthInChars / 2 + 1);
	std::cout << "SAPER" << std::endl;
	drawMarginTop(1);

	GameState state = board.getGameState();
	if (state == FINISHED_WIN) {
		drawMarginLeft(widthInChars / 2 - 6);
		std::cout << "Congrats you won :)" << std::endl;
	} else if (state == FINISHED_LOSS) {
		drawMarginLeft(widthInChars / 2 - 2);
		std::cout << "You lost :(" << std::endl;
	}
	else {
		drawMarginTop(1);
	}

	drawMarginTop(1);

	drawMarginLeft(5);
	for (int col = 0; col < width; ++col) { //Table header with column numbers
		std::cout << formatNumTo3Chars(col);
	}

	std::cout << std::endl;

	for (int row = 0; row < height; ++row) { //Each individual row
		drawMarginLeft(2);
		std::cout << formatNumTo3Chars(row);
		for (int col = 0; col < width; ++col) { //Each column
			std::cout << '[' << board.getFieldInfo(row, col) << ']';
		}
		std::cout << std::endl;
	}
	drawMarginTop(3);
	if (state == RUNNING) {
		std::cout << "(Use wsad keys to move, f key to place a flag, space to reveal field and e to exit.)" << std::endl;
	}
	else {
		std::cout << "(Press e to exit.)" << std::endl;
	}
	

}

void MSBoardTextView::drawMarginTop(int _size) const {
	for (int i = 0; i < _size; i++) {
		std::cout << std::endl;
	}
}

void MSBoardTextView::drawMarginLeft(int _size) const {
	for (int i = 0; i < _size; i++) {
		std::cout << ' ';
	}
}

void MSBoardTextView::clear() const {
	system("cls");
}

std::string MSBoardTextView::formatNumTo3Chars(int _number) const{
		if (_number <10) return " " + std::to_string(_number) + " ";
		else if (_number <100) return std::to_string(_number) + " ";
		else return std::to_string(_number);
}