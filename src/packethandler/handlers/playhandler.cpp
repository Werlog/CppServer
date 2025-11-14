#include "packethandler/handlers/playhandler.h"
#include "logger.h"

PlayHandler::PlayHandler(Server& server, Application& application)
	: PacketHandler(server, application)
{
	registerHandlerFunctions();
}

void PlayHandler::registerHandlerFunctions()
{
	handlerFunctions.insert({ 0x0B, PACKET_HANDLER_BIND(&PlayHandler::handleKeepAlive) });
}

void PlayHandler::handleKeepAlive(Message message)
{
	std::unique_ptr<Packet> packet = std::move(message.packet);

	DEBUG_LOG("Received keep alive from client " + std::to_string(message.clientId));
}
