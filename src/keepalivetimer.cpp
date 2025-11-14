#include "keepalivetimer.h"

KeepAliveTimer::KeepAliveTimer(Server& server)
	: server(server)
{
	this->ticksSinceKeepAlive = 0;
}

void KeepAliveTimer::update()
{
	ticksSinceKeepAlive++;
	if (ticksSinceKeepAlive > ticksBetweenKeepAlive)
	{
		broadcastKeepAlive();
		ticksSinceKeepAlive = 0;
	}
}

void KeepAliveTimer::broadcastKeepAlive()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::unique_ptr<Packet> keepAlive = std::make_unique<Packet>(0x1F);
	auto duration = currentTime.time_since_epoch();
	long millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	keepAlive->writeLong(millis);
	server.sendToAllPlaying(std::move(keepAlive));
}
