#include "MinesweeperBoard.h"
#include "MSSFMLView.h"

int main()
{
		MinesweeperBoard mb(5, 7, DEBUG);
		MSSFMLView view(mb);
		mb.revealField(1, 2);
		view.display(1);


}

