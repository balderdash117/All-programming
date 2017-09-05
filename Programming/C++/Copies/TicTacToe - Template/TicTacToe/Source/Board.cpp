////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									
////		Name:		board.cpp																		
////																									
////		Purpose:	all game board events
////		Uses:		http://code.runnable.com/Vnjjxm6IJit89Bpu/tic-tac-toe-unbeatable-ai-for-c%2B%2B
////					to show how to run a simple recusive board routine																				
////																									
////		Authors:	Roger Keating with assistance from Brody								
////																									
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include "Board.h"
#include "window.h"

using std::cin;
using std::endl;

// constructor
Board::Board()
{
	firstPlayerIsHuman = true;

	for (int x = 0; x<3; ++x)
		for (int y = 0; y<3; ++y)
			m_grid[x][y] = ' ';

	mTopX = 31;
	mTopY = 6;
	mBoardWidth = 57;
	mBoardHeight = 27;
}

// Why is there no destuctor????

// the main game loop
void Board::mainLoop(int a_width, int a_height)
{
}

// print the board
void Board::Print()
{
	short ptX[] = { mTopX + 5, mTopX + 25, mTopX + 45 };
	short ptY[] = { mTopY + 1, mTopY + 11, mTopY + 20 };
	eColor oColor = ORANGE;
	char oValue[][20] = {
		"OOOOOOO",
		"O     O",
		"O     O",
		"O     O",
		"O     O",
		"OOOOOOO"
	};
	eColor xColor = YELLOW;
	char xValue[][20] = {
		"       ",
		" x   x ",
		"  x x  ",
		"   x   ",
		"  x x  ",
		" x   x "
	};

	for (int x = 0; x<3; ++x)
		for (int y = 0; y < 3; ++y) {
			if (m_grid[x][y] == ' ') continue;

			for (int i = 0; i < 6; ++i) {
				SetXY(ptX[x], ptY[y] + i);
				SetTextColor((m_grid[x][y] == 'x' ? xColor : oColor));
				cout << (m_grid[x][y] == 'x' ? xValue[i] : oValue[i]) << endl;
			}
	}
}

// is there a winner
bool Board::IsWinner(int& a_outWinner) const
{
	// check rows
	for (int i = 0; i < 3; ++i)
	{
		// same across row
		if (m_grid[i][0] != ' ' && m_grid[i][0] == m_grid[i][1] && m_grid[i][1] == m_grid[i][2])
		{
			a_outWinner = m_grid[i][0] == 'x' ? 0 : 1;
			return true;
		}
	}

	// check columns
	for (int i = 0; i < 3; ++i)
	{
		// same down column
		if (m_grid[0][i] != ' ' && m_grid[0][i] == m_grid[1][i] && m_grid[1][i] == m_grid[2][i])
		{
			a_outWinner = m_grid[0][i] == 'x' ? 0 : 1;
			return true;
		}
	}

	// check diagonal (top left)
	if (m_grid[0][0] != ' ' && m_grid[0][0] == m_grid[1][1] && m_grid[1][1] == m_grid[2][2])
	{
		a_outWinner = m_grid[0][0] == 'x' ? 0 : 1;
		return true;
	}

	// check diagonal (top right)
	if (m_grid[2][0] != ' ' && m_grid[2][0] == m_grid[1][1] && m_grid[1][1] == m_grid[0][2])
	{
		a_outWinner = m_grid[2][0] == 'x' ? 0 : 1;
		return true;
	}

	// no winner found
	a_outWinner = -1;
	return false;
}

