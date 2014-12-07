/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Identifier
Description: Generates unique entity Ids where an id has not been 
			 identified
*********************************************************************/
#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>
#include <map>

#include <core/Logger.h>

class Identifier
{
public:
	Identifier();
	~Identifier();
        
        std::string gen();
        std::string gen(const char*);
        
        std::string get();

private:
    static int m_nextId;
    static std::map<std::string, int> m_manualList;
    
    std::string m_id;
};
#endif
