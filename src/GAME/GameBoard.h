/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Game Board
Description: 
*********************************************************************/
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <glm/glm.hpp>
#include <vector>

#include "../core/helpers/Keyboard.h"

class GameBoard {
public:
	GameBoard();
	~GameBoard();

	void addConnection(GameBoard*, int);
	void reset();

	void set(int, int, int);
	bool canPlayerMove(int x, int y, int dir); //dir = 0,1,2,3 - +y,-y,-x,+x
	bool canBlockMove(int x, int y, int dir); //dir = 0,1,2,3 - +y,-y,-x,+x

	int board[8][8];
	int face;
	static glm::vec3 playerPosition;

	int switchCount;
	int activeSwitches;

	bool checkComplete();
	bool complete;

private:
	GameBoard* connections[4];

	void MovePlayer(int x, int y, int dir);
	void MoveBlock(int x, int y, int dir);

};
#endif

//GAMEBOARD NOTES
//0 = no object
//1 = wall
//2 = block
//3 = switch
//4 = player
//5 = player on switch
//6 = block on switch