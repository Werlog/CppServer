#pragma once

#include "../command.h"
#include <string>

struct JoinCommand : public Command
{
public:
	std::string playerName;

	JoinCommand(uint32_t fromClientId, const std::string& playerName)
		: Command(CommandType::JOIN_COMMAND, fromClientId)
	{
		this->playerName = playerName;
	}
};
