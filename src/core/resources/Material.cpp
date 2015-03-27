#include "Material.h"

Material::Material(){
	translucent = 0;
}

Material::Material(const char* path){
	load(path);
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
	m_diffuse = ResourceManager::add<Texture>(root.get("diffuse", "vgui/defaults/error.jpg").asString());
	m_normal = ResourceManager::add<Texture>(root.get("normal", "vgui/defaults/error_n.jpg").asString());
	m_specular = ResourceManager::add<Texture>(root.get("specular", "vgui/defaults/error_s.jpg").asString());
	translucent = root.get("translucent", "0").asBool();
	fullbright = root.get("fullbright", "0").asBool();

	return true;
}
GLuint Material::texId(TextureType t)
{
	if (t == TextureType::DIFFUSE)
	{
		if (!m_diffuse)
		{
			return 0;
		}
		return m_diffuse->getTexId();
	}
	if (t == TextureType::NORMAL)
	{
		if (!m_normal)
		{
			return 0;
		}
		return m_normal->getTexId();
	}
	if (t == TextureType::SPECULAR)
	{
		if (!m_specular)
		{
			return 0;
		}
		return m_specular->getTexId();
	}


	return 0;
}

void Material::prepareDefaults()
{
	m_diffuse = ResourceManager::add<Texture>("vgui/defaults/error.jpg");
	m_normal = ResourceManager::add<Texture>("vgui/defaults/error.jpg");
	m_specular = ResourceManager::add<Texture>("vgui/defaults/error.jpg");
	translucent = 0;
}