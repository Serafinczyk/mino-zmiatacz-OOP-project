
#include <iostream>
#include "MinesweeperBoard.h"

int main()
{
	MinesweeperBoard board(3,8,NORMAL);
	int width = board.getBoardWidth();
	int height = board.getBoardHeight();
	int mines = board.getMineCount();
	board.debug_display();
}

