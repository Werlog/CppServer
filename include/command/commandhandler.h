#pragma once

#include "command.h"
#include "commandresult.h"

class CommandHandler
{
public:
	virtual CommandResult handle(const Command& command) = 0;
};
