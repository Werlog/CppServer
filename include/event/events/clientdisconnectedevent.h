#pragma once

#include <stdint.h>
#include "../event.h"

struct ClientDisconnectedEvent : public Event
{
public:
	uint32_t clientId;

	ClientDisconnectedEvent(uint32_t clientId) : Event(EventType::CLIENT_DISCONNECTED_EVENT)
	{
		this->clientId = clientId;
	}
};
