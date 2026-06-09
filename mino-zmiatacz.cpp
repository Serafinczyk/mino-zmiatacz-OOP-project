#include <windows.h>
#include "MinesweeperBoard.h"
#include "MSSFMLView.h"

int main()
{
		MinesweeperBoard mb(50, 50, EASY);
		MSSFMLView view(mb);
		mb.revealField(10, 2);
		view.display(0);


}

