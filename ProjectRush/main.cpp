#include "stdafx.h"
#include "Game.h"

int main()
{
	srand(static_cast<unsigned>(time(0)));

	Game game;

	game.run();

	//End of Application
	return 0;
}
