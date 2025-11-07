#include "command/command.h"

Command::Command(CommandType type, uint32_t fromClientId)
{
	this->type = type;
	this->fromClientId = fromClientId;
}

CommandType Command::getCommandType() const
{
	return type;
}

uint32_t Command::getFromClientId() const
{
	return fromClientId;
}
