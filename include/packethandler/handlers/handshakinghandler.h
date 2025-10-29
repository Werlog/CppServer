#pragma once

#include "../packethandler.h"

class HandshakingHandler : public PacketHandler
{
public:
	HandshakingHandler(Server& server);

	virtual void registerHandlerFunctions() override;
private:
	void handshakeHandler(Message message);
};
