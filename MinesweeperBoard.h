#pragma once
#include <vector>

class MinesweeperBoard
{
	public:
		MinesweeperBoard();

		struct Field {
			bool hasMine;
			bool hasFlag;
			bool isRevealed;
		};

	private:
		int width;
		int height;
		std::vector<std::vector<Field>> board;
		void initializeBoard(int _width, int _eight);
		void placeMinesAtHardCodedPos();

};

