#include "GameBoard.h"

GameBoard::GameBoard()
{
	reset();
}

GameBoard::~GameBoard()
{

}


void GameBoard::addConnection(GameBoard* gameboard, int index)
{
	//Index is L,R,U,D
	connections[index] = gameboard;
}

void GameBoard::reset()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			board[i][j] = 0;
		}
	}
}


void GameBoard::set(int id, int x, int y)
{
	board[y][x] = id;
}