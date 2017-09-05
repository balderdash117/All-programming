////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									////
////		Name:		Number Guessing Game															////
////																									////
////		Purpose:	All the game functions															////
////																									////
////		Author:		John Pelkman																	////
////																									////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "window.h"
#include "main.h"
#include "Game.h"
#include <time.h>

using std::cin;

void Game::drawMenuChoices(int a_lineNum)
{
	eColor lineColor;

	lineColor = (mGameType == 'a') ? GREEN : WHITE;
	DrawTextLine(1, a_lineNum, lineColor, "a) The computer guesses the number", 100);
	lineColor = (mGameType == 'b') ? GREEN : WHITE;
	DrawTextLine(1, a_lineNum+2, lineColor, "b) I guess the number", 100);
	lineColor = (mGameType == 'c') ? GREEN : WHITE;
	DrawTextLine(1, a_lineNum+4, lineColor, "c) Put system on auto", 100);
}

void Game::setUpGame(int a_width, int a_height)
{
	Rect pLocation = { 0, 0, a_width, a_height  };
	DrawBorder(pLocation, YELLOW);

	//Initialize input lines
	for (int i = 0; i < MAX_LINE_CHAR; ++i) {
		strcpy_s(mLines[i], " ");
	}

	mCurrentLineNumber = 0;
	mLinesX = 80;
	mAdviceX = 100;
	guessNumber = 0;
	gQuitGame = false;
	mGameOver = false;

	bool inputNumber = true;
	int lineNum = 2;
	char ch;
	while (inputNumber) {
		DrawTextLine(1, lineNum + 1, WHITE, "Enter the maximum number (10 - 30000 = ", 100);
		cin >> mMaxNum;
		//Flushing the buffer
		while ((ch = getchar()) != '\n' && ch != EOF); {
		//There is nothing in this segment
	};
		if (mMaxNum < 10 || mMaxNum > 30000) {
			mMaxNum = 0;
			DrawTextLine(1, lineNum, RED, "Enter a correct number", 100);
			DrawTextLine(1, lineNum + 1, WHITE, "                                                      ", 100);
		} else { 
			DrawTextLine(1, lineNum, RED, "                                   ", 100);
			inputNumber = false;
		
		}
	}

	bool inputGameType = true;
	lineNum = 8;
	while (inputGameType) {
		drawMenuChoices(lineNum);
		DrawTextLine(1, lineNum + 7, WHITE, "Enter the maximum number (a, b or c) = ", 100);
		cin >> mGameType;
		//Flushing the buffer
		while ((ch = getchar()) != '\n' && ch != EOF);

		//Bring up a web browser
		if (mGameType == 'w') {
			ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
			ShellExecute(0, 0, L"http://www.aie.edu.au", 0, 0, SW_SHOW);
		}
		if (mGameType < 'a' || mGameType > 'c') {
			mGameType = 0;
			DrawTextLine(1, lineNum + 6, RED, "Enter a, b or c", 100);
			DrawTextLine(1, lineNum + 7, WHITE, "                                    ", 100);
		} else{
			DrawTextLine(1, lineNum + 6, RED, "                                ", 100);
			inputGameType = false;
			drawMenuChoices(lineNum);
		}
	}
	if (mGameType == 'a') {
		bool inputNumber = true;
		lineNum = 18;
		while (inputNumber) {
			DrawTextLine(1, lineNum + 1, WHITE, "Enter a number to guess = ", 100);
			cin >> mGuessNum;
			//Flushing the buffer
			while ((ch = getchar()) != '\n' && ch != EOF);
				//There is nothing in this segment
			if (mGuessNum < 1 || mGuessNum > mMaxNum) {
				mGuessNum = 0;
				DrawTextLine(1, lineNum, RED, "Enter a correct number", 100);
				DrawTextLine(1, lineNum + 1, WHITE, "                                                      ", 100);
			} else {
				DrawTextLine(1, lineNum, RED, "                                   ", 100);
				inputNumber = false;

				}
			}
		} else if (mGameType == 'b') {
		mGuessNum = rand() % mMaxNum + 1;
		} else if (mGameType == 'c') {
			lineNum = 18;
			char tempStr[256];
			sprintf_s(tempStr, "Enter a number to guess = %d", mGuessNum);
			mGuessNum = rand() % mMaxNum + 1;
			DrawTextLine(1, lineNum + 1, WHITE, tempStr, 100);
	}
		mMaxGuess = mMaxNum;
		mMinGuess = 1;

}

