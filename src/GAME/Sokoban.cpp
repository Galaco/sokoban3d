#include "Sokoban.h"

Sokoban::Sokoban()
{
	//FRONT
	gameboards[0].addConnection(&gameboards[1], 0); //R
	gameboards[0].addConnection(&gameboards[3], 1); //l
	gameboards[0].addConnection(&gameboards[5], 2); //u
	gameboards[0].addConnection(&gameboards[4], 3); //d
	gameboards[0].face = 0;
	//RIGHT
	gameboards[1].addConnection(&gameboards[2], 0);
	gameboards[1].addConnection(&gameboards[0], 1);
	gameboards[1].addConnection(&gameboards[5], 2);
	gameboards[1].addConnection(&gameboards[4], 3);
	gameboards[1].face = 1;
	//BACK
	gameboards[2].addConnection(&gameboards[3], 0);
	gameboards[2].addConnection(&gameboards[1], 1);
	gameboards[2].addConnection(&gameboards[5], 2);
	gameboards[2].addConnection(&gameboards[4], 3);
	gameboards[2].face = 2;
	//LEFT
	gameboards[3].addConnection(&gameboards[0], 0);
	gameboards[3].addConnection(&gameboards[2], 1);
	gameboards[3].addConnection(&gameboards[5], 2);
	gameboards[3].addConnection(&gameboards[4], 3);
	gameboards[3].face = 3;
	//UP
	gameboards[4].addConnection(&gameboards[3], 0);
	gameboards[4].addConnection(&gameboards[1], 1);
	gameboards[4].addConnection(&gameboards[2], 2);
	gameboards[4].addConnection(&gameboards[0], 3);
	gameboards[4].face = 4;
	//DOWN
	gameboards[5].addConnection(&gameboards[3], 0);
	gameboards[5].addConnection(&gameboards[1], 1);
	gameboards[5].addConnection(&gameboards[0], 2);
	gameboards[5].addConnection(&gameboards[2], 3);
	gameboards[5].face = 5;

	load("assets/levels/extended/01.s3d");

	GameBoard::playerPosition = &playerPosition;
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



	addFloor();
}


void Sokoban::processCharacter(const char& c)
{
	static int currentBoard = 0;
	static int currentX = 0;
	static int currentY = 0;

	if (c == '0')		// Empty Square
	{
		++currentX;
		return;
	}
	if (c == '1')	//Wall
	{
		gameboards[currentBoard].set(1, currentX, currentY);
		originalgameboards[currentBoard].set(1, currentX, currentY);
		addWall(currentX, currentY, currentBoard);
		++currentX;
		return;
	}
	if (c == '2')	//Block
	{
		gameboards[currentBoard].set(2, currentX, currentY);
		originalgameboards[currentBoard].set(2, currentX, currentY);
		addBlock(currentX, currentY, currentBoard);
		++currentX;
		return;
	}
	if (c == '3')	//Switch
	{
		gameboards[currentBoard].set(3, currentX, currentY);
		originalgameboards[currentBoard].set(3, currentX, currentY);
		addSwitch(currentX, currentY, currentBoard);
		++currentX;
		return;
	}

	if (c == '4')	//Player
	{
		gameboards[currentBoard].set(4, currentX, currentY);
		originalgameboards[currentBoard].set(4, currentX, currentY);
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
				-(scale * 4) - scale
			)
		);
	}
	if (face == 1)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * 4),
			(scale * y) - (scale * 4),
			(scale * x) - (scale * 4)
			)
		);
	}
	if (face == 2)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
				(scale * (7-x)) - (scale * 4),
				(scale * y) - (scale * 4),
				(scale * 4)
			)
		);
	}
	if (face == 3)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
				-(scale * 4) - scale,
				(scale * y) - (scale * 4),
				(scale * x) - (scale * 4)
			)
		);
	}
	if (face == 4)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			(scale * 4),
			(scale * y) - (scale * 4)
			)
		);
	}
	if (face == 5)
	{

		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			-(scale * 4) - scale,
			(scale * y) - (scale * 4)
			)
		);
	}

	e->GetTransform()->setScale(glm::vec3(scale, scale, scale));

	CGraphics* c = new CGraphics();
	c->addModel("wall/cube.obj");
	c->addMaterial("wall/wall.mat");
	e->addComponent(c, "Graphics");

	addEntity(*e);
}

