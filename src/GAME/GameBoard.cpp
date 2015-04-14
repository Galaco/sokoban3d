#include "GameBoard.h"

#include "../core/Scene.h"

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
	switchCount = 0;
	activeSwitches = 0;
	complete = false;
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
	board[x][y] = id;	//Reversed to keep data parallel will src
}

bool GameBoard::canPlayerMove(int x2, int y2, int dir)
{
	int x = playerPosition->x;
	int y = playerPosition->y;
	
	if (dir == 0)	//Move Up
	{
		if (y == 0)//If going to move off edge
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
		if (y == 7)//If going to move off edge
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
				MoveBlock(x, y + 1, dir);
				checkComplete();
				MovePlayer(x, y, dir);
			}
			return true;
		}
	}
	else
	if (dir == 2)	//Move Left
	{
		if (x == 0)//If going to move off edge
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
		if (board[y][x-1] == 2)//If going to move off edge
		{
			if (canBlockMove(x-1, y, dir))
			{
				MoveBlock(x, y, dir);
				checkComplete();
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
		if (board[y][x + 1] == 0 || board[y][x + 1] == 4)	//Empty square
		{
			MovePlayer(x, y, dir);
			return true;
		}
		if (board[y][x + 1] == 2 || board[y][x + 1] == 5)
		{
			if (canBlockMove(x + 1, y, dir))
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
	if (dir == 0)	//Move Up
	{
		if (board[y - 1][x] == 0 || board[y][x - 1] == 4)	//Empty square
		{
			return true;
		}
	}
	if (dir == 1)	//Move Down
	{
		if (board[y + 1][x] == 0 || board[y][x - 1] == 4)	//Empty square
		{
			return true;
		}
	}
	if (dir == 2)	//Move Left
	{
		if (board[y][x - 1] == 0 || board[y][x - 1] == 4)	//Empty square
		{
			return true;
		}
	}
	if (dir == 3)	//Move Right
	{
		if (board[y][x + 1] == 0 || board[y][x + 1] == 4)	//Empty square
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
			board[y - 1][x] = 4;
			set(0, y, x);
			playerPosition->y--;
		}
		else {	//Next Board
			connections[2]->board[y][7] = 4;
			set(0, y, x);
			playerPosition->y = 0;
			playerPosition->z = connections[2]->face;
		}
	}

		if (dir == 1)	//DOWN
		{
			if (y != 7)
			{
				set(4, y+1, x);
				set(0, y, x);
				playerPosition->y++;
			}
			else {	//Next Board
				connections[3]->board[y][0] = 4;
				set(0, y, x);
				playerPosition->y = 0;
				playerPosition->z = connections[3]->face;
			}
		}

			if (dir == 2)	//LEFT
			{
				if (x != 0)
				{
					board[y][x - 1] = 4;
					set(0, y, x);
					playerPosition->x--;
				}
				else {	//Next Board
					connections[1]->board[7][x] = 4;
					set(0, y, x);
					playerPosition->x = 7;
					playerPosition->z = connections[1]->face;
				}
			}

				if (dir == 3)	//RIGHT
				{
					if (x != 7)
					{
						board[y][x + 1] = 4;
						set(0, y, x);
						playerPosition->x++;
					}
					else {	//Next Board
						connections[0]->board[0][x] = 4;
						set(0, y, x);
						playerPosition->x = 0;
						playerPosition->z = connections[0]->face;
					}
				}
}



bool GameBoard::checkComplete()
{
	if (this->switchCount == this->activeSwitches)
	{
		if (!complete)
		{
			Scene::completeSides++;
			complete = true;
		}
	}
	else {
		complete = false;
	}

	return complete;
}

void GameBoard::MoveBlock(int x, int y, int dir)
{
	if (dir == 0)		//UP
	{
		if (board[y - 1][x] == 3)	//Is there a switch
		{
			set(5, y - 1, x);	//Old space now switch+ball
			activeSwitches++;
		}
		else {
			set(2, y - 1, x);	//Old space now ball
		}
		if (board[y][x] == 5)		//Is the ball already on the switch?
		{
			set(3, y, x);		//Old space now switch
			activeSwitches--;
		}
		else {
			set(0, y, x);		//Old space now empty
		}
	}

	if (dir == 1)	//DOWN
	{
		if (board[y + 1][x] == 3)	//Is there a switch
		{
			set(5, y + 1, x);	//space now switch+ball
			activeSwitches++;
			checkComplete();
			if (!(switchCount != activeSwitches) && switchCount == activeSwitches)
			{
				complete = true;
			}
			else {
				complete = false;
			}
		}
		else {
			set(2, y + 1, x);	//New Space now ball
		}
		if (board[y][x] == 5)		//Is the ball already on the switch?
		{
			set(3, y, x);		//Old space now switch
			activeSwitches--;
			return;
		}
		else {
			set(0, y, x);		//Old space now empty
			return;
		}
	}
	
	if (dir == 2)	//LEFT
	{
		if (board[y][x - 1] == 3)	//Is there a switch
		{
			set(5, y, x-1);	//Old space now switch+ball
			activeSwitches++;
		}
		else {
			set(2, y, x - 1);	//Old space now ball
		}
		if (board[y][x] == 5)		//Is the ball already on the switch?
		{
			set(3, y, x);		//Old space now switch
			activeSwitches--;
		}
		else {
			set(0, y, x);		//Old space now empty
		}
	}

	if (dir == 3)	//RIGHT
	{
		if (board[y][x + 1] == 3)	//Is there a switch
		{
			set(5, y, x+1);	//Old space now switch+ball
			activeSwitches++;
		}
		else {
			set(2, y, x+1);	//Old space now ball
		}
		if (board[y][x] == 5)		//Is the ball already on the switch?
		{
			set(3, y, x);		//Old space now switch
			activeSwitches--;
		}
		else {
			set(0, y, x);		//Old space now empty
		}	
	}

}