#pragma once
#include <windows.h>
#include <iostream>
#include "MinesweeperBoard.h"

class MSCheatEngine
{
	public:
		MSCheatEngine(MinesweeperBoard& _board);
		~MSCheatEngine();
		void enableStandardMode();
		void enableFrameworkMode();
		void spyOnTile(int _row, int _col);
	private:
		HANDLE serialDevice;
		DCB serialSettings;
		bool serialVersion;
		bool enabled;
		MinesweeperBoard& board;
};

