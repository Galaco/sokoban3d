#include "GameBoard.h"

#include "../core/Scene.h"

glm::vec3 GameBoard::playerPosition;

GameBoard::GameBoard()
{
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
	//board.clear();
	playerPosition.x = 0;
	playerPosition.y = 0;
	playerPosition.z = 0;

	for (int i = 0; i < 8; ++i)
	{
		//std::vector<int> v;
		for (int j = 0; j < 8; ++j)
		{
			//v.push_back(0);
			board[i][j] = 0;
		}
		//board.push_back(v);

	}
}


void GameBoard::set(int id, int x, int y)
{
	board[x][y] = id;	//Reversed to keep data parallel will src
}

bool GameBoard::canPlayerMove(int x2, int y2, int dir)
{
	int x = (int)playerPosition.x;
	int y = (int)playerPosition.y;
	
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
			if (canBlockMove(x - 1, y, dir))
			{
				MoveBlock(x, y - 1, dir);
				checkComplete();
				MovePlayer(x, y, dir);
				return true;
			}
		}
	}
	
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
				return true;
			}
		}
	}
	
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
		if (board[y][x-1] == 2)
		{
			if (canBlockMove(x, y - 1, dir))
			{
				MoveBlock(x - 1, y, dir);
				checkComplete();
				MovePlayer(x, y, dir);
				return true;
			}
		}
	}
	
	if (dir == 3)	//Move Right
	{
		if (x == 7)//If going to move off edge
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
				MoveBlock(x + 1, y, dir);
				checkComplete();
				MovePlayer(x, y, dir);
				return true;
			}
		}
	}
	return false;
}

bool GameBoard::canBlockMove(int x, int y, int dir)
{
	if (dir == 0)	//Move Up
	{
		if (board[y - 1][x] == 0 || board[y - 1][x] == 4 || board[y - 1][x] == 3)	//Empty square
		{
			return true;
		}
	}
	if (dir == 1)	//Move Down
	{
		if (board[y + 1][x] == 0 || board[y + 1][x] == 4 || board[y + 1][x] == 3)	//Empty square
		{
			return true;
		}
	}
	if (dir == 2)	//Move Left
	{
		if (board[y][x - 1] == 0 || board[y][x - 1] == 4 || board[y][x - 1] == 3)	//Empty square
		{
			return true;
		}
	}
	if (dir == 3)	//Move Right
	{
		if (board[y][x + 1] == 0 || board[y][x + 1] == 4 || board[y][x + 1] == 3)	//Empty square
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
			set(4, y - 1, x);
			set(0, y, x);
			playerPosition.y--;
		}
		else {	//Next Board
			connections[2]->board[y][7] = 4;
			set(0, y, x);
			playerPosition.y = 0;
			playerPosition.z = (float)connections[2]->face;
		}
	}

	if (dir == 1)	//DOWN
	{
		if (y != 7)
		{
			set(4, y+1, x);
			set(0, y, x);
			playerPosition.y++;
		}
		else {	//Next Board
			connections[3]->board[y][0] = 4;
			set(0, y, x);
			playerPosition.y = 0;
			playerPosition.z = (float)connections[3]->face;
		}
	}

	if (dir == 2)	//LEFT
	{
		if (x != 0)
		{
			set(4, y, x-1);
			set(0, y, x);
			playerPosition.x--;
		}
		else {	//Next Board
			connections[1]->board[7][x] = 4;
			set(0, y, x);
			playerPosition.x = 7;
			playerPosition.z = (float)connections[1]->face;
		}
	}

	if (dir == 3)	//RIGHT
	{
		if (x != 7)
		{
			set(4, y, x+1);
			set(0, y, x);
			playerPosition.x++;
		}
		else {	//Next Board
			connections[0]->board[0][x] = 4;
			set(0, y, x);
			playerPosition.x = 0;
			playerPosition.z = (float)connections[0]->face;
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
			set(5, y - 1, x);	//space now switch+ball
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
			set(2, y - 1, x);	//New Space now ball
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
			set(5, y, x - 1);	//space now switch+ball
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
			set(2, y, x - 1);	//New Space now ball
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

	if (dir == 3)	//RIGHT
	{
		if (board[y][x + 1] == 3)	//Is there a switch
		{
			set(5, y, x + 1);	//space now switch+ball
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
			set(2, y, x + 1);	//New Space now ball
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
}