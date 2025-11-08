#include "event/eventbus.h"
#include "application.h"

EventBus::EventBus()
{

}

void EventBus::dispatchEvents(Application& application)
{
	while (!eventQueue.empty())
	{
		std::shared_ptr<Event> event = eventQueue.pop_front();

		auto it = eventHandlers.find(event->getEventType());
		if (it == eventHandlers.end())
			continue;

		for (auto& handler : it->second)
		{
			handler->handle(event, application);
		}
	}
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

void EventBus::submitEvent(std::shared_ptr<Event> event)
{
	eventQueue.push_back(event);
}
