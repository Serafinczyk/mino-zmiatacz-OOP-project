#pragma once
#include "MinesweeperBoard.h"
#include "MSCheatEngine.h"
#include "MSSFMLView.h"
#include <SFML/Graphics.hpp>

class MSSFMLController
{
public:
	MSSFMLController(MinesweeperBoard& _board, MSSFMLView& _view, MSCheatEngine& cheat);
	~MSSFMLController();
	void play();

private:
	MinesweeperBoard& board;
	MSSFMLView& view;
	MSCheatEngine& cheatEngine;
	sf::Vector2u windowSize;
	sf::RenderWindow window;

	int fieldHeight;
	int fieldWidth;
	int boardHeight;
	int boardWidth;

	void calcFieldSize();
};

