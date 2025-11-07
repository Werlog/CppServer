#pragma once

#include <stdint.h>

enum CommandType : unsigned char
{
	JOIN_COMMAND,
};

class Command
{
public:
	Command(CommandType type, uint32_t fromClientId);

	CommandType getCommandType() const;
	uint32_t getFromClientId() const;
private:
	CommandType type;
	uint32_t fromClientId;
};
