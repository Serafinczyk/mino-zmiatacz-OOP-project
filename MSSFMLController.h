#pragma once
#include "MinesweeperBoard.h"
#include "MSSFMLView.h"

class MSSFMLController
{
public:
	MSSFMLController(MinesweeperBoard& _board, MSSFMLView& _view, MSCheatEngine& cheat);
	~MSSFMLController();
	void play();

private:
	
};

