/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Scene
Description: A state within the state machine. Could also be referred 
			 to as a scene. More than anything, its a data store that 
			 classes can get and set, and are contained within.
*********************************************************************/
#ifndef SCENE_H
#define SCENE_H

#include <string>

#include <core/Entity.h>
#include <core/Camera.h>
#include <core/resources/DirectionalLight.h>
#include <core/resources/PointLight.h>
#include <core/resources/LuaScript.h>

#include <json/json.h>


#include "../GAME/GameBoard.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	virtual void update(float dt);
	
	std::map<std::string, Entity*>& getEntities();
	std::vector<Camera*>& getCameras();
	std::vector<PointLight*>& getPointLights();

	bool load(std::string filename);

	void addEntity(Entity*);
	void addCamera(Camera*);
	void addPointLight(PointLight*);
	void addScript(LuaScript*);

	Entity* getEntity(std::string);
	Camera* getCamera(std::string);
	Camera* getCurrentCamera();
	void setCurrentCamera(Camera* camera);
	DirectionalLight& getDirectionalLight();


	bool& wantsPriority();
	bool& canDeprioritise();

	unsigned int priority;



	glm::vec3& getPlayerPosition(){ return playerPosition; };
	GameBoard& getGameBoard(int id){ return gameboards[id]; };
	glm::vec3 playerPosition;	//X,Y,BoardId
	
protected:
	std::string m_name;

	bool requestedPriority;
	bool canHalt;
	float m_runningTime;

	Camera* m_currentCamera;

	std::map<std::string, Entity*>	m_mEntityList;
	std::vector<Camera*>	m_mCameraList;
	std::vector<PointLight*>	m_listPointLight;
	DirectionalLight m_directionalLight;
	std::vector<LuaScript *>	m_listScript;


	static GameBoard gameboards[6];
};
#endif