#include "Scene.h"

#include "SceneManager.h"
#include "../components/CGraphics.h"
#include "../components/CLuaScript.h"

Scene::Scene()
{
	priority = 1;
	requestedPriority = false;
	canHalt = false;
	m_runningTime = 0;
	m_currentCamera = nullptr;
}

Scene::~Scene()
{  
	auto it = m_mEntityList.begin();
	while (it != m_mEntityList.end())
	{
		delete it->second;
	}
	auto it2 = m_mCameraList.begin();
	while (it2 != m_mCameraList.end())
	{
		delete it->second;
	}

	delete m_currentCamera;
}


void Scene::update(float dt = 0)
{
	m_runningTime += dt;
	/*auto it = m_mCameraList.begin();
	while(it != m_mCameraList.end()) {
		(*it)->update();
		++it;
	}*/
	m_currentCamera->update();
	auto it = m_listScript.begin();
	while (it != m_listScript.end())
	{
		(*it)->update(dt);
		++it;
	}
}

bool Scene::load(std::string filename)
{
	//Open file
	std::ifstream t(filename);
	if (!t.is_open()){
		Logger::log(ERROR_, (std::string("Scene: Failed to open: ") += filename).c_str());

		return false;
	}

	//Load json to string
	std::string doc((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	//Read json
	Json::Value root;
	Json::Reader reader;
	if (!reader.parse(doc, root))
	{
		Logger::log(ERROR_, reader.getFormattedErrorMessages().c_str());
		return false;
	}

	const Json::Value& sceneData = root.get("scene", 0);
	if (sceneData == 0) return false;

	//Handle settings segment
	const Json::Value& settings = sceneData.get("settings", 0);
	if (settings != 0)
	{
		const Json::Value& mouse = settings.get("mouse", 0);
		if (mouse != 0)
		{
			if (mouse.get("hidden", 0).asBool())
			{
				Mouse::hide();
			}
			else {
				Mouse::hide();
			}
			if (mouse.get("locked", 0).asBool())
			{
				Mouse::lock();
			}
			else {
				Mouse::unlock();
			}
		}
	}
	//Directional light segment
	const Json::Value& directionallight = sceneData.get("directionalLight", 0);
	if (directionallight != 0)
	{
		const Json::Value& color = directionallight.get("color", 0);
		if (color != 0)
		{
			m_directionalLight.Color = glm::vec3(
				color.get("r", 0).asFloat(),
				color.get("g", 0).asFloat(),
				color.get("b", 0).asFloat()
				);
		}
		const Json::Value& ambience = directionallight.get("ambience", 1);
		if (ambience != 0)
		{
			m_directionalLight.AmbientIntensity = ambience.asFloat();
		}
		const Json::Value& diffuse = directionallight.get("diffuse", 1);
		if (ambience != 0)
		{
			m_directionalLight.DiffuseIntensity = diffuse.asFloat();
		}
	}
	//Cameras segment
	const Json::Value& cameras = sceneData.get("cameras", 0);
	if (cameras != 0)
	{
		for (Json::Value::const_iterator it = cameras.begin(); it != cameras.end(); ++it)
		{
			m_mCameraList.push_back(new Camera(it->get("name", "default").asCString()));
			Camera* camera = m_mCameraList[m_mCameraList.size() - 1];
			const Json::Value& transform = it->get("transform", 0);
			if (transform != 0)
			{
				camera->GetTransform()->setPosition(
					glm::vec3(
					transform.get("pX", 0).asDouble(),
					transform.get("pY", 0).asDouble(),
					transform.get("pZ", 0).asDouble()
					)
					);
				camera->GetTransform()->setOrientation(
					glm::vec3(
					transform.get("rX", 0).asDouble(),
					transform.get("rY", 0).asDouble(),
					transform.get("rZ", 0).asDouble()
					)
					);
				camera->GetTransform()->setScale(
					glm::vec3(
					transform.get("sX", 0).asDouble(),
					transform.get("sY", 0).asDouble(),
					transform.get("sZ", 0).asDouble()
					)
					);
			}
			const Json::Value& skybox = it->get("skybox", 0);
			if (skybox != 0)
			{
				camera->addSkybox(skybox.asString());
			}
			const Json::Value& mode = it->get("mode", 0);
			if (mode != 0)
			{
				camera->setCameraMode(CAMERA_ORBIT);
			}

			if (m_currentCamera == nullptr)
			{
				m_currentCamera = m_mCameraList[m_mCameraList.size() - 1];
			}
		}
	}
	//Entities segment
	const Json::Value& entities = sceneData.get("entities", 0);
	if (entities != 0)
	{
		for (Json::Value::const_iterator it = entities.begin(); it != entities.end(); ++it)
		{
			std::string name = it->get("name", "default").asString();
			Entity* entity = new Entity(name.c_str());
			m_mEntityList[name] = entity;
			entity = m_mEntityList[name];
			const Json::Value& transform = it->get("transform", 0);
			if (transform != 0)
			{
				entity->GetTransform()->setPosition(
					glm::vec3(
					transform.get("pX", 0).asDouble(),
					transform.get("pY", 0).asDouble(),
					transform.get("pZ", 0).asDouble()
					)
					);
				entity->GetTransform()->setOrientation(
					glm::vec3(
					transform.get("rX", 0).asDouble(),
					transform.get("rY", 0).asDouble(),
					transform.get("rZ", 0).asDouble()
					)
					);
				entity->GetTransform()->setScale(
					glm::vec3(
					transform.get("sX", 1).asDouble(),
					transform.get("sY", 1).asDouble(),
					transform.get("sZ", 1).asDouble()
					)
					);
			}


			const Json::Value& components = it->get("components", 0);
			if (components != 0)
			{
				const Json::Value& graphics = components.get("graphics", 0);
				if (graphics != 0)
				{
					CGraphics* g = new CGraphics();
					const Json::Value& model = graphics.get("model", 0);
					if (model != 0)
					{
						g->addModel(model.asCString());
					}
					const Json::Value& text = graphics.get("text", 0);
					if (text != 0)
					{
						g->addText(text.asCString(), graphics.get("textSize", 10).asDouble());
					}
					const Json::Value& renderMode = graphics.get("rendermode", 0);
					if (renderMode != 0)
					{
						if (renderMode == "RENDER_2D")
						{
							g->setRenderMode(RENDER_MODE_2D);
						}
						else {
							g->setRenderMode(RENDER_MODE_3D);
						}
					}
					const Json::Value& material = graphics.get("material", 0);
					if (material != 0)
					{
						g->addMaterial(material.asCString());
					}
					entity->addComponent(g, "Graphics");
					g->setOwner(entity);
				}
			}

			const Json::Value& script = it->get("script", 0);
			if (script != 0)
			{
				if (script.get("path", 0) != 0)
				{
					CLuaScript* cscript = new CLuaScript();
					cscript->addScript(script.get("path", 0).asCString());
					entity->addComponent(cscript, "LuaScript");
					cscript->setOwner(entity);
				}

			}
		}
	}

	wantsPriority() = true;
	priority = SceneManager::getActiveState()->priority + 1;

	return true;
}



std::map<std::string, Entity*>& Scene::getEntities()
{
	return m_mEntityList;
}

std::vector<Camera*>& Scene::getCameras()
{
	return m_mCameraList;
}

std::vector<PointLight*>& Scene::getPointLights()
{
	return m_listPointLight;
}

Entity* Scene::getEntity(std::string name)
{
	if (m_mEntityList.find(name) != m_mEntityList.end()) 
	{
		return m_mEntityList[name];
	}
	else
	{
		return nullptr;
	}

}

Camera* Scene::getCamera(std::string name)
{
	auto it = m_mCameraList.begin();
	while (it != m_mCameraList.end())
	{
		if ((*it)->getId() == name)
		{
			return (*it);
		}
		++it;
	}
	return nullptr;

}

void Scene::addEntity(Entity* entity){
	if (m_mEntityList.find(entity->getId()) != m_mEntityList.end())
	{
		delete entity;
		return;
	}
	m_mEntityList[entity->getId()] = entity;
}

void Scene::addCamera(Camera* entity){
	auto it = m_mCameraList.begin();
	while (it != m_mCameraList.end())
	{
		if (entity->getId() == (*it)->getId()){
			return;
		}
		++it;
	}
	m_mCameraList.push_back(entity);

	if (m_mCameraList.size() == 1)
	{
		m_currentCamera = entity;
	}
}

void Scene::addPointLight(PointLight* light){
	m_listPointLight.push_back(light);
}

void Scene::addScript(LuaScript* script){
	m_listScript.push_back(script);
}

Camera* Scene::getCurrentCamera()
{
	return m_currentCamera;
}

void Scene::setCurrentCamera(Camera* camera)
{
	if (camera != nullptr) {
		m_currentCamera = camera;
		//System::setCurrentCamera(m_currentCamera);
		m_currentCamera->rebuildView();
	}
}

DirectionalLight& Scene::getDirectionalLight()
{
	return m_directionalLight;
}

bool& Scene::wantsPriority()
{
	return requestedPriority;
}
bool& Scene::canDeprioritise()
{
	return canHalt;
}