#include "Identifier.h"

int Identifier::m_nextId = 0;
std::map<std::string, bool> Identifier::m_manualList;

Identifier::Identifier(){  
     
}

Identifier::~Identifier(){ 
    
}

std::string Identifier::gen(){
    std::string s = "Unique_"+ std::to_string(m_nextId);
    ++m_nextId;
    
    m_id = s;
    return m_id;
}

std::string Identifier::gen(const char* id ){
    if (m_manualList.find(std::string(id)) != m_manualList.end()) {
	m_pLogger->log(_WARNING, ("Unique id: " + std::string(id) + "is already in use. Changing its name is advised").c_str());
    } else {
	m_manualList[id] = true;
    }
    m_id = std::string(id);
    return m_id;
}

std::string Identifier::get(){
    return m_id;
}