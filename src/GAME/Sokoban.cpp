#include "Sokoban.h"
#include "../core/SceneManager.h"

int Sokoban::level = 1;
Sokoban::BoardLoader Sokoban::boardloader;

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

	load("assets/levels/extended/0"+std::to_string(Sokoban::level)+".s3d");

	numSwitches = 0;
	completeSides = 0;
	boardloader.currentBoard = 0;
	boardloader.currentX = 0;
	boardloader.currentY = 0;

	gameOver = false;
	gameCompleteTime = 0.f;
}

Sokoban::~Sokoban()
{

}


bool Sokoban::load(std::string filename)
{
	reset();
	Logger::log(WARNING, ("Loading: " + filename).c_str());
	std::ifstream file;
	file.open(filename);

	if (!(file.is_open()))
	{
		Logger::log(ERROR_, "Failed to load level");
		Sokoban::level = 0;
		return false;
	}
	typedef std::istreambuf_iterator<char> buf_iter;
	for (buf_iter i(file), e; i != e; ++i){
		processCharacter(*i);
	}
	file.close();

	for (unsigned int i = 0; i < 6; ++i)
	{
		gameboards[i].checkComplete();
	}


	addFloor();
	addHud();

	Sokoban::level++;

	return true;
}

void Sokoban::nextLevel()
{
	if ( !load("assets/levels/extended/0" + std::to_string(Sokoban::level) + ".s3d") )
	{
		Scene* s = SceneManager::getState("mainmenu");
		if (!s)
		{
			Logger::log(FATAL, "An error has been encountered that could not be recovered from: ERR_NO_SCENE");
		}

		Sokoban::level++;
		s->wantsPriority() = true;
		s->priority = SceneManager::getActiveState()->priority + 1;
		SceneManager::getActiveState()->canDeprioritise() = true;
		s = nullptr;
	}
}

void Sokoban::reset()
{
	m_mEntityList.clear();

	Scene::completeSides = 0;
	player = nullptr;

	for (unsigned int i = 0; i < 6; ++i)
	{
		gameboards[i].reset();
	}

	boardloader.currentBoard = 0;
	boardloader.currentX = 0;
	boardloader.currentY = 0;

	Scene::ForceRecache = true;
	gameCompleteTime = 0.f;
	gameOver = false;

	elapsedTime = 0;
}

void Sokoban::update(float dt)
{
	elapsedTime += dt;
	
	if (((gameboards[0].checkComplete() &&
		gameboards[1].checkComplete() &&
		gameboards[2].checkComplete() &&
		gameboards[3].checkComplete() &&
		gameboards[4].checkComplete() &&
		gameboards[5].checkComplete()) || Scene::completeSides == 1 || Keyboard::get("n") )
		)
	{
		if (!gameOver)
		{
			Logger::log(WARNING, "SOKOBAN: Level complete");
			Entity* ent = new Entity("completed");
			ent->GetTransform()->setPosition(glm::vec3(-0.35, 0.2, 0));
			CGraphics* g = new CGraphics;
			ent->addComponent(g, "Graphics");
			g->addText("Level Complete!", 12);
			g->setRenderMode(RENDER_MODE_2D);
			addEntity(ent);
			Scene::ForceRecache = true;
		}
		gameOver = true;
	}

	if (gameOver)
	{
		gameCompleteTime += dt;
		if (gameCompleteTime >= 4.f)
		{
			nextLevel();
		}
	}


	Scene::update(dt);
}


