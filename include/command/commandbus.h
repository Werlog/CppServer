#pragma once

#include <unordered_map>
#include <memory>
#include "command.h"
#include "commandhandler.h"

class CommandBus
{
public:

	CommandBus();

	void registerHandler(CommandType commandType, std::unique_ptr<CommandHandler> handler);

	CommandResult execute(const Command& command, Application& application);
private:
	std::unordered_map<CommandType, std::unique_ptr<CommandHandler>> handlers;
};
