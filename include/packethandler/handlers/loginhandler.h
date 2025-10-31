#pragma once

#include "../packethandler.h"

class LoginHandler : public PacketHandler
{
public:

	LoginHandler(Server& server);

	virtual void registerHandlerFunctions() override;
private:
	void handleLoginStart(Message message);
};
