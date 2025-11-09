#pragma once

enum EventType : unsigned char
{	
	PLAYER_JOINED_EVENT,
};

struct Event
{
	EventType type;

	Event(EventType eventType)
	{
		this->type = eventType;
	}

	virtual ~Event() = default;
};
