

#include "MinesweeperBoard.h"

int main()
{
	MinesweeperBoard board(3,8,HARD);
	board.debug_display();
	board.toggleFlag(1, 1);
	
	board.hasFlag(1, 1);
	board.revealField(0, 0);
	board.revealField(1, 0);
	board.debug_display();
}

