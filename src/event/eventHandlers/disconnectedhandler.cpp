#include "event/eventHandlers/disconnectedhandler.h"
#include "event/events/clientdisconnectedevent.h"
#include "application.h"
#include "logger.h"

void DisconnectedEventHandler::handle(std::shared_ptr<const Event> event, Application& application)
{
	auto disconnectedEvent = std::dynamic_pointer_cast<const ClientDisconnectedEvent>(event);

	std::shared_ptr<Player> player = application.getPlayerById(disconnectedEvent->clientId);
	if (player != nullptr)
	{
		application.removePlayer(player->getPlayerId());
		logger::logInfo("Player " + player->getPlayerName() + " left the game");

		application.broadcastMessage(player->getPlayerName() + " left the game");
	}
}
