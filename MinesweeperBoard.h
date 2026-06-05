#pragma once
#include <vector>
#include <iostream>
#include <random>

enum GameMode {
	EASY = 10,
	NORMAL = 20,
	HARD = 30,
	DEBUG = 0
};

class MinesweeperBoard
{
	public:
		MinesweeperBoard();
		MinesweeperBoard(int _width, int _height, GameMode _mode);

		void debug_display() const;

		struct Field {
			bool hasMine;
			bool hasFlag;
			bool isRevealed;
		};

	private:
		int width;
		int height;
		std::vector<std::vector<Field>> board;

		void initializeBoard(int _height, int _width);
		void initializeRandomDevice();
		void placeMinesAtHardCodedPos();
		void placeMinesInDebugMode();
		void placeMinesRandomly(int _minesToPlace);

		//Randomness for mines placement
		std::random_device randomDevice;
		std::mt19937 randomGenerator;
		std::uniform_int_distribution<> randomDistributionForRow;
		std::uniform_int_distribution<> randomDistributionForCol;
};

