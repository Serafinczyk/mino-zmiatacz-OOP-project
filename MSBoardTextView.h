#pragma once
#include <iostream>
#include "MinesweeperBoard.h"
#include <Windows.h>

class MSBoardTextView
{
	public:
	//Constructor
	MSBoardTextView(MinesweeperBoard& _board);
	
		void display() const;
		void clear() const;

	private:
		MinesweeperBoard& board;
		void drawMarginTop(int _size) const;
		void drawMarginLeft(int _size) const;
};

