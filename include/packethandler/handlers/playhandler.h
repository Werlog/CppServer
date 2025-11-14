#pragma once

#include "../packethandler.h"

class PlayHandler : public PacketHandler
{
public:
	PlayHandler(Server& server, Application& application);

	virtual void registerHandlerFunctions() override;
private:
	void handleKeepAlive(Message message);
	void handleChatMessage(Message message);
};
