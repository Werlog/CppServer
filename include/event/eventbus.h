#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include "eventhandler.h"

class EventBus
{
public:

	EventBus();

	void registerHandler(EventType eventType, std::unique_ptr<EventHandler> handler);

	void handleEvent(const Event& event);
private:
	std::unordered_map<EventType, std::vector<std::unique_ptr<EventHandler>>> eventHandlers;
};
