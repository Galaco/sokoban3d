/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Sokoban
Description: 
*********************************************************************/
#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <map>

#include <core/Scene.h>
#include "GameBoard.h"
#include "../Components/CAnimation.h"
#include "../Components/CGraphics.h"
#include "../Components/CLuaScript.h"

class Sokoban : public Scene {
public:
	Sokoban();
	~Sokoban();

	bool load(std::string);

	void update(float dt);

	void reset();

	void nextLevel();

	float elapsedTime;
	static int level;

	struct BoardLoader{
		int currentBoard = 0;
		int currentX = 0;
		int currentY = 0;
	};

	static BoardLoader boardloader;
	bool gameOver;
	float gameCompleteTime;

private:
	void processCharacter(const char& c);

	void addWall(int x, int y, int face);
	void addFloor();
	void addPlayer(int x, int y, int face);
	void addSwitch(int x, int y, int face);
	void addBlock(int x, int y, int face);
	void addHud();

	Entity* player;

	int numSwitches;
};
#endif
