#pragma once

#include "command.h"
#include "commandresult.h"

class Application;

class CommandHandler
{
public:
	virtual CommandResult handle(const Command& command, Application& application) = 0;
};
