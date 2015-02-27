#include "Sokoban.h"

Sokoban::Sokoban()
{
	gameboards[0].addConnection(&gameboards[3], 0);
	gameboards[0].addConnection(&gameboards[1], 1);
	gameboards[0].addConnection(&gameboards[4], 2);
	gameboards[0].addConnection(&gameboards[5], 3);

	gameboards[1].addConnection(&gameboards[0], 0);
	gameboards[1].addConnection(&gameboards[2], 1);
	gameboards[1].addConnection(&gameboards[4], 2);
	gameboards[1].addConnection(&gameboards[5], 3);

	gameboards[2].addConnection(&gameboards[1], 0);
	gameboards[2].addConnection(&gameboards[3], 1);
	gameboards[2].addConnection(&gameboards[4], 2);
	gameboards[2].addConnection(&gameboards[5], 3);

	gameboards[3].addConnection(&gameboards[2], 0);
	gameboards[3].addConnection(&gameboards[0], 1);
	gameboards[3].addConnection(&gameboards[4], 2);
	gameboards[3].addConnection(&gameboards[5], 3);

	gameboards[4].addConnection(&gameboards[3], 0);
	gameboards[4].addConnection(&gameboards[1], 1);
	gameboards[4].addConnection(&gameboards[2], 2);
	gameboards[4].addConnection(&gameboards[0], 3);

	gameboards[5].addConnection(&gameboards[3], 0);
	gameboards[5].addConnection(&gameboards[1], 1);
	gameboards[5].addConnection(&gameboards[0], 2);
	gameboards[5].addConnection(&gameboards[2], 3);

	load("assets/levels/extended/01.s3d");
}

Sokoban::~Sokoban()
{

}


void Sokoban::load(std::string filename)
{
	std::ifstream file;
	file.open(filename);
	if (!(file.is_open()))
	{
		Logger::log(ERROR_, "Failed to load level");
	}
	typedef std::istreambuf_iterator<char> buf_iter;
	for (buf_iter i(file), e; i != e; ++i){
		processCharacter(*i);
	}
	file.close();
}


void Sokoban::processCharacter(const char& c)
{
	static int currentBoard = 0;
	static int currentX = 0;
	static int currentY = 0;

	if (c == '1')	//Wall
	{
		gameboards[currentBoard].set(1, currentX, currentY);
		addWall(currentX, currentY, currentBoard);
		++currentX;
		return;
	}

	if (c == '2')	//Block
	{
		gameboards[currentBoard].set(2, currentX, currentY);
		addBlock(currentX, currentY, currentBoard);
		++currentX;
		return;
	}

	if (c == '3')	//Switch
	{
		gameboards[currentBoard].set(3, currentX, currentY);
		addSwitch(currentX, currentY, currentBoard);
		++currentX;
		return;
	}

	if (c == '4')	//Player
	{
		gameboards[currentBoard].set(4, currentX, currentY);
		addPlayer(currentX, currentY, currentBoard);
		++currentX;
		return;
	}



	if (c == '\n')	//NEW LINE
	{
		++currentY;
		currentX = 0;

		if (currentY > 8)
		{
			currentY = 0;
			++currentBoard;
		}
		return;
	}
}



void Sokoban::addWall(int x, int y, int face)
{
	float scale = 32.f;
	Entity * e = new Entity();
	if (face == 0)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
				(scale * x) - (scale * 4),
				(scale * y) - (scale * 4),
				-scale * 4
			)
		);
	}
	if (face == 1)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			scale * 4,
			(scale * y) - (scale * 4),
			(scale * x) - (scale * 4)
			)
		);
	}
	if (face == 2)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
				(scale * x) - (scale * 4),
				(scale * y) - (scale * 4),
				scale * 4
			)
		);
	}
	if (face == 3)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
				-scale * 4,
				(scale * y) - (scale * 4),
				(scale * x) - (scale * 4)
			)
		);
	}
	if (face == 4)
	{
		//e->GetTransform()->setPosition(glm::vec3(scale * x, -(scale * y), (scale * 4) + (scale / 2)));
	}
	if (face == 5)
	{
		//e->GetTransform()->setPosition(glm::vec3(scale * x, -(scale * y), -((scale * 4) - (scale / 2))));
	}

	e->GetTransform()->setScale(glm::vec3(scale, scale, scale));

	CGraphics* c = new CGraphics();
	c->addModel("wall/wall.obj");
	c->addMaterial("wall/wall.mat");
	e->addComponent(c, "Graphics");

	addEntity(e);
}

void Sokoban::addPlayer(int x, int y, int face)
{

}

void Sokoban::addSwitch(int x, int y, int face)
{

}

void Sokoban::addBlock(int x, int y, int face)
{

}