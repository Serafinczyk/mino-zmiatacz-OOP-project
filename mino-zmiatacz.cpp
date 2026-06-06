#include "MSBoardTextView.h"
#include "MinesweeperBoard.h"

int main()
{
	MinesweeperBoard board(6, 6, GameMode::EASY); //max 50 x 50
	MSBoardTextView view(board);
	view.display();
	board.revealField(0, 5);
	board.revealField(0, 0);
	view.clear();
	view.display();

}

