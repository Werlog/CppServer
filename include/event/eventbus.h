#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include "eventhandler.h"
#include "util/tsqueue.h"

class Application;

class EventBus
{
public:

	EventBus();

	void dispatchEvents(Application& application);

	void registerHandler(EventType eventType, std::unique_ptr<EventHandler> handler);

	void submitEvent(std::shared_ptr<Event> event);
private:
	tsqueue<std::shared_ptr<Event>> eventQueue;
	std::unordered_map<EventType, std::vector<std::unique_ptr<EventHandler>>> eventHandlers;
};
