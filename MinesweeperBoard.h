#pragma once
#include <vector>
#include <iostream>
#include <random>

struct Field {
	bool hasMine;
	bool hasFlag;
	bool isRevealed;
};

enum GameMode {
	EASY = 10,
	NORMAL = 20,
	HARD = 30,
	DEBUG = 0
};

enum GameState {
	RUNNING = 0,
	FINISHED_WIN = 1,
	FINISHED_LOSS = -1
};

class MinesweeperBoard
{
	public:
		//Constructors
		MinesweeperBoard();
		MinesweeperBoard(int _width, int _height, GameMode _mode);

		//Debug function to display the board in console
		void debug_display() const;

		//Getters
		int getBoardWidth() const;
		int getBoardHeight() const;
		int getMineCount() const;

		//Game logic functions
		int countMines(int _row, int _col) const;
		bool hasFlag(int _row, int _col) const;
		void toggleFlag(int _row, int _col);
		void revealField(int _row, int _col);

	private:
		//Board data
		int width;
		int height;
		int minesCount;
		bool waitingForFirstMove; //To ensure that the first move is always safe
		std::vector<std::vector<Field>> board;
		GameState gameState;
		GameMode gameMode;

		//Helpers and initializers
		void initializeBoard(int _height, int _width);
		void initializeRandomDevice();
		void placeMinesAtHardCodedPos();
		void placeMinesInDebugMode();
		void placeMinesRandomly(int _minesToPlace);
		void moveMine(int _row, int _col);
		void revealAllMines();

		//Randomness for mines placement
		std::random_device randomDevice;
		std::mt19937 randomGenerator;
		std::uniform_int_distribution<> randomDistributionForRow;
		std::uniform_int_distribution<> randomDistributionForCol;
};

