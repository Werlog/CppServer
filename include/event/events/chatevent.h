#pragma once

#include "../event.h"
#include <string>

enum ChatMessageType : unsigned char
{
	CHAT,
	SYSTEM_MESSAGE,
	GAME_INFO
};

struct ChatEvent : public Event
{
	std::string message;
	bool broadcast;
	uint32_t toClientId;
	ChatMessageType messageType;

	ChatEvent(const std::string& message, uint32_t clientId, bool broadcast = false, ChatMessageType messageType = ChatMessageType::SYSTEM_MESSAGE)
		: Event(EventType::CHAT_EVENT)
	{
		this->message = message;
		this->toClientId = clientId;
		this->broadcast = broadcast;
		this->messageType = messageType;
	}
};
