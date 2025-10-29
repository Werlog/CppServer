#pragma once

#include "../packethandler.h"

class StatusHandler : public PacketHandler
{
public:
	StatusHandler(Server& server);

	virtual void registerHandlerFunctions() override;
private:
	void requestHandler(Message message);
	void pingHandler(Message message);
};
