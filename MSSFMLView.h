#pragma once
#include "MinesweeperBoard.h"

#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"

class MSSFMLView
{
public:
	MSSFMLView(MinesweeperBoard& _b);

	const void display(const bool& _debug);

private:
	struct Scene
	{
		//assets here
	};

	Scene createScene();
	//the below functions update the view every frame
	const void updateScene(Scene& _s);
	const void updateSceneDebug(Scene& _s);

	MinesweeperBoard& board;
};


