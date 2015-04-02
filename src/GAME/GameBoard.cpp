#include "GameBoard.h"

glm::vec3* GameBoard::playerPosition;

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
	board[y][x] = id;	//Reversed to keep data parallel will src
}

bool GameBoard::canPlayerMove(int x2, int y2, int dir)
{
	int x = playerPosition->x;
	int y = playerPosition->y;
	//For a non-edge position
	if (dir == 0)	//Move Up
	{
		if (y == 0)
		{
			if (connections[2]->board[7][x] == 0)
			{
				MovePlayer(x, y, dir);
				return true;
			}
		}
		if (board[y-1][x] == 0 || board[y-1][x] == 4)	//Empty square
		{
			MovePlayer(x, y, dir);
			return true;
		}
		if (board[y-1][x] == 2)
		{
			if (canBlockMove(x, y - 1, dir))
			{
				MoveBlock(x, y, dir);
				MovePlayer(x, y, dir);
			}
			return true;
		}
	}
	else
	if (dir == 1)	//Move Down
	{
		if (y == 7)
		{
			if (connections[3]->board[0][x] == 0)
			{
				MovePlayer(x, y, dir);
				return true;
			}
		}
		if (board[y + 1][x] == 0 || board[y + 1][x] == 4)	//Empty square
		{
			MovePlayer(x, y, dir);
			return true;
		}
		if (board[y + 1][x] == 2)
		{
			if (canBlockMove(x + 1, y, dir))
			{
				MoveBlock(x, y, dir);
				MovePlayer(x, y, dir);
			}
			return true;
		}
	}
	else
	if (dir == 2)	//Move Left
	{
		if (x == 0)
		{
			if (connections[1]->board[y][7] == 0)
			{
				MovePlayer(x, y, dir);
				return true;
			}
		}
		if (board[y][x - 1] == 0 || board[y][x-1] == 4)	//Empty square
		{
			MovePlayer(x, y, dir);
			return true;
		}
		if (board[y][x-1] == 2)
		{
			if (canBlockMove(x, y-1, dir))
			{
				MoveBlock(x, y, dir);
				MovePlayer(x, y, dir);
			}
			return true;
		}
	}
	else
	if (dir == 3)	//Move Right
	{
		if (x == 7)
		{
			if (connections[0]->board[y][0] == 0)
			{
				MovePlayer(x, y, dir);
				return true;
			}
		}
		if (board[y][x + 1] == 0 || board[y][x+1] == 4)	//Empty square
		{
			MovePlayer(x, y, dir);
			return true;
		}
		if (board[y][x + 1] == 2)
		{
			if (canBlockMove(x, y + 1, dir))
			{
				MoveBlock(x, y, dir);
				MovePlayer(x, y, dir);
			}
			return true;
		}
	}
	return false;
}

bool GameBoard::canBlockMove(int x, int y, int dir)
{
	//For a non-edge position
	if (dir == 0)	//Move Up
	{
		if (y == 0)
		{
			if (connections[2]->board[7][x] == 0)
			{
				return true;
			}
		}
		if (this->board[y][x-1] == 0)	//Empty square
		{
			return true;
		}
	}
	else
		if (dir == 1)	//Move Down
		{
			if (y == 7)
			{
				if (connections[3]->board[0][x] == 0)
				{
					return true;
				}
			}
			if (board[y + 1][x] == 0)	//Empty square
			{
				return true;
			}
		}
		else
			if (dir == 2)	//Move Left
			{
				if (x == 0)
				{
					if (connections[1]->board[y][7] == 0)
					{
						return true;
					}
				}
				if (board[y][x - 1] == 0)	//Empty square
				{
					return true;
				}
			}
			else
				if (dir == 3)	//Move Right
				{
					if (x == 7)
					{
						if (connections[0]->board[y][0] == 0)
						{
							return true;
						}
					}
					if (board[y][x + 1] == 0)	//Empty square
					{
						return true;
					}
				}
	return false;

}

void GameBoard::MovePlayer(int x, int y, int dir)
{
	if (dir == 0)		//UP
	{
		if (y != 0)
		{
			board[x - 1][y] = 4;
			board[y][x] = 0;
			playerPosition->y--;
		}
		else {	//Next Board
			connections[2]->board[y][7] = 4;
			board[y][x] = 0;
			playerPosition->y = 0;
			playerPosition->z = connections[2]->face;
		}
	}
	else

		if (dir == 1)	//DOWN
		{
			if (y != 7)
			{
				board[x + 1][y] = 4;
				board[y][x] = 0;
				playerPosition->y++;
			}
			else {	//Next Board
				connections[3]->board[y][0] = 4;
				board[y][x] = 0;
				playerPosition->y = 0;
				playerPosition->z = connections[3]->face;
			}
		}
		else
			if (dir == 2)	//LEFT
			{
				if (x != 0)
				{
					board[y][x - 1] = 4;
					board[y][x] = 0;
					playerPosition->x--;
				}
				else {	//Next Board
					connections[1]->board[7][x] = 4;
					board[y][x] = 0;
					playerPosition->x = 7;
					playerPosition->z = connections[1]->face;
				}
			}
			else
				if (dir == 3)	//RIGHT
				{
					if (x != 7)
					{
						board[y][x + 1] = 4;
						board[y][x] = 0;
						playerPosition->x++;
					}
					else {	//Next Board
						connections[0]->board[0][x] = 4;
						board[y][x] = 0;
						playerPosition->x = 0;
						playerPosition->z = connections[0]->face;
					}
				}
}

void GameBoard::MoveBlock(int x, int y, int dir)
{
	if (dir == 0)		//UP
	{
		if (y != 0)
		{
			board[x - 1][y] = 2;
			board[y][x] = 0;
		}
		else {	//Next Board
			connections[2]->board[y][7] = 2;
			board[y][x] = 0;
		}
	}
	else

		if (dir == 1)	//DOWN
		{
			if (y != 7)
			{
				board[x + 1][y] = 2;
				board[y][x] = 0;
			}
			else {	//Next Board
				connections[3]->board[y][0] = 2;
				board[y][x] = 0;
			}
		}
		else
			if (dir == 2)	//LEFT
			{
				if (x != 0)
				{
					board[y][x - 1] = 2;
					board[y][x] = 0;
				}
				else {	//Next Board
					connections[1]->board[7][x] = 2;
					board[y][x] = 0;
				}
			}
			else
				if (dir == 3)	//RIGHT
				{
					if (x != 7)
					{
						board[y][x + 1] = 2;
						board[y][x] = 0;
					}
					else {	//Next Board
						connections[0]->board[0][x] = 2;
						board[y][x] = 0;
					}
				}
}