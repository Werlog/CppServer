#include "command/commandHandlers/joincommandhandler.h"
#include "command/commands/joincommand.h"

#include "application.h"
#include "logger.h"

CommandResult JoinCommandHandler::handle(const Command& command, Application& application)
{
	const JoinCommand& joinCommand = static_cast<const JoinCommand&>(command);

	if (application.getPlayers().size() >= application.getMaxPlayers())
	{
		return CommandResult::failure("Server is full!");
	}

	std::shared_ptr<Player> player = std::make_shared<Player>(joinCommand.getFromClientId(), joinCommand.getName());

	application.getPlayers().insert({ player->getPlayerId(), player });

	logger::logInfo("Player " + player->getPlayerName() + " joined the game");

	return CommandResult::ok();
}
