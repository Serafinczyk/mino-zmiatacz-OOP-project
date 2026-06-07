#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"

int main()
{
		MinesweeperBoard mb(5, 7, DEBUG);
		MSSFMLView view(mb);
		mb.revealField(1, 2);
		view.display(1);


}