// is it a draw
bool Board::IsDraw() const
{
	// no winner means it might be a draw
	int winnerIdx;
	if (!IsWinner(winnerIdx))
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				// we still have a cell in the grid without a choice
				if (m_grid[i][j] != 'x' &&
					m_grid[i][j] != 'o')
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool Board::ResolveIndex(int a_index1D, int& a_outX, int& a_outY) const
{
	a_outY = a_index1D % 3;
	a_outX = a_index1D / 3;

	// was the given index even on the grid?
	return a_index1D >= 0 && a_index1D < 9;
}

// AI steps - this is the 'imported' code
char Board::check_win(char board[3][3]) {

	// Check horizontal, vertical & diagonal through [0][0]
	if (board[0][0] != '.' && (board[0][0] == board[0][1] && board[0][0] == board[0][2] ||
		board[0][0] == board[1][0] && board[0][0] == board[2][0] ||
		board[0][0] == board[1][1] && board[0][0] == board[2][2]))

		return board[0][0];

	// Check horizontal, vertical & diagonal through [1][1]
	if (board[1][1] != '.' && (board[1][1] == board[1][0] && board[1][1] == board[1][2] ||
		board[1][1] == board[0][1] && board[1][1] == board[2][1] ||
		board[1][1] == board[2][0] && board[1][1] == board[0][2]))

		return board[1][1];

	// Check horizontal, vertical & diagonal through [2][2]
	if (board[2][2] != '.' && (board[2][2] == board[0][2] && board[2][2] == board[1][2] ||
		board[2][2] == board[2][0] && board[2][2] == board[2][1]))

		return board[2][2];

	return 0;
}

// AI steps 
int Board::pick_best_move(char board[3][3], char player1, char player2)
{
	int best_move_score = -9999;
	int best_move_row = -9999;
	int best_move_col = -9999;
	int score_for_this_move = 0;

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (board[r][c] == ' ') {
				board[r][c] = player1; //Try test move.
				score_for_this_move = -(negamax(board, player2, player1));
				board[r][c] = ' '; //Put back test move.
				if (score_for_this_move >= best_move_score) {
					best_move_score = score_for_this_move;
					best_move_row = r;
					best_move_col = c;
				}
			}
		}
	}
	return (10 * best_move_row + best_move_col);
}

/*********************************************************************
** Function: negamax
** Description: Recursively calls itself to play out every possible
** position.
** Parameters: char[3][3], char, char
** Pre-Conditions: pick_best_move has been called.
** Post-Conditions: Returns best_score_move to pick_best_move
*********************************************************************/
int Board::negamax(char board[3][3], char player1, char player2) {

	int best_move_score = -9999;
	int score_for_this_move = 0;

	//If player 1 wins, then the score is high (good for player1)
	if (check_win(board) == player1) return 1000;

	//If player 2 loses, then the score is low (bad for player1)
	else if (check_win(board) == player2) return -1000;

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (board[r][c] == '.') {
				board[r][c] = player1; //Try test move.
				score_for_this_move = -(negamax(board, player2, player1));
				board[r][c] = '.'; //Put back test move.
				if (score_for_this_move >= best_move_score) {
					best_move_score = score_for_this_move;
				}
			}
		}
	}

	if (best_move_score == -9999 || best_move_score == 0) return 0;

	else if (best_move_score < 0) return best_move_score + 1;

	else if (best_move_score > 0)
		return best_move_score - 1; //As the game goes longer, and the recursion goes deeper, the moves near the end are less favorable than in the beginning.

	return 0;
}

void Board::get_computer_move() //AI move input
{
#if 0 // one easy way
	int i, j;
	for (i = 0; i<3; i++) {
		for (j = 0; j<3; j++)
			if (m_grid[i][j] == ' ') break;
		if (m_grid[i][j] == ' ') break;
	}

	if (i*j == 9) {
		return;
	} else
		m_grid[i][j] = 'o';
#else // second easy way
	//If the space is empty
	if (m_grid[0][0] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[0][0] = 'o';
	}
	else if (m_grid[1][0] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[1][0] = 'o';
	}
	else if (m_grid[2][0] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[2][0] = 'o';
	}
	else if (m_grid[0][1] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[0][1] = 'o';
	}
	else if (m_grid[1][1] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[1][1] = 'o';
	}
	else if (m_grid[1][2] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[1][2] = 'o';
	}
	else if (m_grid[2][0] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[2][0] = 'o';
	}
	else if (m_grid[2][1] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[2][1] = 'o';
	}
	else if (m_grid[2][2] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[2][2] = 'o';
	}
#endif
}

// hit the board with the mouse
void Board::checkMouseHit(COORD a_pt)
{
}
