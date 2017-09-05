////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									
////		Name:		Tic Tac Toe template															
////																									
////		Purpose:	Main program																	
////																									
////		Author:		Ben Alder 27/2/2017																
////																									
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Board.h"
#include "window.h"
#include <time.h>


int main()
{
	Board board;

	// randomize the guessing
	srand((unsigned int)time(NULL));

	// initalize the window
	// (140, 80) is a the maximum
	int width = 120;
	int height = 40;
	bool result = board.Initialise(width, height, "Tic Tac Toe");

	if (result == EXIT_FAILURE)	return EXIT_FAILURE;

	board.mainLoop(width, height);

	system("pause");
	return 0;
}
