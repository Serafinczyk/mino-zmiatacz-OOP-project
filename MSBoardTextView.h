#pragma once
#include <iostream>
#include <string>
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
		std::string formatNumTo3Chars(int _number) const;
};

