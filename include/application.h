#pragma once

#include "server.h"
#include "command/commandbus.h"
#include "event/eventbus.h"

class Application
{
public:
	Application();

	void mainLoop();
private:
	CommandBus commandBus;
	EventBus eventBus;
	Server server;
};
