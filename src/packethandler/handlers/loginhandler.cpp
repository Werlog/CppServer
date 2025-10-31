#include "packethandler/handlers/loginhandler.h"
#include <iostream>

LoginHandler::LoginHandler(Server& server)
	: PacketHandler(server)
{
	registerHandlerFunctions();
}

void LoginHandler::registerHandlerFunctions()
{
	handlerFunctions.insert({ 0, PACKET_HANDLER_BIND(&LoginHandler::handleLoginStart) });
}

void LoginHandler::handleLoginStart(Message message)
{
	std::unique_ptr<Packet> packet = std::move(message.packet);

	std::string playerName = packet->readString();

	std::cout << "Received login start, player name: " << playerName << std::endl;
}
