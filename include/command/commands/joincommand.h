#pragma once

#include "../command.h"
#include <string>

class JoinCommand : public Command
{
public:

	JoinCommand(uint32_t fromClientId, const std::string& playerName);

	const std::string& getName() const;
private:
	std::string playerName;
};
