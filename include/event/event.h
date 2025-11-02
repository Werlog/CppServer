#pragma once

enum EventType : unsigned char
{	
	
};

class Event
{
public:
	Event(EventType eventType);

	EventType getEventType() const;
private:
	EventType type;
};
