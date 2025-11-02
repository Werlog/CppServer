#include "event/event.h"

Event::Event(EventType eventType)
{
	this->type = eventType;
}

EventType Event::getEventType() const
{
	return type;
}
