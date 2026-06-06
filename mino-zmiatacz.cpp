#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"

int main()
{
	MinesweeperBoard board(20, 10, GameMode::EASY);
	MSBoardTextView view(board);
	MSTextController ctrl(board, view);

	ctrl.play();


}

