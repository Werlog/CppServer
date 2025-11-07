#pragma once

#include <stdint.h>
#include <unordered_map>
#include <functional>
#include "message.h"

class Server;
class Application;

#define PACKET_HANDLER_BIND(method) std::bind((method), this, std::placeholders::_1)

class PacketHandler
{
public:

	PacketHandler(Server& server, Application& application);

	void handleMessage(Message message);

	virtual void registerHandlerFunctions() = 0;
protected:
	Server& server;
	Application& application;

	std::unordered_map<uint32_t, std::function<void(Message)>> handlerFunctions;
};
