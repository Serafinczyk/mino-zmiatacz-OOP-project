#include "MSBoardTextView.h"

MSBoardTextView::MSBoardTextView(MinesweeperBoard& _board) : board(_board){

}

void MSBoardTextView::display() const {
	int width = board.getBoardWidth();
	int height = board.getBoardHeight();
	int widthInChars = width * 3 + 3 - 5; //Board width in characters (3 chars per field + 3 char for the left border, -5 to center)
	drawMarginTop(3);
	drawMarginLeft(widthInChars / 2 + 3);
	std::cout << "SAPER" << std::endl;
	drawMarginTop(3);
	drawMarginLeft(3);
	for (int col = 0; col < width; ++col) { //Table header with column numbers
		if (col < 10) drawMarginLeft(1);
		if (col < 100) drawMarginLeft(1);
		std::cout << col;
	}
	std::cout << std::endl;
	for (int row = 0; row < height; ++row) { //Each individual row
		if (row < 10) drawMarginLeft(1);
		if (row < 100) drawMarginLeft(1);
		std::cout << row;
		drawMarginLeft(1);
		for (int col = 0; col < width; ++col) { //Each column
			std::cout << '[' << board.getFieldInfo(row, col) << ']';
		}
		std::cout << std::endl;
	}
	drawMarginTop(3);
	std::cout << "(Use arrow keys to move, f key to place a flag, and space to reveal field.)"<<std::endl;

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