#include "Identifier.h"

int Identifier::m_nextId = 0;
std::map<std::string, int> Identifier::m_manualList;

Identifier::Identifier(){  
     
}

Identifier::~Identifier(){ 
    
}

std::string Identifier::gen(){
	//Generates a unique id for any object that asks. Format is Unique_x where x is a number
    std::string s = "Unique_"+ std::to_string(m_nextId);
    ++m_nextId;
    
    m_id = s;
    return m_id;
}

std::string Identifier::gen(const char* id ){
	//If a custom name requested, use that if it is available.
    if (m_manualList.find(std::string(id)) != m_manualList.end()) {
		m_manualList[id] += 1;

		m_id = std::string(id) + std::to_string(m_manualList[id]);
		m_pLogger->log(WARNING, ("Unique id: " + std::string(id) + "in use. Object has renamed to: " + (id + m_nextId)).c_str());
    } else {
		m_manualList[id] = 1;
		m_id = std::string(id);
    }
    return m_id;
}

std::string Identifier::get(){
    return m_id;
}