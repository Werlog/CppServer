#pragma once

#include "server.h"

class Application
{
public:
	Application();

	void mainLoop();
private:
	Server server;
};
