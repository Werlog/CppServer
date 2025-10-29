#pragma once

#include <asio.hpp>
#include "util/tsqueue.h"
#include "packet.h"
#include <stdint.h>
#include <thread>
#include "connection.h"

class Server
{
public:
	Server(uint32_t serverPort);

	void update(uint32_t maxPackets = -1);

	bool startServer();
	bool stopServer();

	void receivePacket(Packet& packet);
private:
	std::vector<std::shared_ptr<Connection>> connections;

	tsqueue<Packet> packetQueue;
	asio::io_context context;
	std::thread contextThread;

	asio::ip::tcp::acceptor acceptor;

	void beginAcceptClient();
};
