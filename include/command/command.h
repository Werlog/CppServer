#pragma once

#include <stdint.h>

enum CommandType : unsigned char
{
	JOIN_COMMAND,
};

struct Command
{
	Command(CommandType type, uint32_t clientId)
	{
		this->type = type;
		this->clientId = clientId;
	}

	virtual ~Command() = default;

	CommandType type;
	uint32_t clientId;
};
