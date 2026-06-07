#pragma once
#include "MinesweeperBoard.h"

class MSSFMLView
{
public:
	MSSFMLView(MinesweeperBoard& b);

	const void display(const bool& debug);

private:
	struct Scene
	{
		//assets here
	};

	Scene createScene();
	//the below functions update the view every frame
	const void updateScene(Scene& s);
	const void updateSceneDebug(Scene& s);

	MinesweeperBoard& board;
};


