#include "packethandler/packethandler.h"
#include "server.h"
#include "logger.h"

PacketHandler::PacketHandler(Server& server, Application& application)
	: server(server), application(application)
{

}

void PacketHandler::handleMessage(Message message)
{
	auto it = handlerFunctions.find(message.packet->getPacketId());
	if (it == handlerFunctions.end())
	{
		DEBUG_LOG("No handler function found for packet id " + std::to_string(message.packet->getPacketId()));
		return;
	}

	if (it->second)
		it->second(std::move(message));
}
