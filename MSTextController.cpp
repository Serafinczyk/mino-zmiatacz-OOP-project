#include "MSTextController.h"
#include <conio.h>

MSTextController::MSTextController(MinesweeperBoard& _board, MSBoardTextView& _view) : board(_board), view(_view){
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleMode = 0;

	cursorRow = 0;
	cursorCol = 0;
	placeCursor(cursorRow, cursorCol);

	zeroPos.X = 0;
	zeroPos.Y = 0;

	width = board.getBoardWidth();
	height = board.getBoardHeight();
}

MSTextController::~MSTextController() {
	releaseCursor();
}

void MSTextController::placeCursor(int _row, int _col) {
	pos.X = 6 + _col * 3;
	pos.Y = 8 + _row;
	SetConsoleCursorPosition(console, pos);
}

void MSTextController::moveCursor(int _row, int _col) {
	cursorRow += _row;
	if (cursorRow < 0) cursorRow = 0;
	if (cursorRow >= height) cursorRow = height - 1;

	cursorCol += _col;
	if (cursorCol < 0) cursorCol = 0;
	if (cursorCol >= width)cursorCol = width - 1;

	placeCursor(cursorRow, cursorCol);
}

void MSTextController::releaseCursor() {
	std::cout << "\x1b[0 q";
	SetConsoleCursorPosition(console, zeroPos);
}

void MSTextController::getCursorBack() {
	std::cout << "\x1b[1 q"; //set blinking cursor
	SetConsoleCursorPosition(console, pos);
}

void MSTextController::play() {
	view.clear();
	view.display();
	GetConsoleMode(console, &consoleMode);
	SetConsoleMode(console, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING); //enable ANSI escape sequences
	SetConsoleCursorPosition(console, pos);
	std::cout << "\x1b[1 q"; //set blinking cursor
	
	char key;
	do {
		key = _getch();
		switch (key) {
			case 'w':
			case 'W':
				moveCursor(-1, 0);
			break;

			case 's':
			case 'S':
				moveCursor(1, 0);
			break;

			case 'a':
			case 'A':
				moveCursor(0, -1);
			break;

			case 'd':
			case 'D':
				moveCursor(0, 1);
			break;

			case 'f':
			case 'F':
				board.toggleFlag(cursorRow,cursorCol);
				releaseCursor();
				view.clear();
				view.display();
				getCursorBack();
			break;

			case ' ':
				board.revealField(cursorRow, cursorCol);
				releaseCursor();
				view.clear();
				view.display();
				getCursorBack();
			break;

			default:
			break;
		}
	} while (key!='e');
	view.clear();
}