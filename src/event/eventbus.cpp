#include "event/eventbus.h"

EventBus::EventBus()
{

}

void EventBus::registerHandler(EventType eventType, std::unique_ptr<EventHandler> handler)
{
	auto it = eventHandlers.find(eventType);
	if (it == eventHandlers.end())
	{
		std::vector<std::unique_ptr<EventHandler>> handlers = std::vector<std::unique_ptr<EventHandler>>();
		handlers.push_back(std::move(handler));
		eventHandlers.insert({ eventType, std::move(handlers) });
		return;
	}

	it->second.push_back(std::move(handler));
}

void EventBus::handleEvent(const Event& event)
{
	auto it = eventHandlers.find(event.getEventType());
	if (it == eventHandlers.end())
		return;

	for (auto&& handler : it->second)
	{
		handler->handle(event);
	}
}
