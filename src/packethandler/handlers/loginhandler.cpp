#include "packethandler/handlers/loginhandler.h"
#include <iostream>
#include "command/commands/joincommand.h"
#include "server.h"
#include "command/commandresult.h"
#include "application.h"
#include "logger.h"

LoginHandler::LoginHandler(Server& server, Application& application)
	: PacketHandler(server, application)
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
	
	CommandResult result = application.submitCommand(JoinCommand(message.clientId, playerName));
	if (!result)
	{
		std::shared_ptr<Client> client = server.getClientById(message.clientId);
		if (client != nullptr)
		{
			std::unique_ptr<Packet> disconnectPacket = std::make_unique<Packet>(0);
			disconnectPacket->writeString("{\"text\":\"" + result.message + "\"}");
			client->sendPacket(std::move(disconnectPacket));
		}
		logger::logInfo("Player " + playerName + " could not join: " + result.message);
	}
}
