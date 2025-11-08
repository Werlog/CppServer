#pragma once

enum EventType : unsigned char
{	
	PLAYER_JOINED_EVENT,
};

class Event
{
public:
	Event(EventType eventType);
	virtual ~Event() = default;

	EventType getEventType() const;
private:
	EventType type;
};
