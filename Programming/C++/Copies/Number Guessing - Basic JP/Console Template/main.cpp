////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									////
////		Name:		Number Guessing Game															////
////																									////
////		Purpose:	Main program																	////
////																									////
////		Author:		John Pelkman 																	////
////																									////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "window.h"
#include "main.h"
#include <time.h>
#include "Game.h"

using std::cin;

int main()
{
	Game game;

	// randomize the guessing
	srand((unsigned int)time(NULL));

	// initalize the window
	// (140, 80) is a the maximum
	int width	= 120;
	int height	= 40;
	bool result = game.Initialise(width, height, L"Number Guessing Game");

	if (result == EXIT_FAILURE)
		return EXIT_FAILURE;

	// go to the game
	game.setUpGame(width, height);
	game.mainGameLoop();

	system("pause");
	return EXIT_SUCCESS;
}


