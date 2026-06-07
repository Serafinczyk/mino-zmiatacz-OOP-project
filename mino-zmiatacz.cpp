#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"

int main()
{
	MinesweeperBoard board(5, 5, GameMode::EASY);
	MSBoardTextView view(board);
	MSCheatEngine sussObject(board);
	//sussObject.enableFrameworkMode();
	sussObject.enableStandardMode();
	MSTextController ctrl(board, view, sussObject);

	ctrl.play();


}

