#include "EventManager.h"

std::map<MessageType, std::vector<void (*)(const char*, void*)>*> EventManager::m_registerList;
int EventManager::m_subscriptionId = -1;

EventManager::EventManager(){

}

EventManager::~EventManager(){
}

std::string EventManager::subscribe(MessageType t, void (*f)(const char* c, void* v)) {
	if (m_registerList.find(t) == m_registerList.end() ) {
		m_registerList[t] = new std::vector<void (*)(const char*, void*)>;
	}
	m_registerList[t]->push_back((f));
	m_subscriptionId++;

	std::string r = std::to_string(t) + "_" + std::to_string(m_subscriptionId);
	return r;
}

void EventManager::unsubscribe(std::string subscriptionId){
	unsigned found = subscriptionId.find_last_of("_");
	MessageType t = static_cast<MessageType>(atoi(subscriptionId.substr(0, found).c_str()));
	int id = atoi(subscriptionId.substr(found+1, subscriptionId.length()-found).c_str());

	m_registerList[t]->erase(m_registerList[t]->begin()+id);
}

void EventManager::publish(MessageType t, const char* c, void* v = nullptr){
	auto it = m_registerList[t]->begin();
	while (it != m_registerList[t]->end()) {
		(*it)(c, v);;
		++it;
	}
}