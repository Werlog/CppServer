#pragma once

#include <asio.hpp>
#include "util/tsqueue.h"
#include "packet.h"
#include <stdint.h>
#include <thread>
#include "client.h"
#include <unordered_map>

class Server
{
public:
	Server(uint32_t serverPort);

	void update(uint32_t maxPackets = -1);

	bool startServer();
	bool stopServer();

	void receiveMessage(Message message);
	void onClientDisconnected(uint32_t clientId);
private:
	std::unordered_map<uint32_t, std::shared_ptr<Client>> clients;
	tsqueue<Message> messageQueue;
	uint32_t currentClientId;

	asio::io_context context;
	std::thread contextThread;
	asio::ip::tcp::acceptor acceptor;

	void beginAcceptClient();
	uint32_t getNextClientId();
};
