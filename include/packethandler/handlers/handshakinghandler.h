#pragma once

#include "../packethandler.h"

class HandshakingHandler : public PacketHandler
{
public:
	HandshakingHandler(Server& server, Application& application);

	virtual void registerHandlerFunctions() override;
private:
	void handshakeHandler(Message message);
};