void Game::printAllLines()
{
	// write all the current lines, up to mCurrentLineNumber
	for (int y = 0; y <mCurrentLineNumber + 1; ++y) {
		DrawTextLine(mLinesX, y + 1, GREEN, mLines[y], 100);
	}
}

void Game::pauseTillEscapeHit()
{
	// wait until the ESC key is hit, system("pause") would disrupt the screen to much
	while (GetKeyState(VK_ESCAPE) >= 0) {
	}
}

void Game::mainGameLoop()
{
	while (!gQuitGame) {
		//have i exceeded printout
		if (mCurrentLineNumber == MAX_LINE_CHAR) {
			//Initialize input lines
			for (int i = 0; i < MAX_LINE_CHAR; ++i) {
				strcpy_s(mLines[i], "                              ");
			}
			printAllLines();
			mCurrentLineNumber = 0;
		}
		// Is the game over
		if (mGameOver) {
			pauseTillEscapeHit();
			return;
		}
		int trial;
		char ch, guessHigh;
		bool inputInProgress = true;
		switch (mGameType)
		{
		case 'a':
		case 'c':
			trial = (mMaxGuess - mMinGuess) / 2 + mMinGuess;
			sprintf_s(mLines[mCurrentLineNumber], "%3d: %5d", ++guessNumber, trial);
			break;
		case 'b':
			while (inputInProgress) {
				SetXY(mLinesX + 1, mCurrentLineNumber + 1);
				cin >> trial;
				//Flushing the buffer
				while ((ch = getchar()) != '\n' && ch != EOF);

				if (trial >= mMinGuess && trial <= mMaxGuess) {
					sprintf_s(mLines[mCurrentLineNumber], "%3d: %5d", ++guessNumber, trial);
					inputInProgress = false;
				}
			}
			break;
		}
			printAllLines();
			//if (trial == mGuessNum) {
			//	//yeh
			//	SetXY(mLinesX + 1, mCurrentLineNumber + 1);
			//	SetTextColor(GREEN);
			//	cout << "Got it.. " << trial;
			//	pauseTillEscapeHit();
			//	return;
			//}

			//now the high and low guess section
			switch (mGameType) {
			case 'a':
				if (trial == mGuessNum) {
					//yeh
					SetXY(mLinesX + 1, mCurrentLineNumber + 1);
					SetTextColor(GREEN);
					cout << "Got it.. " << trial;
					pauseTillEscapeHit();
					return;
				}
				while (inputInProgress) {
					SetXY(mAdviceX, mCurrentLineNumber + 1);
					cin >> guessHigh;
					//Flushing the buffer
					while ((ch = getchar()) != '\n' && ch != EOF);
					if (guessHigh == 'h') mMaxGuess = trial, inputInProgress = false;
					if (guessHigh == 'l') mMinGuess = trial, inputInProgress = false;

				}
				mCurrentLineNumber++;
				break;
			case 'b':
			case 'c':
				if (trial < mGuessNum) {
					//Higher
					mMinGuess = trial;
					strcat_s(mLines[mCurrentLineNumber], " Low");
				}
				if (trial > mGuessNum) {
					//Lower
					mMaxGuess = trial;
					strcat_s(mLines[mCurrentLineNumber], " Higher");
				}
				mCurrentLineNumber++;
				printAllLines();
				break;
			}
	}
	
}
