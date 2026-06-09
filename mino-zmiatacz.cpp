#include <Windows.h>
#include <conio.h>
#include <iostream>

#include "MinesweeperBoard.h"

#include "MSBoardTextView.h"
#include "MSTextController.h"

#include "MSSFMLView.h"
#include "MSSFMLController.h"

#include "MSCheatEngine.h"

int main()
{
	int width, height;
	std::cout << "Welcome to minesweeper, please enter board size:" << std::endl;
	std::cout << "Width: ";
	std::cin >> width;
	std::cout << "Height: ";
	std::cin >> height;
	if (width<0 || height<0) {
		std::cerr << "Invalid input" << std::endl;
	}
	std::cout << "Select gamemode: " << std::endl;
	std::cout << "  1) EASY" << std::endl;
	std::cout << "  2) MEDIUM" << std::endl;
	std::cout << "  3) HARD" << std::endl;
	std::cout << "***************" << std::endl;
	std::cout << "  0) DEBUG" << std::endl;
	char decision;
	do {
		decision = _getch();
	} while (!(decision >= '0' && decision <= '3'));
	GameMode gameMode = DEBUG;
	switch (decision) {
		case '0':
			gameMode = DEBUG;
		break;

		case '1':
			gameMode = EASY;
		break;

		case '2':
			gameMode = NORMAL;
		break;

		case '3':
		default:
			gameMode = HARD;
		break;

	}
	MinesweeperBoard game(width, height, gameMode);
	MSCheatEngine cheat(game);
	
	std::cout << "Select cheats: " << std::endl;
	std::cout << "  1) STANDARD" << std::endl;
	std::cout << "  2) FRAMEWORK SPECIAL" << std::endl;
	std::cout << "  3) FAIR PLAY" << std::endl;
	do {
		decision = _getch();
	} while (!(decision >= '1' && decision <= '3'));
	switch (decision) {
	case '1':
		cheat.enableStandardMode();
		break;

	case '2':
		cheat.enableFrameworkMode();
		break;

	case '3':
		default:
		break;
	}

	std::cout << "Game in: " << std::endl;
	std::cout << "  1) TUI" << std::endl;
	std::cout << "  2) GUI" << std::endl;
	do {
		decision = _getch();
	} while (!(decision >= '1' && decision <= '2'));
	if (decision=='1') {
		MSBoardTextView view(game);
		MSTextController playable(game, view, cheat);
		playable.play();
	}
	else {
		MSSFMLView view(game);
		MSSFMLController playable(game, view, cheat);
		playable.play();
	}

}

