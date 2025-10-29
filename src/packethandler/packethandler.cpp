#include "packethandler/packethandler.h"
#include "server.h"

PacketHandler::PacketHandler(Server& server)
	: server(server)
{

}

void PacketHandler::handleMessage(Message message)
{
	auto it = handlerFunctions.find(message.packet->getPacketId());
	if (it == handlerFunctions.end())
		return;

	if (it->second)
		it->second(std::move(message));
}
