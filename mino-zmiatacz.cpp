#include "MSBoardTextView.h"
#include "MinesweeperBoard.h"

int main()
{
	MinesweeperBoard board(15, 15, GameMode::EASY); //max 50 x 50
	MSBoardTextView view(board);
	view.display();
	board.revealField(0, 5);
	view.display();

}

