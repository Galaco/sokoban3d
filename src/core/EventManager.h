#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <string>
#include<map>
#include <vector>

enum MessageType{
	NewEntity,
	DestroyEntity,
	NewComponent,
	DestroyComponent,
	NewPointLight,
	NewDirectionalLight,
	CallScript,
	NewCamera,
	NewActiveCamera
};

class EventManager {
public:
	EventManager();
	~EventManager();


	std::string subscribe(MessageType, void (*)(const char*, void*));
	void unsubscribe(std::string);

	void publish(MessageType, const char*, void*);

private:
	static std::map<MessageType, std::vector<void (*)(const char*, void*)>*> m_registerList;
	static int m_subscriptionId;
};
#endif
