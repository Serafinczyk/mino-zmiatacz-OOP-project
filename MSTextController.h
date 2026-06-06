#pragma once
#include <windows.h>
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"

class MSTextController
{
	public:
		MSTextController(MinesweeperBoard& _board, MSBoardTextView& _view);
		~MSTextController();
		void play();

	private:
		MinesweeperBoard& board;
		MSBoardTextView& view;
		HANDLE console;
		COORD pos;
		COORD zeroPos;
		DWORD consoleMode;
		int cursorRow;
		int cursorCol;
		int width;
		int height;

		void moveCursor(int _row, int _col); //Move with relative offset
		void placeCursor(int _row, int _col);//Place at given coords
		void releaseCursor();
		void getCursorBack();
};

