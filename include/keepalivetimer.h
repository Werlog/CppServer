#pragma once

#include <chrono>
#include "server.h"

constexpr int ticksBetweenKeepAlive = 200;

class KeepAliveTimer
{
public:

	KeepAliveTimer(Server& server);

	void update();

private:
	Server& server;
	int ticksSinceKeepAlive;

	void broadcastKeepAlive();
};
