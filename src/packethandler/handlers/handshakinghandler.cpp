#include "packethandler/handlers/handshakinghandler.h"
#include <iostream>
#include "server.h"

HandshakingHandler::HandshakingHandler(Server& server, Application& application)
	: PacketHandler(server, application)
{
	registerHandlerFunctions();
}

void HandshakingHandler::registerHandlerFunctions()
{
	handlerFunctions.insert({ 0, PACKET_HANDLER_BIND(&HandshakingHandler::handshakeHandler) });
}

void HandshakingHandler::handshakeHandler(Message message)
{
	std::unique_ptr<Packet> packet = std::move(message.packet);

	int32_t protocolVersion = packet->readVarInt();
	std::string address = packet->readString();
	uint16_t port = packet->readUShort();
	int32_t nextState = packet->readVarInt();

	std::shared_ptr<Client> client = server.getClientById(message.clientId);
	if (client != nullptr)
		client->setConnectionState((ConnectionState)nextState);
}
