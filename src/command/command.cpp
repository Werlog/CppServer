#include "command/command.h"

Command::Command(CommandType type)
{
	this->type = type;
}

CommandType Command::getCommandType() const
{
	return type;
}
