#include "command/commandbus.h"

CommandBus::CommandBus()
{

}

void CommandBus::registerHandler(CommandType commandType, std::unique_ptr<CommandHandler> handler)
{
	auto it = handlers.find(commandType);
	if (it != handlers.end())
		return;

	handlers.insert({ commandType, std::move(handler) });
}

CommandResult CommandBus::execute(const Command& command)
{
	auto it = handlers.find(command.getCommandType());

	if (it == handlers.end())
		return CommandResult::failure("No command handler found");

	return it->second->handle(command);
}