void Sokoban::addPlayer(int x, int y, int face)
{
	float scale = 32.f;
	player = new Entity("PLAYER");
	if (face == 0)
	{
		player->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			(scale * y) - (scale * 4),
			-(scale * 4) - scale
			)
			);
	}
	if (face == 1)
	{
		player->GetTransform()->setPosition(
			glm::vec3(
			(scale * 4) - scale / 2,
			(scale * y) - (scale * 4),
			(scale * x) - (scale * 4)
			)
			);
	}
	if (face == 2)
	{
		player->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			(scale * y) - (scale * 4),
			(scale * 4) - scale/2
			)
			);
	}
	if (face == 3)
	{
		player->GetTransform()->setPosition(
			glm::vec3(
			-(scale * 4) - scale,
			(scale * y) - (scale * 4),
			(scale * x) - (scale * 4)
			)
			);
	}
	if (face == 4)
	{
		player->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			(scale * 4),
			(scale * y) - (scale * 4)
			)
			);
	}
	if (face == 5)
	{

		player->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			-(scale * 4) - scale,
			(scale * y) - (scale * 4)
			)
			);
	}
	playerPosition = glm::vec3(x, y, face);

	player->GetTransform()->setScale(glm::vec3(0.5, 0.5, 0.5));
	player->GetTransform()->setOrientation(glm::vec3(0, 90, 0));

	CGraphics* g = new CGraphics();
	g->addModel("player/boblampclean.md5mesh");
	//g->addModel("player/Miku/miku3.dae");
	player->addComponent(g, "Graphics");


	/*CAnimation* a = new CAnimation();
	a->addAnimation("player/boblampclean.md5anim");
	player->addComponent(a, "Animation");*/

	addEntity(*player);
}

void Sokoban::addSwitch(int x, int y, int face)
{
	float scale = 32.f;
	Entity * e = new Entity();
	if (face == 0)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			(scale * y) - (scale * 4),
			-(scale * 4) - scale / 2
			)
			);
		e->GetTransform()->setScale(glm::vec3(scale, scale, 2));
	}
	if (face == 1)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * 4),
			(scale * y) - (scale * 4),
			(scale * x) - (scale * 4)
			)
			);
		e->GetTransform()->setScale(glm::vec3(2, scale, scale));
	}
	if (face == 2)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * (7 - x)) - (scale * 4),
			(scale * y) - (scale * 4),
			(scale * 4)
			)
			);
		e->GetTransform()->setScale(glm::vec3(scale, scale, 2));
	}
	if (face == 3)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			-(scale * 4) - scale / 2,
			(scale * y) - (scale * 4),
			(scale * x) - (scale * 4)
			)
			);
		e->GetTransform()->setScale(glm::vec3(2, scale, scale));
	}
	if (face == 4)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			(scale * 4),
			(scale * y) - (scale * 4)
			)
			);
		e->GetTransform()->setScale(glm::vec3(scale, 2, scale));
	}
	if (face == 5)
	{

		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			-(scale * 4) - scale/2,
			(scale * y) - (scale * 4)
			)
			);

		e->GetTransform()->setScale(glm::vec3(scale, 2, scale));
	}


	CGraphics* c = new CGraphics();
	c->addModel("wall/wall.obj");
	c->addMaterial("switch/switch.mat");
	e->addComponent(c, "Graphics");

	addEntity(*e);
}

void Sokoban::addBlock(int x, int y, int face)
{
	float scale = 32.f;
	Entity * e = new Entity();
	if (face == 0)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			(scale * y) - (scale * 4),
			-(scale * 4) - scale
			)
			);
	}
	if (face == 1)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * 4),
			(scale * y) - (scale * 4),
			(scale * x) - (scale * 4)
			)
			);
	}
	if (face == 2)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * (7 - x)) - (scale * 4),
			(scale * y) - (scale * 4),
			(scale * 4)
			)
			);
	}
	if (face == 3)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			-(scale * 4) - scale,
			(scale * y) - (scale * 4),
			(scale * x) - (scale * 4)
			)
			);
	}
	if (face == 4)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			(scale * 4),
			(scale * y) - (scale * 4)
			)
			);
	}
	if (face == 5)
	{

		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			-(scale * 4) - scale,
			(scale * y) - (scale * 4)
			)
			);
	}

	e->GetTransform()->setScale(glm::vec3(16, 16, 16));

	CGraphics* c = new CGraphics();
	c->addModel("block/block.obj");
	c->addMaterial("block/block.mat");
	e->addComponent(c, "Graphics");

	//addEntity(e);
}


void Sokoban::addFloor()
{
	float scale = 32.f;
	Entity * e = new Entity();
	e->GetTransform()->setPosition(
		glm::vec3(-scale / 2, -scale/2, -scale / 2)
	);

	e->GetTransform()->setScale(
		glm::vec3(scale * 8, scale * 8, scale * 8)
		);
	CGraphics* c = new CGraphics();
	c->addModel("wall/cube.obj");
	c->addMaterial("ground/floor.mat");
	//c->addMaterial("wall/wall.mat");
	e->addComponent(c, "Graphics");
	addEntity(*e);
}