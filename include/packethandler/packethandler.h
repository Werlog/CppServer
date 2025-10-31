#pragma once

#include <stdint.h>
#include <unordered_map>
#include <functional>
#include "message.h"

class Server;

#define PACKET_HANDLER_BIND(method) std::bind((method), this, std::placeholders::_1)

class PacketHandler
{
public:

	PacketHandler(Server& server);

	void handleMessage(Message message);

	virtual void registerHandlerFunctions() = 0;
protected:
	Server& server;

	std::unordered_map<uint32_t, std::function<void(Message)>> handlerFunctions;
};
