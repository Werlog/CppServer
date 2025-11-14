#include "packethandler/handlers/playhandler.h"
#include "logger.h"
#include "application.h"
#include "event/events/chatevent.h"

PlayHandler::PlayHandler(Server& server, Application& application)
	: PacketHandler(server, application)
{
	registerHandlerFunctions();
}

void PlayHandler::registerHandlerFunctions()
{
	handlerFunctions.insert({ 0x0B, PACKET_HANDLER_BIND(&PlayHandler::handleKeepAlive) });
	handlerFunctions.insert({ 0x02, PACKET_HANDLER_BIND(&PlayHandler::handleChatMessage) });
}

void PlayHandler::handleKeepAlive(Message message)
{
	// TODO: Kick clients that are not responding to keep alive
}

void PlayHandler::handleChatMessage(Message message)
{
	std::unique_ptr<Packet> packet = std::move(message.packet);

	std::string chatMessage = packet->readString();

	std::shared_ptr<Player> player = application.getPlayerById(message.clientId);
	if (player != nullptr)
	{
		application.submitEvent(std::make_shared<ChatEvent>(player->getPlayerName() + ": " + chatMessage, 0, true, ChatMessageType::CHAT));
	}
}
