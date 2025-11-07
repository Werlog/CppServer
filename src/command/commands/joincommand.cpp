#include "command/commands/joincommand.h"


JoinCommand::JoinCommand(uint32_t fromClientId, const std::string& playerName)
	: Command(CommandType::JOIN_COMMAND, fromClientId)
{
	this->playerName = playerName;
}

const std::string& JoinCommand::getName() const
{
	return playerName;
}