void Sokoban::processCharacter(const char& c)
{
	if (c == '0')		// Empty Square
	{
		++boardloader.currentX;
		return;
	}
	if (c == '1')	//Wall
	{
		gameboards[boardloader.currentBoard].set(1, boardloader.currentY, boardloader.currentX);
		addWall(boardloader.currentX, boardloader.currentY, boardloader.currentBoard);
		++boardloader.currentX;
		return;
	}
	if (c == '2')	//Block
	{
		gameboards[boardloader.currentBoard].set(2, boardloader.currentY, boardloader.currentX);
		addBlock(boardloader.currentX, boardloader.currentY, boardloader.currentBoard);
		++boardloader.currentX;
		return;
	}
	if (c == '3')	//Switch
	{
		gameboards[boardloader.currentBoard].set(3, boardloader.currentY, boardloader.currentX);
		addSwitch(boardloader.currentX, boardloader.currentY, boardloader.currentBoard);
		++boardloader.currentX;
		gameboards[boardloader.currentBoard].switchCount++;
		numSwitches++;
		return;
	}

	if (c == '4')	//Player
	{
		gameboards[boardloader.currentBoard].set(4, boardloader.currentY, boardloader.currentX);
		addPlayer(boardloader.currentX, boardloader.currentY, boardloader.currentBoard);
		++boardloader.currentX;
		return;
	}



	if (c == '\n')	//NEW LINE
	{
		++boardloader.currentY;
		boardloader.currentX = 0;

		if (boardloader.currentY > 8)
		{
			boardloader.currentY = 0;
			++boardloader.currentBoard;
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
				(scale * (7-x)) - (scale * 4)
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
	e->addComponent(c, "Graphics");
	c->addModel("wall/cube.obj", true, 1.f, false);
	c->addMaterial("wall/wall.mat");

	addEntity(e);
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
			-(scale * 4)
			)
			);
	}
	if (face == 1)
	{
		player->GetTransform()->setPosition(
			glm::vec3(
			(scale * 4),
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
			(scale * 4)
			)
			);
	}
	if (face == 3)
	{
		player->GetTransform()->setPosition(
			glm::vec3(
			-(scale * 4),
			(scale * y) - (scale * 4),
			(scale * (7-x)) - (scale * 4)
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
			-(scale * 4),
			(scale * y) - (scale * 4)
			)
			);
	}
	playerPosition = glm::vec3(x, y, face);

	player->GetTransform()->setScale(glm::vec3(0.5,0.5,0.5));
	player->GetTransform()->setOrientation(glm::vec3(0, 90, 0));

	CGraphics* g = new CGraphics();
	player->addComponent(g, "Graphics");
	g->addModel("player/boblampclean.md5mesh", true, 0.8f, false);
	//g->addModel("wall/wall.obj", true, 0.8f, false);
	//g->addModel("miku/negimiku.dae", true);
	g->addMaterial("player/guard.mat");


	//CAnimation* a = new CAnimation();
	//a->addAnimation("player/boblampclean.md5anim");
	//player->addComponent(a, "Animation");

	addEntity(player);


	Entity* controller = new Entity("PlayerController");
	addEntity(controller);
	CLuaScript* script = new CLuaScript();
	controller->addComponent(script, "LuaScript");
	script->addScript("objects/player/controller.lua");


	GameBoard::playerPosition = playerPosition;
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
		e->GetTransform()->setOrientation(glm::vec3(0, 180, 0));
	}
	if (face == 1)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * 4) - scale / 2,
			(scale * y) - (scale * 4),
			(scale * x) - (scale * 4)
			)
			);
		e->GetTransform()->setOrientation(glm::vec3(0,90,0));
	}
	if (face == 2)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * (7 - x)) - (scale * 4),
			(scale * y) - (scale * 4),
			(scale * 4) - scale / 2
			)
			);
	}
	if (face == 3)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			-(scale * 4) - scale / 2,
			(scale * y) - (scale * 4),
			(scale * (7 - x)) - (scale * 4)
			)
			);
		e->GetTransform()->setOrientation(glm::vec3(0, 270, 0));
	}
	if (face == 4)
	{
		e->GetTransform()->setPosition(
			glm::vec3(
			(scale * x) - (scale * 4),
			(scale * 4) - scale / 2,
			(scale * y) - (scale * 4)
			)
			);
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
	}


	e->GetTransform()->setScale(glm::vec3(0.75, 0.75, 0.75));
	CGraphics* c = new CGraphics();
	c->addModel("switch/plinth.dae");
	c->addMaterial("switch/switch.mat");
	e->addComponent(c, "Graphics");

	addEntity(e);
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
			(scale * (7 - x)) - (scale * 4)
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

	e->GetTransform()->setScale(glm::vec3(15, 15, 15));

	CGraphics* c = new CGraphics();
	e->addComponent(c, "Graphics");
	c->addModel("block/block.obj", true, 0.98f, true);
	c->addMaterial("block/block.mat");

	addEntity(e);
}

void Sokoban::addFloor()
{
	float scale = 32.f;
	Entity * e = new Entity("PLANET");
	e->GetTransform()->setPosition(
		glm::vec3(-scale / 2, -scale/2, -scale / 2)
	);

	e->GetTransform()->setScale(
		glm::vec3(scale * 8, scale * 8, scale * 8)
		);
	CGraphics* c = new CGraphics();
	e->addComponent(c, "Graphics");
	c->addModel("wall/cube.obj", true, 8, false);
	c->addMaterial("ground/floor.mat");
	addEntity(e);
}

void Sokoban::addHud()
{
	Entity * currentlevel = new Entity("CURRENTLEVEL");
	currentlevel->GetTransform()->setPosition(
		glm::vec3(-0.95, 0.9, -0.5)
		);

	CGraphics* c = new CGraphics();
	c->addText(std::string(std::string("Current Level: ") + std::to_string(level)).c_str(), 10);
	c->setRenderMode(RENDER_MODE_2D);
	currentlevel->addComponent(c, "Graphics");
	addEntity(currentlevel);




	Entity * time = new Entity("TIMETAKEN");
	time->GetTransform()->setPosition(
		glm::vec3(-0.95, 0.8, -0.5)
	);

	CGraphics* graphics = new CGraphics();
	graphics->addText("Time Elapsed: ", 8);
	graphics->setRenderMode(RENDER_MODE_2D);
	time->addComponent(graphics, "Graphics");

	CLuaScript* script = new CLuaScript;
	time->addComponent(script, "LuaScript");
	script->addScript("interface/timeElapsed.lua");
	addEntity(time);
}