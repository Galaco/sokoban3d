#include "Material.h"

Material::Material(){
	translucent = 0;
}

Material::Material(const char* path){

}

Material::~Material(){

}

bool Material::load(const char* filename){
	std::string path("assets/materials/");
	path += filename;

	//Open file
	std::ifstream t(path);
	if (!t.is_open()){
		Logger::log(ERROR_, (std::string("Material: Failed to open: ") += path).c_str());
		prepareDefaults();

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
		prepareDefaults();
		return false;
	}
	
	//Set material values from json
	m_texture = ResourceManager::add<Texture>(root.get("diffuse", "vgui/defaults/error.jpg").asString());
	translucent = root.get("translucent", "0").asBool();
	//More values to be added at a later date

	return true;
}
GLuint Material::texId()
{
	if (!m_texture) return 0;
	return m_texture->getTexId();
}

void Material::prepareDefaults()
{
	m_texture = ResourceManager::add<Texture>("vgui/defaults/error.jpg");
	translucent = 0;
}