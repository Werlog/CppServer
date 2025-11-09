#pragma once

enum EventType : unsigned char
{	
	PLAYER_JOINED_EVENT,
	CLIENT_DISCONNECTED_EVENT,
	CHAT_EVENT,
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
