#pragma once
#include "MinesweeperBoard.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MSSFMLView
{
public:
	MSSFMLView(MinesweeperBoard& _b);

	const void display(const bool& _debug);
	const void showScene(sf::RenderWindow& _window);

private:
	struct Scene //all assets here
	{
		sf::Image textures;
		sf::Texture coveredFields[3];
		sf::Texture unCoveredFields[10];
		sf::Texture flag;
		std::vector<std::vector<std::pair<bool,sf::Sprite>>> fields; //Playing board
		std::vector<std::vector<sf::Sprite>> flags; //Flags
	};

	Scene activeScene;

	//only at start, then only update
	Scene createScene();
	const void renderFlags(Scene& _s);
	const void renderFields(Scene& _s);
	const void renderFieldsDebug(Scene& _s);

	//the below functions update the view every frame
	const void updateScene(Scene& _s);

	void drawScene(sf::RenderWindow& _window,Scene& _s);

	MinesweeperBoard& board;
	int boardHeight;
	int boardWidth;
};


